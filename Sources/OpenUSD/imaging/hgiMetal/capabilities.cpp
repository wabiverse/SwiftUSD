//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/imaging/hgiMetal/capabilities.h"
#include "pxr/imaging/hgiMetal/hgi.h"

#include "pxr/base/arch/defines.h"
#include "pxr/base/tf/envSetting.h"

#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(HGIMETAL_ENABLE_INDIRECT_COMMAND_BUFFER, true,
                      "Enable indirect command buffers");

HgiMetalCapabilities::HgiMetalCapabilities(MTL::Device* device)
{
    _SetFlag(HgiDeviceCapabilitiesBitsConcurrentDispatch, true);

    bool const hasIntelGPU = device->lowPower();

    defaultStorageMode = MTL::ResourceStorageModeShared;
    bool unifiedMemory = false;
    bool barycentrics = false;
    bool hasAppleSilicon = false;
    bool icbSupported = false;
#if defined(ARCH_OS_IOS) && (__IPHONE_OS_VERSION_MAX_ALLOWED <= 120000)
    unifiedMemory = true;
#elif defined(ARCH_OS_OSX) && (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) || \
      defined(ARCH_OS_IOS) && (defined(__IPHONE_13_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_13_0)
    unifiedMemory = device->hasUnifiedMemory();
#else
    unifiedMemory = device->lowPower();
#endif
    // On macOS 10.15 and 11.0 the AMD drivers reported the wrong value for
    // supportsShaderBarycentricCoordinates so check both flags.
    // Also, Intel GPU drivers do not correctly support barycentrics.
    barycentrics = (device->supportsShaderBarycentricCoordinates() || device->barycentricCoordsSupported()) && !hasIntelGPU;
    hasAppleSilicon = device->hasUnifiedMemory() && !device->lowPower();
    
    if (hasAppleSilicon) {
        // Indirect command buffers supported only on
        // Apple Silicon GPUs with macOS 12.3 or later.
        icbSupported = false;
#if defined(ARCH_OS_OSX) && (defined(__MAC_12_3) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_12_3)
        icbSupported = true;
#endif /* defined(ARCH_OS_OSX) && (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) */
    } else if (hasIntelGPU) {
        // Indirect command buffers not currently supported on Intel GPUs.
        icbSupported = false;
    }

    if (!TfGetEnvSetting(HGIMETAL_ENABLE_INDIRECT_COMMAND_BUFFER)) {
        icbSupported = false;
    }

    _SetFlag(HgiDeviceCapabilitiesBitsUnifiedMemory, unifiedMemory);

    _SetFlag(HgiDeviceCapabilitiesBitsBuiltinBarycentrics, barycentrics);

    _SetFlag(HgiDeviceCapabilitiesBitsShaderDoublePrecision, false);
    
    _SetFlag(HgiDeviceCapabilitiesBitsDepthRangeMinusOnetoOne, false);

    _SetFlag(HgiDeviceCapabilitiesBitsCppShaderPadding, true);
    
    _SetFlag(HgiDeviceCapabilitiesBitsMetalTessellation, true);

    _SetFlag(HgiDeviceCapabilitiesBitsMultiDrawIndirect, true);
    
    _SetFlag(HgiDeviceCapabilitiesBitsIndirectCommandBuffers, icbSupported);

    // This is done to decide whether to use a workaround for post tess
    // patch primitive ID lookup. The bug causes the firstPatch offset
    // to be included incorrectly in the primitive ID. Our workaround
    // is to subtract it based on the base primitive offset
    // Found in MacOS 13. If confirmed fixed for MacOS 14, add a check
    // if we are on MacOS 14 or less
    //bool isMacOs13OrLess = NSProcessInfo.processInfo.operatingSystemVersion.majorVersion <= 13
    //bool requireBasePrimitiveOffset = hasAppleSilicon && isMacOs13OrLess;
    bool requiresBasePrimitiveOffset = hasAppleSilicon || hasIntelGPU;
    _SetFlag(HgiDeviceCapabilitiesBitsBasePrimitiveOffset,
             requiresBasePrimitiveOffset);

    // Intel GPU drivers do not correctly support primitive_id.
    if (hasIntelGPU) {
        _SetFlag(HgiDeviceCapabilitiesBitsPrimitiveIdEmulation, true);
    }

    if (!unifiedMemory) {
        defaultStorageMode = MTL::ResourceStorageModeManaged;
    }

    _maxUniformBlockSize          = 64 * 1024;
    _maxShaderStorageBlockSize    = 1 * 1024 * 1024 * 1024;
    _uniformBufferOffsetAlignment = 16;
    _maxClipDistances             = 8;
    _pageSizeAlignment            = 4096;

    // Apple Silicon only support memory barriers between vertex stages after
    // macOS 12.3.
    hasVertexMemoryBarrier = !hasAppleSilicon;
#if defined(ARCH_OS_OSX) && (defined(__MAC_12_3) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_12_3)
    hasVertexMemoryBarrier = true;
#endif /* defined(ARCH_OS_OSX) && (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) */

    // Vega GPUs require a fix to the indirect draw before macOS 12.2
    requiresIndirectDrawFix = false;
#if defined(ARCH_OS_OSX) && (__MAC_OS_X_VERSION_MAX_ALLOWED <= 120200)
    if (device->name()->rangeOfString(NS::String::string("Vega", NS::UTF8StringEncoding), 
                                      NS::CaseInsensitiveSearch).location != NS::NotFound) {
        requiresIndirectDrawFix = true;
    }
#endif /* defined(ARCH_OS_OSX) && (__MAC_OS_X_VERSION_MAX_ALLOWED <= 120200) */

    useParallelEncoder = true;
}

HgiMetalCapabilities::~HgiMetalCapabilities() = default;

int
HgiMetalCapabilities::GetAPIVersion() const
{
#if defined(ARCH_OS_OSX) && (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) || \
    defined(ARCH_OS_IOS) && (defined(__IPHONE_13_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_13_0)
        return APIVersion_Metal3_0;
#elif defined(ARCH_OS_OSX) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= 101300) || \
      defined(ARCH_OS_IOS) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= 110000)
        return APIVersion_Metal2_0;
#else
        return APIVersion_Metal1_0;
#endif
}

int
HgiMetalCapabilities::GetShaderVersion() const
{
    // Note: This is not the Metal Shader Language version. It is provided for
    // compatibility with code that is asking for the GLSL version.
    return 450;
}

PXR_NAMESPACE_CLOSE_SCOPE
