//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H
#define PXR_IMAGING_HD_ST_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H

#include "Hd/bufferSource.h"
#include "Hd/types.h"
#include "HdSt/api.h"
#include "pxr/pxrns.h"

#include "Tf/token.h"

#include "Sdf/path.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdStExtCompGpuPrimvarBufferSource
/// A buffer source mapped to an output of an ExtComp CPU computation.
///
class HdStExtCompGpuPrimvarBufferSource final : public HdNullBufferSource {
 public:
  HdStExtCompGpuPrimvarBufferSource(TfToken const &name,
                                    HdTupleType const &valueType,
                                    int numElements,
                                    SdfPath const &compId);

  HDST_API
  virtual ~HdStExtCompGpuPrimvarBufferSource() = default;

  HDST_API
  virtual size_t ComputeHash() const override;

  HDST_API
  virtual bool Resolve() override;

  HDST_API
  virtual TfToken const &GetName() const override;

  HDST_API
  virtual size_t GetNumElements() const override;

  HDST_API
  virtual HdTupleType GetTupleType() const override;

  HDST_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  TfToken _name;
  HdTupleType _tupleType;
  size_t _numElements;
  SdfPath _compId;

  HdStExtCompGpuPrimvarBufferSource() = delete;
  HdStExtCompGpuPrimvarBufferSource(const HdStExtCompGpuPrimvarBufferSource &) = delete;
  HdStExtCompGpuPrimvarBufferSource &operator=(const HdStExtCompGpuPrimvarBufferSource &) = delete;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H
