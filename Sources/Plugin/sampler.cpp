//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Plugin/hdEmbree/sampler.h"

PXR_NAMESPACE_OPEN_SCOPE

bool HdEmbreeBufferSampler::Sample(int index, void *value, HdTupleType dataType) const
{
  // Sanity checks: index is within the bounds of buffer,
  // and the sample type and buffer type (defined by the dataType)
  // are the same.
  if (_buffer.GetNumElements() <= (size_t)index || _buffer.GetTupleType() != dataType) {
    return false;
  }

  // Calculate the element's byte offset in the array.
  size_t elemSize = HdDataSizeOfTupleType(dataType);
  size_t offset = elemSize * index;

  // Equivalent to:
  // *static_cast<ElementType*>(value) =
  //     static_cast<ElementType*>(_buffer.GetData())[index];
  memcpy(value, static_cast<const uint8_t *>(_buffer.GetData()) + offset, elemSize);

  return true;
}

template<typename T>
static void _InterpolateImpl(
    void *out, void **samples, float *weights, size_t sampleCount, short numComponents)
{
  // This is an implementation of a general blend of samples:
  // out = sum_j { sample[j] * weights[j] }.
  // Since the vector length comes in as a parameter, and not part
  // of the type, the blend is implemented per component.
  for (short i = 0; i < numComponents; ++i) {
    static_cast<T *>(out)[i] = 0;
    for (size_t j = 0; j < sampleCount; ++j) {
      static_cast<T *>(out)[i] += static_cast<T *>(samples[j])[i] * weights[j];
    }
  }
}

/* static */ bool HdEmbreePrimvarSampler::_Interpolate(
    void *out, void **samples, float *weights, size_t sampleCount, HdTupleType dataType)
{
  // Combine maps from component type tag to C++ type, and delegates to
  // the templated _InterpolateImpl.

  // Combine number of components in the underlying type and tuple arity.
  short numComponents = HdGetComponentCount(dataType.type) * dataType.count;

  HdType componentType = HdGetComponentType(dataType.type);

  switch (componentType) {
    case HdTypeBool:
      /* This function isn't meaningful on boolean types. */
      return false;
    case HdTypeInt8:
      _InterpolateImpl<char>(out, samples, weights, sampleCount, numComponents);
    case HdTypeInt16:
      _InterpolateImpl<short>(out, samples, weights, sampleCount, numComponents);
      return true;
    case HdTypeUInt16:
      _InterpolateImpl<unsigned short>(out, samples, weights, sampleCount, numComponents);
      return true;
    case HdTypeInt32:
      _InterpolateImpl<int>(out, samples, weights, sampleCount, numComponents);
      return true;
    case HdTypeUInt32:
      _InterpolateImpl<unsigned int>(out, samples, weights, sampleCount, numComponents);
      return true;
    case HdTypeFloat:
      _InterpolateImpl<float>(out, samples, weights, sampleCount, numComponents);
      return true;
    case HdTypeDouble:
      _InterpolateImpl<double>(out, samples, weights, sampleCount, numComponents);
      return true;
    default:
      TF_CODING_ERROR("Unsupported type '%s' passed to _Interpolate",
                      TfEnum::GetName(componentType).c_str());
      return false;
  }
}

PXR_NAMESPACE_CLOSE_SCOPE
