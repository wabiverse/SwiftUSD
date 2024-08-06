//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "HdSt/extComputation.h"
#include "HdSt/extCompComputedInputSource.h"
#include "HdSt/primUtils.h"
#include "HdSt/renderParam.h"
#include "HdSt/resourceRegistry.h"

#include "Hd/extComputationContext.h"
#include "Hd/perfLog.h"
#include "Hd/sceneDelegate.h"
#include "Hd/vtBufferSource.h"

#include "Hgi/capabilities.h"

#include "Arch/hash.h"

PXR_NAMESPACE_OPEN_SCOPE

HdStExtComputation::HdStExtComputation(SdfPath const &id) : HdExtComputation(id), _inputRange() {}

HdStExtComputation::~HdStExtComputation() = default;

//
// De-duplicating and sharing of ExtComputation data.
//
// This is similar to sharing of primvar data. We identify
// data by computing a hash of the sources of the data. For
// now, buffer data allocated here is read-only and is never
// mutated. If that changes, then we will have to deal with
// migrating shared data to a non-shared buffer so that it
// can be modified safely.
//
static uint64_t _ComputeSharedComputationInputId(uint64_t baseId,
                                                 HdBufferSourceSharedPtrVector const &sources)
{
  size_t inputId = baseId;
  for (HdBufferSourceSharedPtr const &bufferSource : sources) {
    size_t sourceId = bufferSource->ComputeHash();
    inputId = ArchHash64((const char *)&sourceId, sizeof(sourceId), inputId);
  }
  return inputId;
}

static HdBufferArrayRangeSharedPtr _AllocateComputationDataRange(
    HdBufferSourceSharedPtrVector &&inputs, HdStResourceRegistrySharedPtr const &resourceRegistry)
{
  HdBufferSpecVector bufferSpecs;
  HdBufferSpec::GetBufferSpecs(inputs, &bufferSpecs);

  HdBufferArrayRangeSharedPtr inputRange = resourceRegistry->AllocateShaderStorageBufferArrayRange(
      HdPrimTypeTokens->extComputation, bufferSpecs, HdBufferArrayUsageHintBitsStorage);
  resourceRegistry->AddSources(inputRange, std::move(inputs));

  return inputRange;
}

void HdStExtComputation::Sync(HdSceneDelegate *sceneDelegate,
                              HdRenderParam *renderParam,
                              HdDirtyBits *dirtyBits)
{
  HD_TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();

  HdExtComputation::_Sync(sceneDelegate, renderParam, dirtyBits);

  TF_DEBUG(HD_EXT_COMPUTATION_UPDATED)
      .Msg("HdStExtComputation::Sync for %s (dirty bits = 0x%x)\n", GetId().GetText(), *dirtyBits);

  // During Sprim sync, we only commit GPU resources when directly executing a
  // GPU computation or when aggregating inputs for a downstream computation.
  // Note: For CPU computations, we pull the inputs when we create the
  // HdStExtCompCpuComputation, which happens during Rprim sync.
  if (GetGpuKernelSource().empty() && !IsInputAggregation()) {
    return;
  }

  if (!(*dirtyBits & DirtySceneInput)) {
    // No scene inputs to sync. All other computation dirty bits (barring
    // DirtyCompInput) are sync'd in HdExtComputation::_Sync.
    return;
  }

  HdRenderIndex &renderIndex = sceneDelegate->GetRenderIndex();
  HdStResourceRegistrySharedPtr const &resourceRegistry =
      std::dynamic_pointer_cast<HdStResourceRegistry>(renderIndex.GetResourceRegistry());

  HgiCapabilities const *capabilities = resourceRegistry->GetHgi()->GetCapabilities();
  bool const doublesSupported = capabilities->IsSet(
      HgiDeviceCapabilitiesBitsShaderDoublePrecision);

  HdBufferSourceSharedPtrVector inputs;
  for (TfToken const &inputName : GetSceneInputNames()) {
    VtValue inputValue = sceneDelegate->GetExtComputationInput(GetId(), inputName);
    size_t arraySize = inputValue.IsArrayValued() ? inputValue.GetArraySize() : 1;
    HdBufferSourceSharedPtr const inputSource = std::make_shared<HdVtBufferSource>(
        inputName, inputValue, arraySize, doublesSupported);
    if (inputSource->IsValid()) {
      inputs.push_back(inputSource);
    }
    else {
      TF_WARN("Unsupported type %s for source %s in extComputation %s.",
              inputValue.GetType().GetTypeName().c_str(),
              inputName.GetText(),
              GetId().GetText());
    }
  }

  // Store the current range to know if garbage collection  is necessary.
  HdBufferArrayRangeSharedPtr const prevRange = _inputRange;

  if (!inputs.empty()) {
    if (_IsEnabledSharedExtComputationData() && IsInputAggregation()) {
      uint64_t inputId = _ComputeSharedComputationInputId(0, inputs);

      HdInstance<HdBufferArrayRangeSharedPtr> barInstance =
          resourceRegistry->RegisterExtComputationDataRange(inputId);

      if (barInstance.IsFirstInstance()) {
        // Allocate the first buffer range for this input key
        _inputRange = _AllocateComputationDataRange(std::move(inputs), resourceRegistry);
        barInstance.SetValue(_inputRange);

        TF_DEBUG(HD_SHARED_EXT_COMPUTATION_DATA)
            .Msg("Allocated shared ExtComputation buffer range: %s: %p\n",
                 GetId().GetText(),
                 (void *)_inputRange.get());
      }
      else {
        // Share the existing buffer range for this input key
        _inputRange = barInstance.GetValue();

        TF_DEBUG(HD_SHARED_EXT_COMPUTATION_DATA)
            .Msg("Reused shared ExtComputation buffer range: %s: %p\n",
                 GetId().GetText(),
                 (void *)_inputRange.get());
      }
    }
    else {
      // We're not sharing.

      // We don't yet have the ability to track dirtiness per scene input.
      // Each time DirtySceneInput is set, we pull and upload _all_ the
      // scene inputs.
      // This means that BAR migration isn't necessary, and so we avoid
      // using the Update*BufferArrayRange flavor of methods in
      // HdStResourceRegistry and handle allocation/upload manually.

      if (!_inputRange || !_inputRange->IsValid()) {
        // Allocate a new BAR if we haven't already.
        _inputRange = _AllocateComputationDataRange(std::move(inputs), resourceRegistry);
        TF_DEBUG(HD_SHARED_EXT_COMPUTATION_DATA)
            .Msg("Allocated unshared ExtComputation buffer range: %s: %p\n",
                 GetId().GetText(),
                 (void *)_inputRange.get());
      }
      else {
        HdBufferSpecVector inputSpecs;
        HdBufferSpec::GetBufferSpecs(inputs, &inputSpecs);
        HdBufferSpecVector barSpecs;
        _inputRange->GetBufferSpecs(&barSpecs);

        bool useExistingRange = HdBufferSpec::IsSubset(/*subset*/ inputSpecs,
                                                       /*superset*/ barSpecs);
        if (useExistingRange) {
          resourceRegistry->AddSources(_inputRange, std::move(inputs));

          TF_DEBUG(HD_SHARED_EXT_COMPUTATION_DATA)
              .Msg(
                  "Reused unshared ExtComputation buffer range: "
                  "%s: %p\n",
                  GetId().GetText(),
                  (void *)_inputRange.get());
        }
        else {
          _inputRange = _AllocateComputationDataRange(std::move(inputs), resourceRegistry);
          TF_DEBUG(HD_SHARED_EXT_COMPUTATION_DATA)
              .Msg(
                  "Couldn't reuse existing unshared range. Allocated a "
                  "new one.%s: %p\n",
                  GetId().GetText(),
                  (void *)_inputRange.get());
        }
      }
    }

    if (prevRange && (prevRange != _inputRange)) {
      // Make sure that we also release any stale input range data
      HdStMarkGarbageCollectionNeeded(renderParam);
    }
  }

  *dirtyBits &= ~DirtySceneInput;
}

void HdStExtComputation::Finalize(HdRenderParam *renderParam)
{
  // Release input range data.
  HdStMarkGarbageCollectionNeeded(renderParam);
}

PXR_NAMESPACE_CLOSE_SCOPE
