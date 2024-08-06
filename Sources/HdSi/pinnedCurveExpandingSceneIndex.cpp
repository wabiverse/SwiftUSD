//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSi/pinnedCurveExpandingSceneIndex.h"

#include "Hd/basisCurvesSchema.h"
#include "Hd/basisCurvesTopologySchema.h"
#include "Hd/dataSource.h"
#include "Hd/dataSourceTypeDefs.h"
#include "Hd/geomSubsetSchema.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/primvarsSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneIndex.h"
#include "Hd/tokens.h"

#include "Tf/diagnostic.h"
#include "Tf/token.h"
#include "Vt/array.h"
#include "Vt/typeHeaders.h"
#include "Vt/types.h"
#include "Vt/value.h"
#include "Vt/visitValue.h"

#include <vector>

#define USE_PARALLEL_EXPANSION 0

// TODO: This scene index doesn't account for time varying curve topology

PXR_NAMESPACE_OPEN_SCOPE

namespace {

// Returns the expanded value that is computed by replicating the first and last
// values `numRepeat` times per curve. This is used for expanding index buffers,
// vertex primvars and possibly varying primvars of pinned curves.
// See relevant comments in _ComputeExpandedVaryingValue below.
template<typename T>
VtArray<T> _ComputeExpandedValue(const VtArray<T> &input,
                                 const VtIntArray &perCurveCounts,
                                 const size_t numRepeat,
                                 const TfToken &name)
{
  // Build cumulative sum arrays to help index into the authored and expanded
  // values per curve.
  const size_t numCurves = perCurveCounts.size();
  VtIntArray authoredStartIndices(numCurves);
  size_t idx = 0;
  size_t authoredSum = 0;
  for (int const &vc : perCurveCounts) {
    authoredStartIndices[idx++] = authoredSum;
    authoredSum += size_t(vc);
  }

  if (input.size() != authoredSum) {
    TF_WARN(
        "Data for %s does not match expected size "
        "(got %zu, expected %zu)",
        name.GetText(),
        input.size(),
        authoredSum);
    return input;
  }

  const size_t outputSize = input.size() + 2 * numRepeat * numCurves;
  VtArray<T> output(outputSize);

  const auto workLambda = [&](const size_t beginIdx, const size_t endIdx) {
    for (size_t curveIdx = beginIdx; curveIdx < endIdx; ++curveIdx) {
      // input index range [start, end)
      const size_t inputStartIdx = authoredStartIndices[curveIdx];
      const size_t inputEndIdx = inputStartIdx + perCurveCounts[curveIdx];

      const size_t outStartIdx = inputStartIdx + 2 * numRepeat * curveIdx;
      typename VtArray<T>::iterator outIt = output.begin() + outStartIdx;

      // Repeat the first value as necessary.
      outIt = std::fill_n(outIt, numRepeat, input[inputStartIdx]);

      // Copy authored data.
      outIt = std::copy(input.cbegin() + inputStartIdx, input.cbegin() + inputEndIdx, outIt);

      // Repeat the last value as necessary.
      outIt = std::fill_n(outIt, numRepeat, input[inputEndIdx - 1]);
    }
  };

// Dirty data in Hydra is sync'd in parallel, so whether we benefit from
// the additional parallelism below needs to be tested.
#if USE_PARALLEL_EXPANSION
  // XXX Using a simple untested heuristic to divvy up the work.
  constexpr size_t numCurvesPerThread = 25;
  WorkParallelForN(numCurves, workLambda, numCurvesPerThread);
#else
  workLambda(0, numCurves);
#endif

  return output;
}

// Returns the expanded value that is computed by replicating the first and last
// values `numRepeat` times per curve when the vertex count is 4 or more, and
// repeating the authored varying values if/as necessary otherwise.
//
template<typename T>
VtArray<T> _ComputeExpandedVaryingValue(const VtArray<T> &input,
                                        const VtIntArray &curveVaryingCounts,
                                        const VtIntArray &curveVertexCounts,
                                        const size_t numRepeat,
                                        const TfToken &name)
{
  if (!TF_VERIFY(curveVaryingCounts.size() == curveVertexCounts.size())) {
    return input;
  }

  // Build cumulative sum arrays to help index into the authored and expanded
  // varying values per curve.
  const size_t numCurves = curveVaryingCounts.size();
  VtIntArray authoredStartIndices(numCurves);
  VtIntArray expandedStartIndices(numCurves);
  size_t authoredSum = 0;
  size_t expandedSum = 0;

  for (size_t idx = 0; idx < numCurves; idx++) {
    const int numVarying = curveVaryingCounts[idx];
    const int numVertices = curveVertexCounts[idx];

    authoredStartIndices[idx] = authoredSum;
    authoredSum += size_t(numVarying);

    expandedStartIndices[idx] = expandedSum;

    if (numVertices >= 4) {
      expandedSum += size_t(numVarying) + 2 * numRepeat;
    }
    else if (numVertices >= 2) {  // i.e., 2 or 3

      const size_t numExpandedVertices = numVertices + 2 * numRepeat;
      const size_t nSegs = numExpandedVertices - 3;
      const size_t nVarying = nSegs + 1;
      expandedSum += nVarying;
    }
  }

  if (input.size() != authoredSum) {
    TF_WARN(
        "Data for %s does not match expected size "
        "(got %zu, expected %zu)",
        name.GetText(),
        input.size(),
        authoredSum);
    return input;
  }

  VtArray<T> output(expandedSum);

  const auto workLambda = [&](const size_t beginIdx, const size_t endIdx) {
    for (size_t curveIdx = beginIdx; curveIdx < endIdx; ++curveIdx) {
      // input index range [start, end)
      const size_t inputStartIdx = authoredStartIndices[curveIdx];
      const size_t outStartIdx = expandedStartIndices[curveIdx];

      const size_t nextIdx = curveIdx + 1;

      const size_t inputEndIdx = (nextIdx != endIdx) ? authoredStartIndices[nextIdx] : authoredSum;
      const size_t outEndIdx = (nextIdx != endIdx) ? expandedStartIndices[nextIdx] : expandedSum;

      const size_t inputSize = inputEndIdx - inputStartIdx;
      const size_t outputSize = outEndIdx - outStartIdx;
      const size_t padding = outputSize - inputSize;

      typename VtArray<T>::iterator outIt = output.begin() + outStartIdx;

      if (padding == 2 * numRepeat) {
        // Repeat the first value as necessary.
        outIt = std::fill_n(outIt, numRepeat, input[inputStartIdx]);

        // Copy authored data.
        outIt = std::copy(input.cbegin() + inputStartIdx, input.cbegin() + inputEndIdx, outIt);

        // Repeat the last value as necessary.
        outIt = std::fill_n(outIt, numRepeat, input[inputEndIdx - 1]);
      }
      else {
        // curveVertexCount is 2 or 3 requiring special handling for
        // varying primvar expansion. The possible scenarios are:
        //        |           AUTHORED       ||         EXPANDED
        // repeat | vtx count | varyingCount || vtx count | varyingCount
        // -------|--------------------------||-------------------------
        //    1   |     2     |       2      ||     4     |      2
        //    1   |     3     |       2      ||     5     |      3
        //    2   |     2     |       2      ||     6     |      4
        //    2   |     3     |       2      ||     7     |      5

        // Repeat the first value *if* necessary.
        outIt = std::fill_n(outIt, (padding + 1) / 2, input[inputStartIdx]);

        // Copy authored data.
        outIt = std::copy(input.cbegin() + inputStartIdx, input.cbegin() + inputEndIdx, outIt);

        // Repeat the last value *if* necessary.
        outIt = std::fill_n(outIt, padding - (padding + 1) / 2, input[inputEndIdx - 1]);
      }
    }
  };

// Dirty data in Hydra is sync'd in parallel, so whether we benefit from
// the additional parallelism below needs to be tested.
#if USE_PARALLEL_EXPANSION
  // XXX Using a simple untested heuristic to divvy up the work.
  constexpr size_t numCurvesPerThread = 25;
  WorkParallelForN(numCurves, workLambda, numCurvesPerThread);
#else
  workLambda(0, numCurves);
#endif

  return output;
}

template<typename T> T _SafeGetTypedValue(typename HdTypedSampledDataSource<T>::Handle ds)
{
  if (ds) {
    return ds->GetTypedValue(0.0f);
  }
  return T();
}

// A fallback container data source for use when an invalid one is provided
// when constructing the pinned curve data source overrides below.
class _EmptyContainerDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_EmptyContainerDataSource);

  TfTokenVector GetNames() override
  {
    return {};
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    return nullptr;
  }
};

// Typed sampled data source override that does the actual primvar expansion
template<typename T>
class _ExpandedDataSource final : public HdTypedSampledDataSource<VtArray<T>> {
 public:
  using Time = HdSampledDataSource::Time;

  HD_DECLARE_DATASOURCE_ABSTRACT(_ExpandedDataSource<T>);

  /// input: the original data source
  _ExpandedDataSource(const HdSampledDataSourceHandle &input,
                      const TfToken &primvarName,
                      const VtIntArray &perCurveCounts,
                      const VtIntArray &curveVertexCounts,
                      const size_t numExtraEnds,
                      const bool expandConditionally)
      : _input(input),
        _primvarName(primvarName),
        _perCurveCounts(perCurveCounts),
        _curveVertexCounts(curveVertexCounts),
        _numExtraEnds(numExtraEnds),
        _expandConditionally(expandConditionally)
  {
  }

  VtValue GetValue(Time shutterOffset) override
  {
    return VtValue(GetTypedValue(shutterOffset));
  }

  bool GetContributingSampleTimesForInterval(Time startTime,
                                             Time endTime,
                                             std::vector<Time> *outSampleTimes) override
  {
    return _input->GetContributingSampleTimesForInterval(startTime, endTime, outSampleTimes);
  }

  VtArray<T> GetTypedValue(Time shutterOffset) override
  {
    const VtValue &v = _input->GetValue(shutterOffset);
    if (v.IsHolding<VtArray<T>>()) {
      const VtArray<T> array = v.UncheckedGet<VtArray<T>>();
      if (array.empty()) {
        return array;
      }

      if (_expandConditionally) {
        return _ComputeExpandedVaryingValue<T>(
            array, _perCurveCounts, _curveVertexCounts, _numExtraEnds, _primvarName);
      }

      return _ComputeExpandedValue<T>(array, _perCurveCounts, _numExtraEnds, _primvarName);
    }
    return VtArray<T>();
  }

  static typename _ExpandedDataSource<T>::Handle New(const HdSampledDataSourceHandle &input,
                                                     const TfToken &primvarName,
                                                     const VtIntArray &perCurveCounts,
                                                     const VtIntArray &curveVertexCounts,
                                                     const size_t numExtraEnds,
                                                     const bool expandConditionally)
  {
    return _ExpandedDataSource<T>::Handle(new _ExpandedDataSource<T>(
        input, primvarName, perCurveCounts, curveVertexCounts, numExtraEnds, expandConditionally));
  }

 private:
  HdSampledDataSourceHandle _input;
  const TfToken _primvarName;
  const VtIntArray _perCurveCounts;
  const VtIntArray _curveVertexCounts;
  size_t _numExtraEnds;
  bool _expandConditionally;
};

// Visitor that expands a given value if it holds an array and returns
// the value otherwise.
struct _Visitor {
  HdSampledDataSourceHandle _input;
  const TfToken _primvarName;
  const VtIntArray &_perCurveCounts;
  const VtIntArray &_curveVertexCounts;
  size_t _numExtraEnds;
  bool _expandConditionally;

  template<typename T> HdDataSourceBaseHandle operator()(const VtArray<T> &array)
  {
    return _ExpandedDataSource<T>::New(_input,
                                       _primvarName,
                                       _perCurveCounts,
                                       _curveVertexCounts,
                                       _numExtraEnds,
                                       _expandConditionally);
  }

  HdDataSourceBaseHandle operator()(const VtValue &value)
  {
    TF_WARN("Unsupported type for expansion %s", value.GetTypeName().c_str());
    return _input;
  }
};

// Primvar schema data source override that:
//  - expands vertex primvars for non-indexed curves (not to be confused with
//    indexed primvars mentioned below).
//  - expands varying primvars.
//  - expands indices for indexed primvars with vertex & varying interp.
class _PrimvarDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_PrimvarDataSource);

  _PrimvarDataSource(const HdContainerDataSourceHandle &input,
                     const TfToken &primvarName,
                     const VtIntArray &curveVertexCounts,
                     const size_t numExtraEnds,
                     bool hasCurveIndices)
      : _input(input),
        _primvarName(primvarName),
        _curveVertexCounts(curveVertexCounts),
        _numExtraEnds(numExtraEnds),
        _hasCurveIndices(hasCurveIndices),
        _expandVaryingConditionally(false)
  {
    if (ARCH_UNLIKELY(!_input)) {
      TF_CODING_ERROR("Invalid container data source input provided.");
      _input = _EmptyContainerDataSource::New();
    }
    // _curveVaryingCounts is initialized when necessary in Get(..).
  }

  TfTokenVector GetNames() override
  {
    return _input->GetNames();
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    HdDataSourceBaseHandle result = _input->Get(name);
    if (!result) {
      return nullptr;
    }

    if (name == HdPrimvarSchemaTokens->primvarValue || name == HdPrimvarSchemaTokens->indices) {
      HdPrimvarSchema pvs(_input);
      const TfToken interp = _SafeGetTypedValue<TfToken>(pvs.GetInterpolation());

      if (interp != HdPrimvarSchemaTokens->vertex && interp != HdPrimvarSchemaTokens->varying) {
        // constant and uniform interp don't need expansion.
        // faceVarying isn't relevant for curves.
        return result;
      }

      // For indexed primvars, only the indices needs to be expanded.
      // The indexedPrimvarValue doesn't.
      if (name == HdPrimvarSchemaTokens->primvarValue && _hasCurveIndices &&
          interp == HdPrimvarSchemaTokens->vertex)
      {
        // Don't need to expand the primvar since the expanded curve
        // index buffer takes care of it.
        return result;
      }

      HdSampledDataSourceHandle sds = HdSampledDataSource::Cast(result);
      if (!sds) {
        return result;
      }

      if (interp == HdPrimvarSchemaTokens->varying && _curveVaryingCounts.empty()) {
        _InitCurveVaryingCounts();
      }

      const VtIntArray &perCurveCounts = (interp == HdPrimvarSchemaTokens->varying) ?
                                             _curveVaryingCounts :
                                             _curveVertexCounts;

      const bool expandConditionally = interp == HdPrimvarSchemaTokens->varying &&
                                       _expandVaryingConditionally;

      return VtVisitValue(sds->GetValue(0.0f),
                          _Visitor{sds,
                                   _primvarName,
                                   perCurveCounts,
                                   _curveVertexCounts,
                                   _numExtraEnds,
                                   expandConditionally});
    }

    return result;
  }

 private:
  // Compute the expected number of authored varying primvars per curve.
  // Note that we still compute it as though it were non-periodic.
  void _InitCurveVaryingCounts()
  {
    const size_t numCurves = _curveVertexCounts.size();
    _curveVaryingCounts.resize(numCurves);
    for (size_t cId = 0; cId < numCurves; cId++) {
      const int &vertexCount = _curveVertexCounts[cId];
      int &varyingCount = _curveVaryingCounts[cId];

      if (vertexCount < 2) {
        varyingCount = 0;
        continue;
      }
      if (vertexCount < 4) {
        _expandVaryingConditionally = true;
      }

      // Note: We treat cv = 2 or 3 as a single segment requiring 2
      // authored varying values.
      const size_t nSegs = std::max(_curveVertexCounts[cId] - 4, 0) + 1;
      const size_t nVarying = nSegs + 1;
      varyingCount = nVarying;
    }
  }

 private:
  HdContainerDataSourceHandle _input;
  const TfToken _primvarName;
  const VtIntArray _curveVertexCounts;
  size_t _numExtraEnds;
  bool _hasCurveIndices;
  VtIntArray _curveVaryingCounts;
  bool _expandVaryingConditionally;
};

// Primvars schema data source override.
//
class _PrimvarsDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_PrimvarsDataSource);

  _PrimvarsDataSource(const HdContainerDataSourceHandle &input,
                      const VtIntArray &curveVertexCounts,
                      const size_t &numExtraEnds,
                      bool hasCurveIndices)
      : _input(input),
        _curveVertexCounts(curveVertexCounts),
        _numExtraEnds(numExtraEnds),
        _hasCurveIndices(hasCurveIndices)
  {
    if (ARCH_UNLIKELY(!_input)) {
      TF_CODING_ERROR("Invalid container data source input provided.");
      _input = _EmptyContainerDataSource::New();
    }
  }

  TfTokenVector GetNames() override
  {
    return _input->GetNames();
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    HdDataSourceBaseHandle result = _input->Get(name);
    if (result) {
      if (HdContainerDataSourceHandle pc = HdContainerDataSource::Cast(result)) {
        return _PrimvarDataSource::New(
            pc, name, _curveVertexCounts, _numExtraEnds, _hasCurveIndices);
      }
    }

    return result;
  }

 private:
  HdContainerDataSourceHandle _input;
  const VtIntArray _curveVertexCounts;
  size_t _numExtraEnds;
  bool _hasCurveIndices;
};

// Basis curves topology schema data source override.
//
class _TopologyDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_TopologyDataSource);

  _TopologyDataSource(const HdContainerDataSourceHandle &input,
                      const VtIntArray &curveVertexCounts,
                      const size_t &numExtraEnds)
      : _input(input), _curveVertexCounts(curveVertexCounts), _numExtraEnds(numExtraEnds)
  {
    if (ARCH_UNLIKELY(!_input)) {
      TF_CODING_ERROR("Invalid container data source input provided.");
      _input = _EmptyContainerDataSource::New();
    }
  }

  TfTokenVector GetNames() override
  {
    return _input->GetNames();
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    HdBasisCurvesTopologySchema ts = HdBasisCurvesTopologySchema(_input);
    HdDataSourceBaseHandle result = _input->Get(name);

    if (name == HdBasisCurvesTopologySchemaTokens->curveVertexCounts) {
      VtIntArray curveVertexCounts = _curveVertexCounts;
      for (int &count : curveVertexCounts) {
        count += 2 * _numExtraEnds;  // added to beginning and end...
      }

      return HdRetainedTypedSampledDataSource<VtIntArray>::New(curveVertexCounts);
    }

    if (name == HdBasisCurvesTopologySchemaTokens->curveIndices) {
      VtIntArray curveIndices = _SafeGetTypedValue<VtIntArray>(ts.GetCurveIndices());

      if (!curveIndices.empty()) {
        // Curve indices can be expanded just like we'd expand a
        // vertex primvar by replicating the first and last values as
        // necessary.
        VtIntArray vExpanded = _ComputeExpandedValue<int>(
            curveIndices,
            _curveVertexCounts,
            _numExtraEnds,
            HdBasisCurvesTopologySchemaTokens->curveIndices);

        return HdRetainedTypedSampledDataSource<VtIntArray>::New(vExpanded);
      }
    }

    if (name == HdBasisCurvesTopologySchemaTokens->wrap) {
      // Override to nonPeriodic.
      return HdRetainedTypedSampledDataSource<TfToken>::New(HdTokens->nonperiodic);
    }

    return result;
  }

 private:
  HdContainerDataSourceHandle _input;
  const VtIntArray _curveVertexCounts;
  size_t _numExtraEnds;
};

// Basis curves schema data source override.
//
class _BasisCurvesDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_BasisCurvesDataSource);

  _BasisCurvesDataSource(const HdContainerDataSourceHandle &input,
                         const VtIntArray &curveVertexCounts,
                         const size_t &numExtraEnds)
      : _input(input), _curveVertexCounts(curveVertexCounts), _numExtraEnds(numExtraEnds)
  {
    if (ARCH_UNLIKELY(!_input)) {
      TF_CODING_ERROR("Invalid container data source input provided.");
      _input = _EmptyContainerDataSource::New();
    }
  }

  TfTokenVector GetNames() override
  {
    return _input->GetNames();
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    HdDataSourceBaseHandle result = _input->Get(name);
    if (name == HdBasisCurvesSchemaTokens->topology) {
      if (HdContainerDataSourceHandle tc = HdContainerDataSource::Cast(result)) {
        return _TopologyDataSource::New(tc, _curveVertexCounts, _numExtraEnds);
      }
    }
    return result;
  }

 private:
  HdContainerDataSourceHandle _input;
  const VtIntArray _curveVertexCounts;
  size_t _numExtraEnds;
};

// Prim level data source override.
// The basis curves prim container has the following hierarchy:
// prim
//     basisCurvesSchema
//         topologySchema
//             curveVertexCounts
//             curveIndices
//             wrap
//             ...
//     primvarsSchema
//         primvarSchema[]
//             primvarValue
//             indexedPrimvarValue
//
class _PrimDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_PrimDataSource);

  _PrimDataSource(const HdContainerDataSourceHandle &input) : _input(input)
  {
    if (ARCH_UNLIKELY(!_input)) {
      TF_CODING_ERROR("Invalid container data source input provided.");
      _input = _EmptyContainerDataSource::New();
    }
  }

  TfTokenVector GetNames() override
  {
    return _input->GetNames();
  }

  HdDataSourceBaseHandle Get(const TfToken &name) override
  {
    HdDataSourceBaseHandle result = _input->Get(name);
    if (!result) {
      return HdDataSourceBaseHandle();
    }
    if (name != HdBasisCurvesSchemaTokens->basisCurves && name != HdPrimvarsSchemaTokens->primvars)
    {
      return result;
    }
    HdBasisCurvesSchema bcs = HdBasisCurvesSchema::GetFromParent(_input);
    if (!bcs) {
      return result;
    }
    HdBasisCurvesTopologySchema ts = bcs.GetTopology();
    if (!ts) {
      return result;
    }

    // TODO: Avoid sampling sampled sources here!
    const TfToken wrap = _SafeGetTypedValue<TfToken>(ts.GetWrap());
    const TfToken basis = _SafeGetTypedValue<TfToken>(ts.GetBasis());

    if (wrap == HdTokens->pinned && (basis == HdTokens->bspline || basis == HdTokens->catmullRom ||
                                     basis == HdTokens->centripetalCatmullRom))
    {

      // Add 2 additional end points for bspline and
      // 1 for catmullRom|centripetalCatmullRom.
      const size_t numExtraEnds = (basis == HdTokens->bspline) ? 2 : 1;

      // Need to cache the per-curve vertex counts since the
      // expansion is per-curve.
      const VtIntArray curveVertexCounts = _SafeGetTypedValue<VtIntArray>(
          ts.GetCurveVertexCounts());

      if (name == HdBasisCurvesSchemaTokens->basisCurves) {
        if (HdContainerDataSourceHandle bcc = HdContainerDataSource::Cast(result)) {
          return _BasisCurvesDataSource::New(bcc, curveVertexCounts, numExtraEnds);
        }
      }

      if (name == HdPrimvarsSchemaTokens->primvars) {
        // If we have authored curve indices, we can avoid expanding
        // vertex primvars by expanding the curve indices instead.
        // Note that varying primvars would still need to be
        // expanded due to the additional curve segments.
        VtIntArray curveIndices = _SafeGetTypedValue<VtIntArray>(ts.GetCurveIndices());

        if (HdContainerDataSourceHandle pc = HdContainerDataSource::Cast(result)) {
          return _PrimvarsDataSource::New(
              pc, curveVertexCounts, numExtraEnds, !curveIndices.empty());
        }
      }
    }
    return result;
  }

 private:
  HdContainerDataSourceHandle _input;
};

class _SubsetIndicesDataSource : public HdIntArrayDataSource {
 public:
  HD_DECLARE_DATASOURCE(_SubsetIndicesDataSource);

  VtValue GetValue(Time shutterOffset) override
  {
    return VtValue(GetTypedValue(shutterOffset));
  }

  VtIntArray GetTypedValue(Time shutterOffset) override
  {
    if (_typeSource->GetTypedValue(shutterOffset) == HdGeomSubsetSchemaTokens->typePointSet) {
      // TODO: Remap geomsubset indices accounting for the additional
      //       curve points.
    }
    return _dataSource->GetTypedValue(shutterOffset);
  }

  bool GetContributingSampleTimesForInterval(
      Time startTime,
      Time endTime,
      std::vector<HdSampledDataSource::Time> *outSampleTimes) override
  {
    std::vector<HdSampledDataSourceHandle> sources{_dataSource, _typeSource};
    const auto &topoSchema = HdBasisCurvesTopologySchema::GetFromParent(_parentSource);
    if (topoSchema) {
      sources.push_back(topoSchema.GetWrap());
      sources.push_back(topoSchema.GetBasis());
      sources.push_back(topoSchema.GetCurveVertexCounts());
    }
    return HdGetMergedContributingSampleTimesForInterval(
        sources.size(), sources.data(), startTime, endTime, outSampleTimes);
  }

 private:
  _SubsetIndicesDataSource(const HdIntArrayDataSourceHandle &dataSource,
                           const HdTokenDataSourceHandle &typeSource,
                           const HdContainerDataSourceHandle &parentSource)
      : _dataSource(dataSource), _typeSource(typeSource), _parentSource(parentSource)
  {
    TF_VERIFY(dataSource);
    TF_VERIFY(typeSource);
    TF_VERIFY(parentSource);
  }

  HdIntArrayDataSourceHandle _dataSource;
  HdTokenDataSourceHandle _typeSource;
  HdContainerDataSourceHandle _parentSource;
};

HD_DECLARE_DATASOURCE_HANDLES(_SubsetIndicesDataSource);

}  // namespace

////////////////////////////////////////////////////////////////////////////////

/* static */
HdsiPinnedCurveExpandingSceneIndexRefPtr HdsiPinnedCurveExpandingSceneIndex::New(
    const HdSceneIndexBaseRefPtr &inputSceneIndex)
{
  return TfCreateRefPtr(new HdsiPinnedCurveExpandingSceneIndex(inputSceneIndex));
}

HdsiPinnedCurveExpandingSceneIndex::HdsiPinnedCurveExpandingSceneIndex(
    const HdSceneIndexBaseRefPtr &inputSceneIndex)
    : HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
{
}

HdSceneIndexPrim HdsiPinnedCurveExpandingSceneIndex::GetPrim(const SdfPath &primPath) const
{
  HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(primPath);
  if (!prim.dataSource) {
    return prim;
  }

  // Override the prim data source for basis curves.
  if (prim.primType == HdPrimTypeTokens->basisCurves) {
    prim.dataSource = _PrimDataSource::New(prim.dataSource);
  }

  // Override the prim data source for geom subsets if parent is basis curves
  if (prim.primType == HdPrimTypeTokens->geomSubset) {
    const HdSceneIndexPrim parentPrim = _GetInputSceneIndex()->GetPrim(primPath.GetParentPath());
    if (parentPrim.primType == HdPrimTypeTokens->basisCurves && parentPrim.dataSource) {

      // overlay indices
      // XXX: When basis curves support visible subsets,
      //      add support for subset primvars.
      prim.dataSource = HdOverlayContainerDataSource::New(
          HdRetainedContainerDataSource::New(
              HdGeomSubsetSchemaTokens->indices,
              _SubsetIndicesDataSource::New(
                  HdIntArrayDataSource::Cast(
                      prim.dataSource->Get(HdGeomSubsetSchemaTokens->indices)),
                  HdTokenDataSource::Cast(prim.dataSource->Get(HdGeomSubsetSchemaTokens->type)),
                  parentPrim.dataSource)),
          prim.dataSource);
    }
  }

  return prim;
}

SdfPathVector HdsiPinnedCurveExpandingSceneIndex::GetChildPrimPaths(const SdfPath &primPath) const
{
  if (auto input = _GetInputSceneIndex()) {
    return input->GetChildPrimPaths(primPath);
  }

  return {};
}

void HdsiPinnedCurveExpandingSceneIndex::_PrimsAdded(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::AddedPrimEntries &entries)
{
  _SendPrimsAdded(entries);
}

void HdsiPinnedCurveExpandingSceneIndex::_PrimsRemoved(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::RemovedPrimEntries &entries)
{
  _SendPrimsRemoved(entries);
}

void HdsiPinnedCurveExpandingSceneIndex::_PrimsDirtied(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::DirtiedPrimEntries &entries)
{
  _SendPrimsDirtied(entries);
}

PXR_NAMESPACE_CLOSE_SCOPE
