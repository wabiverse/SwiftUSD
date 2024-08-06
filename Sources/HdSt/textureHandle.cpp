//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/textureHandle.h"

#include "HdSt/textureHandleRegistry.h"

#include "HdSt/resourceBinder.h"
#include "HdSt/resourceRegistry.h"
#include "HdSt/samplerObject.h"
#include "HdSt/samplerObjectRegistry.h"
#include "HdSt/textureObjectRegistry.h"

#include "Hgi/capabilities.h"

#include "Tf/diagnostic.h"

PXR_NAMESPACE_OPEN_SCOPE

HdStTextureHandle::HdStTextureHandle(HdStTextureObjectSharedPtr const &textureObject,
                                     const HdSamplerParameters &samplerParams,
                                     const size_t memoryRequest,
                                     HdStShaderCodePtr const &shaderCode,
                                     HdSt_TextureHandleRegistry *textureHandleRegistry)
    : _textureObject(textureObject),
      _samplerParams(samplerParams),
      _memoryRequest(memoryRequest),
      _shaderCode(shaderCode),
      _textureHandleRegistry(textureHandleRegistry)
{
}

HdStTextureHandle::~HdStTextureHandle()
{
  if (TF_VERIFY(_textureHandleRegistry)) {
    // The target memory of the texture might change, so mark dirty.
    _textureHandleRegistry->MarkDirty(_textureObject);
    // The shader needs to be updated after it dropped a texture
    // handle (i.e., because it re-allocated the shader bar after
    // dropping a texture).
    _textureHandleRegistry->MarkDirty(_shaderCode);
    _textureHandleRegistry->MarkSamplerGarbageCollectionNeeded();
  }
}

void HdStTextureHandle::ReallocateSamplerIfNecessary()
{
  if (_samplerObject) {
    if (!UseBindlessHandles()) {
      // There is no setter for sampler parameters,
      // so we only need to create a sampler once...
      return;
    }

    // ... except that the sampler object has a texture sampler
    // handle that needs to be re-created if the underlying texture
    // changes, so continue.

    if (TF_VERIFY(_textureHandleRegistry)) {
      _textureHandleRegistry->MarkSamplerGarbageCollectionNeeded();
    }

    _samplerObject = nullptr;
  }

  // Create sampler object through registry.
  HdSt_SamplerObjectRegistry *const samplerObjectRegistry =
      _textureHandleRegistry->GetSamplerObjectRegistry();

  _samplerObject = samplerObjectRegistry->AllocateSampler(_textureObject, _samplerParams);
}

bool HdStTextureHandle::UseBindlessHandles() const
{
  if (TF_VERIFY(_textureHandleRegistry)) {
    return _textureHandleRegistry->GetTextureObjectRegistry()
        ->GetResourceRegistry()
        ->GetHgi()
        ->GetCapabilities()
        ->IsSet(HgiDeviceCapabilitiesBitsBindlessTextures);
  }
  return false;
}

PXR_NAMESPACE_CLOSE_SCOPE
