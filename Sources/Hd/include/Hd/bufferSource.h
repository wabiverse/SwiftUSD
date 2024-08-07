//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_BUFFER_SOURCE_H
#define PXR_IMAGING_HD_BUFFER_SOURCE_H

#include "Hd/api.h"
#include "Hd/bufferSpec.h"
#include "Hd/version.h"
#include "Tf/diagnostic.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

#include <atomic>
#include <memory>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class HdBufferSource;
using HdBufferSourceSharedPtr = std::shared_ptr<HdBufferSource>;
using HdBufferSourceConstSharedPtr = std::shared_ptr<HdBufferSource const>;
using HdBufferSourceSharedPtrVector = std::vector<HdBufferSourceSharedPtr>;
using HdBufferSourceWeakPtr = std::weak_ptr<HdBufferSource>;

/// \class HdBufferSource
///
/// A transient buffer of data that has not yet been committed.
///
/// HdBufferSource is an abstract interface class, to be registered to the
/// resource registry with the buffer array range that specifies the
/// destination resource.
///
class HdBufferSource {
 public:
  HdBufferSource() : _state(UNRESOLVED) {}

  HD_API
  virtual ~HdBufferSource();

  /// Return the name of this buffer source.
  virtual TfToken const &GetName() const = 0;

  /// Add the buffer spec for this buffer source into given bufferspec vector.
  /// note: buffer specs has to be determined before the source resolution.
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const = 0;

  /// Computes and returns a hash value for the underlying data.
  HD_API
  virtual size_t ComputeHash() const;

  /// Prepare the access of GetData(). This process may include some
  /// computations (e.g. cpu smooth normals).
  /// Note: Resolve may be called in parallel from multiple threads
  /// across buffer sources, so be careful if it uses static/shared
  /// states among objects.
  /// Returns true if it resolved. If the buffer source has to wait
  /// some results of other buffer sources, or the buffer source is
  /// being resolved by other threads, it returns false.
  virtual bool Resolve() = 0;

  /// Following interfaces will be called after Resolve.

  /// Returns the raw pointer to the underlying data.
  virtual void const *GetData() const = 0;

  /// Returns the data type and count (array size) for this buffer source.
  virtual HdTupleType GetTupleType() const = 0;

  /// Returns the number of elements (e.g. VtVec3dArray().GetLength()) from
  /// the source array.
  virtual size_t GetNumElements() const = 0;

  /// Returns true it this computation has already been resolved.
  bool IsResolved() const
  {
    return _state >= RESOLVED;
  }

  /// Returns true if an error occurred during resolve.
  bool HasResolveError() const
  {
    return _state == RESOLVE_ERROR;
  }

  /// \name Chained Buffers
  /// Buffer sources may be daisy-chained together.
  ///
  /// Pre-chained buffer sources typically represent sources that
  /// are inputs to computed buffer sources (e.g. coarse vertex
  /// privmar data needing to be quadrangulated or refined) and
  /// will be scheduled to be resolved along with their owning
  /// buffer sources.
  ///
  /// Post-chained buffer sources typically represent additional
  /// results produced by a computation (e.g. primitive param data
  /// computed along with index buffer data) and will be scheduled
  /// to be committed along with their owning buffer sources.
  /// @{

  /// Returns true if this buffer has a pre-chained buffer.
  HD_API
  virtual bool HasPreChainedBuffer() const;

  /// Returns the pre-chained buffer.
  HD_API
  virtual HdBufferSourceSharedPtr GetPreChainedBuffer() const;

  /// Returns true if this buffer has any chained buffer(s)
  HD_API
  virtual bool HasChainedBuffer() const;

  /// Returns the vector of chained buffers.
  HD_API
  virtual HdBufferSourceSharedPtrVector GetChainedBuffers() const;

  /// @}

  /// Checks the validity of the source buffer.
  /// The function should be called to determine if
  /// AddBufferSpec() and Resolve() would return valid
  /// results.
  HD_API
  bool IsValid() const;

 protected:
  /// Marks this buffer source as resolved. It has to be called
  /// at the end of Resolve on concrete implementations.
  void _SetResolved()
  {
    TF_VERIFY(_state == BEING_RESOLVED);
    _state = RESOLVED;
  }

  /// Called during Resolve() to indicate an unrecoverable failure occurred
  /// and the results of the computation can not be used.
  /// Further calls to Resolve() will not lead to success.
  ///
  /// This is different from Resolve() returning false, which indicates
  /// that additional calls to Resolve() will eventually lead to success.
  ///
  /// This is also later in the pipeline than IsValid, which checks
  /// that the buffer is setup such that Resolve() can be successful.
  void _SetResolveError()
  {
    TF_VERIFY(_state == BEING_RESOLVED);
    _state = RESOLVE_ERROR;
  }

  /// Non-blocking lock acquisition.
  /// If no one else is resolving this buffer source, returns true.
  /// In that case the caller needs to call _SetResolved at the end
  /// of computation.
  /// It returns false if anyone else has already acquired lock.
  bool _TryLock()
  {
    State oldState = UNRESOLVED;
    return _state.compare_exchange_strong(oldState, BEING_RESOLVED);
  }

  /// Checks the validity of the source buffer.
  /// This function is called by IsValid() to do the real checking.
  ///
  /// Should only be implemented in classes at leafs of the class hierarchy
  /// (Please place common validation code in a new non-virtual method)
  ///
  /// This code should return false:
  ///   - If the buffer would produce an invalid BufferSpec
  ///   - If a required dependent buffer is invalid
  /// For example, return false when:
  ///   The data type is invalid, causing an invalid BufferSpec.
  ///
  ///   The resolve step requires a 'source' buffer and that buffer is invalid.
  ///
  /// If returning false, the buffer will not be registered with the resource
  /// registry.  AddBufferSpec and Resolve will not be called
  virtual bool _CheckValid() const = 0;

 private:
  // Don't allow copies
  HdBufferSource(const HdBufferSource &) = delete;
  HdBufferSource &operator=(const HdBufferSource &) = delete;

  enum State { UNRESOLVED = 0, BEING_RESOLVED, RESOLVED, RESOLVE_ERROR };
  std::atomic<State> _state;
};

/// A abstract base class for cpu computation followed by buffer
/// transfer to the GPU.
///
/// concrete class needs to implement
///   virtual void GetBufferSpecs(HdBufferSpecVector *specs) const;
///   virtual void Resolve();
/// and set the result via _SetResult().
///
class HdComputedBufferSource : public HdBufferSource {
 public:
  HD_API
  virtual TfToken const &GetName() const override;
  HD_API
  virtual size_t ComputeHash() const override;
  HD_API
  virtual void const *GetData() const override;
  HD_API
  virtual HdTupleType GetTupleType() const override;
  HD_API
  virtual size_t GetNumElements() const override;

 protected:
  void _SetResult(HdBufferSourceSharedPtr const &result)
  {
    _result = result;
  }

 private:
  HdBufferSourceSharedPtr _result;
};

/// A abstract base class for pure cpu computation.
/// the result won't be scheduled for GPU transfer.
///
class HdNullBufferSource : public HdBufferSource {
 public:
  HD_API
  virtual TfToken const &GetName() const override;
  HD_API
  virtual void const *GetData() const override;
  HD_API
  virtual size_t ComputeHash() const override;
  HD_API
  virtual size_t GetNumElements() const override;
  HD_API
  virtual HdTupleType GetTupleType() const override;
  HD_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_BUFFER_SOURCE_H
