//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_QUADRANGULATE_H
#define PXR_IMAGING_HD_ST_QUADRANGULATE_H

#include "HdSt/computation.h"
#include "pxr/pxrns.h"

#include "Hd/bufferSource.h"

#include "Sdf/path.h"
#include "Tf/token.h"
#include "Vt/array.h"

PXR_NAMESPACE_OPEN_SCOPE

using HdSt_QuadInfoBuilderComputationSharedPtr =
    std::shared_ptr<class HdSt_QuadInfoBuilderComputation>;

class HdSt_MeshTopology;

/*
  Computation classes for quadrangulation.

   *CPU quadrangulation

    (buffersource)
     QuadIndexBuilderComputation  (quad indices)
      |
      +--QuadrangulateComputation (primvar quadrangulation)

     note: QuadrangulateComputation also copies the original primvars.
           no need to transfer the original primvars to GPU separately.

       +--------------------+
   CPU |  original primvars |
       +--------------------+
                |
                v
       +--------------------+-------------------------+
   CPU |  original primvars | quadrangulated primvars |
       +--------------------+-------------------------+
       <---------------------------------------------->
                    filled by computation
                          |
                          v
                         GPU

   *GPU quadrangulation

    (buffersource)
     QuadIndexBuilderComputation  (quad indices)
      |
      +--QuadrangulateTableComputation  (quadrangulate table on GPU)

    (computation)
     QuadrangulateComputationGPU  (primvar quadrangulation)

     note: QuadrangulateComputationGPU just fills quadrangulated primvars.
           the original primvars has to be transfered before the computation.

       +--------------------+
   CPU |  original primvars |
       +--------------------+
                |
                v
               GPU
                |
                v
       +--------------------+-------------------------+
   GPU |  original primvars | quadrangulated primvars |
       +--------------------+-------------------------+
                            <------------------------->
                               filled by computation

   *Computation dependencies

    Topology ---> QuadInfo --->  QuadIndices
                           --->  QuadrangulateComputation(CPU)
                           --->  QuadrangulateTable --->
                           ----------------------------> QuadrangulateComputationGPU
 */

/// \class HdSt_QuadInfoBuilderComputation
///
/// Quad info computation.
///
class HdSt_QuadInfoBuilderComputation : public HdNullBufferSource {
 public:
  HdSt_QuadInfoBuilderComputation(HdSt_MeshTopology *topology, SdfPath const &id);
  bool Resolve() override;

 protected:
  bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
};

/// \class HdSt_QuadIndexBuilderComputation
///
/// Quad indices computation CPU.
///

// Index quadrangulation generates a mapping from triangle ID to authored
// face index domain, called primitiveParams. The primitive params are
// stored alongisde topology index buffers, so that the same aggregation
// locators can be used for such an additional buffer as well. This change
// transforms index buffer from int array to int[3] array or int[4] array at
// first. Thanks to the heterogenius non-interleaved buffer aggregation ability
// in hd, we'll get this kind of buffer layout:
//
// ----+-----------+-----------+------
// ... |i0 i1 i2 i3|i4 i5 i6 i7| ...    index buffer (for quads)
// ----+-----------+-----------+------
// ... |     m0    |     m1    | ...    primitive param buffer (coarse face index)
// ----+-----------+-----------+------

class HdSt_QuadIndexBuilderComputation : public HdComputedBufferSource {
 public:
  HdSt_QuadIndexBuilderComputation(HdSt_MeshTopology *topology,
                                   HdSt_QuadInfoBuilderComputationSharedPtr const &quadInfoBuilder,
                                   SdfPath const &id);
  void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  bool Resolve() override;

  bool HasChainedBuffer() const override;
  HdBufferSourceSharedPtrVector GetChainedBuffers() const override;

 protected:
  bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
  HdSt_QuadInfoBuilderComputationSharedPtr _quadInfoBuilder;
  HdBufferSourceSharedPtr _primitiveParam;
  HdBufferSourceSharedPtr _quadsEdgeIndices;
};

/// \class HdSt_QuadrangulateTableComputation
///
/// Quadrangulate table computation (for GPU quadrangulation).
///
class HdSt_QuadrangulateTableComputation : public HdComputedBufferSource {
 public:
  HdSt_QuadrangulateTableComputation(HdSt_MeshTopology *topology,
                                     HdBufferSourceSharedPtr const &quadInfoBuilder);
  void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  bool Resolve() override;

 protected:
  bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
  HdBufferSourceSharedPtr _quadInfoBuilder;
};

/// \class HdSt_QuadrangulateComputation
///
/// CPU quadrangulation.
///
class HdSt_QuadrangulateComputation : public HdComputedBufferSource {
 public:
  HdSt_QuadrangulateComputation(HdSt_MeshTopology *topology,
                                HdBufferSourceSharedPtr const &source,
                                HdBufferSourceSharedPtr const &quadInfoBuilder,
                                SdfPath const &id);
  void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  bool Resolve() override;
  HdTupleType GetTupleType() const override;

  bool HasPreChainedBuffer() const override;
  HdBufferSourceSharedPtr GetPreChainedBuffer() const override;

 protected:
  bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
  HdBufferSourceSharedPtr _source;
  HdBufferSourceSharedPtr _quadInfoBuilder;
};

/// \class HdSt_QuadrangulateFaceVaryingComputation
///
/// CPU face-varying quadrangulation.
///
class HdSt_QuadrangulateFaceVaryingComputation : public HdComputedBufferSource {
 public:
  HdSt_QuadrangulateFaceVaryingComputation(HdSt_MeshTopology *topolgoy,
                                           HdBufferSourceSharedPtr const &source,
                                           SdfPath const &id);

  void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  bool Resolve() override;

 protected:
  bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
  HdBufferSourceSharedPtr _source;
};

/// \class HdSt_QuadrangulateComputationGPU
///
/// GPU quadrangulation.
///
class HdSt_QuadrangulateComputationGPU : public HdStComputation {
 public:
  /// This computaion doesn't generate buffer source (i.e. 2nd phase)
  HdSt_QuadrangulateComputationGPU(HdSt_MeshTopology *topology,
                                   TfToken const &sourceName,
                                   HdType dataType,
                                   SdfPath const &id);
  void Execute(HdBufferArrayRangeSharedPtr const &range,
               HdResourceRegistry *resourceRegistry) override;
  void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  int GetNumOutputElements() const override;

 private:
  SdfPath const _id;
  HdSt_MeshTopology *_topology;
  TfToken _name;
  HdType _dataType;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_QUADRANGULATE_H
