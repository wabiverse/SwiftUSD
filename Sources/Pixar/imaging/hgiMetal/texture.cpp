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
#include <Metal/Metal.hpp>

#include "pxr/imaging/hgiMetal/buffer.h"
#include "pxr/imaging/hgiMetal/capabilities.h"
#include "pxr/imaging/hgiMetal/conversions.h"
#include "pxr/imaging/hgiMetal/diagnostic.h"
#include "pxr/imaging/hgiMetal/hgi.h"
#include "pxr/imaging/hgiMetal/texture.h"


PXR_NAMESPACE_OPEN_SCOPE

HgiMetalTexture::HgiMetalTexture(HgiMetal *hgi, HgiTextureDesc const & desc)
    : HgiTexture(desc)
    , _textureId(nil)
{
    MTL::ResourceOptions resourceOptions = MTL::ResourceStorageModePrivate;
    MTL::TextureUsage usage = MTL::TextureUsageShaderRead;

    MTL::PixelFormat mtlFormat = HgiMetalConversions::GetPixelFormat(desc.format, desc.usage);

    if (desc.usage &
        (HgiTextureUsageBitsColorTarget | HgiTextureUsageBitsDepthTarget)) {
        usage |= MTL::TextureUsageRenderTarget;
    }

    if (desc.usage & HgiTextureUsageBitsShaderWrite) {
        usage |= MTL::TextureUsageShaderWrite;
    }

    const size_t width = desc.dimensions[0];
    const size_t height = desc.dimensions[1];
    const size_t depth = desc.dimensions[2];

    MTL::TextureDescriptor* texDesc;

    texDesc = MTL::TextureDescriptor::texture2DDescriptor(mtlFormat, width, height, false);
    
    texDesc->setMipmapLevelCount(desc.mipLevels);
    texDesc->setArrayLength(desc.layerCount);
    texDesc->setResourceOptions(resourceOptions);
    texDesc->setUsage(usage);

#if (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) \
    || __IPHONE_OS_VERSION_MAX_ALLOWED >= 130000
        size_t numChannels = HgiGetComponentCount(desc.format);

        if (usage == MTL::TextureUsageShaderRead && numChannels == 1) {
            MTL::TextureSwizzle s = HgiMetalConversions::GetComponentSwizzle(desc.componentMapping.r);
            texDesc->setSwizzle(MTL::TextureSwizzleChannels{s, s, s, s});
        }
        else {
            texDesc->setSwizzle(MTL::TextureSwizzleChannels{
              HgiMetalConversions::GetComponentSwizzle(desc.componentMapping.r),
              HgiMetalConversions::GetComponentSwizzle(desc.componentMapping.g),
              HgiMetalConversions::GetComponentSwizzle(desc.componentMapping.b),
              HgiMetalConversions::GetComponentSwizzle(desc.componentMapping.a)
            });
        }
#endif

    if (desc.type == HgiTextureType3D) {
        texDesc->setDepth(depth);
        texDesc->setTextureType(MTL::TextureType::TextureType3D);
    } else if (desc.type == HgiTextureType2DArray) {
        texDesc->setTextureType(MTL::TextureType::TextureType2DArray);
    } else if (desc.type == HgiTextureType1D) {
        texDesc->setTextureType(MTL::TextureType::TextureType1D);
    } else if (desc.type == HgiTextureType1DArray) {
        texDesc->setTextureType(MTL::TextureType::TextureType1DArray);
    }

    if (desc.sampleCount > 1) {
        texDesc->setSampleCount(desc.sampleCount);
        texDesc->setTextureType(MTL::TextureType::TextureType2DMultisampleArray);
    }

    _textureId = hgi->GetPrimaryDevice()->newTexture(texDesc);

    if (desc.initialData && desc.pixelsByteSize > 0) {
        // Depth, stencil, depth-stencil, and multisample textures must be
        // allocated with MTLStorageModePrivate, which should not be used with
        // replaceRegion. We create a temporary, non-private texture to fill
        // with the initial data, then  blit the data from that texture
        // to our original, private texture.

        // Modify texture descriptor to describe the temp texture.
        texDesc->setResourceOptions(MTL::ResourceStorageModeManaged);
        texDesc->setSampleCount(1);
        if (desc.type == HgiTextureType3D) {
            texDesc->setTextureType(MTL::TextureType::TextureType3D);
        } else if (desc.type == HgiTextureType2DArray) {
            texDesc->setTextureType(MTL::TextureType::TextureType2DArray);
        } else if (desc.type == HgiTextureType1D) {
            texDesc->setTextureType(MTL::TextureType::TextureType1D);
        } else if (desc.type == HgiTextureType1DArray) {
            texDesc->setTextureType(MTL::TextureType::TextureType1DArray);        
        }
        texDesc->setUsage(MTL::TextureUsageShaderRead);
        texDesc->setPixelFormat(HgiMetalConversions::GetPixelFormat(desc.format, HgiTextureUsageBitsShaderRead));    

        // Create temp texture and fill with initial data.
        MTL::Texture *tempTextureId = hgi->GetPrimaryDevice()->newTexture(texDesc);

        size_t perPixelSize = HgiGetDataSizeOfFormat(desc.format);

        // Upload each (available) mip
        const std::vector<HgiMipInfo> mipInfos =
            HgiGetMipInfos(
                desc.format,
                desc.dimensions,
                desc.layerCount,
                desc.pixelsByteSize);
        const size_t mipLevels = std::min(
            mipInfos.size(), size_t(desc.mipLevels));
        const char * const initialData = reinterpret_cast<const char *>(
            desc.initialData);

        for (size_t mip = 0; mip < mipLevels; mip++) {
            const HgiMipInfo &mipInfo = mipInfos[mip];

            const size_t width = mipInfo.dimensions[0];
            const size_t height = mipInfo.dimensions[1];
            const size_t bytesPerRow = perPixelSize * width;

            if (desc.type == HgiTextureType1D) {
                tempTextureId->replaceRegion(MTL::Region::Make1D(0, width),
                                             mip,
                                             initialData + mipInfo.byteOffset,
                                             bytesPerRow);
            } else if (desc.type == HgiTextureType2D) {
                tempTextureId->replaceRegion(MTL::Region::Make2D(0, 0, width, height),
                                             mip,
                                             initialData + mipInfo.byteOffset,
                                             bytesPerRow);
            } else if (desc.type == HgiTextureType3D) {
                const size_t depth = mipInfo.dimensions[2];
                const size_t imageBytes = bytesPerRow * height;
                for (size_t d = 0; d < depth; d++) {
                    const size_t offset = d * imageBytes;
                    tempTextureId->replaceRegion(MTL::Region::Make3D(0, 0, d, width, height, 1),
                                                 mip,
                                                 0,
                                                 initialData + mipInfo.byteOffset + offset,
                                                 bytesPerRow,
                                                 0);
                }
            } else if (desc.type == HgiTextureType2DArray) {
                const size_t imageBytes = bytesPerRow * height;
                for (int slice = 0; slice < desc.layerCount; slice++) {
                    char const *sliceBase = static_cast<char const*>(initialData) + mipInfo.byteOffset + imageBytes * slice;
                    tempTextureId->replaceRegion(MTL::Region::Make2D(0, 0, width, height),
                                                  mip,
                                                  slice,
                                                  sliceBase,
                                                  bytesPerRow,
                                                  0);
                }
            } else if (desc.type == HgiTextureType1DArray) {
                const size_t imageBytes = bytesPerRow;
                for (int slice = 0; slice < desc.layerCount; slice++) {
                    char const *sliceBase = static_cast<char const*>(initialData) + mipInfo.byteOffset + imageBytes * slice;
                    tempTextureId->replaceRegion(MTL::Region::Make1D(0, width),
                                                  mip,
                                                  slice,
                                                  sliceBase,
                                                  bytesPerRow,
                                                  0);
                }
            } else {
                TF_CODING_ERROR("Missing Texture upload implementation");
            }
        }

        // Blit data from temp texture to original texture.
        MTL::CommandBuffer *commandBuffer = hgi->GetQueue()->commandBuffer();
        MTL::BlitCommandEncoder *blitCommandEncoder = commandBuffer->blitCommandEncoder();
        int sliceCount = 1;
        if (desc.type == HgiTextureType1DArray ||
            desc.type == HgiTextureType2DArray) {
            sliceCount = desc.layerCount;
        }
        blitCommandEncoder->copyFromTexture(tempTextureId,
                                            0,
                                            0,
                                            _textureId,
                                            0,
                                            0,
                                            sliceCount,
                                            mipLevels);
        blitCommandEncoder->endEncoding();
        commandBuffer->commit();
        tempTextureId->release();
    }
    
    if (!(usage & MTL::TextureUsageRenderTarget)) {
        MTL::CommandBuffer *commandBuffer = hgi->GetQueue()->commandBuffer();
        MTL::BlitCommandEncoder *blitCommandEncoder = commandBuffer->blitCommandEncoder();
        blitCommandEncoder->optimizeContentsForGPUAccess(_textureId);
        blitCommandEncoder->endEncoding();
        commandBuffer->commit();
    }
    
    HGIMETAL_DEBUG_LABEL(_textureId, _descriptor.debugName.c_str());
}

HgiMetalTexture::HgiMetalTexture(HgiMetal *hgi, HgiTextureViewDesc const & desc)
    : HgiTexture(desc.sourceTexture->GetDescriptor())
    , _textureId(nil)
{
    HgiMetalTexture* srcTexture = static_cast<HgiMetalTexture*>(desc.sourceTexture.Get());
    NS::Range levels = NS::Range::Make(desc.sourceFirstMip, desc.mipLevels);
    NS::Range slices = NS::Range::Make(desc.sourceFirstLayer, desc.layerCount);
    MTL::PixelFormat mtlFormat = HgiMetalConversions::GetPixelFormat(desc.format, HgiTextureUsageBitsColorTarget);

    _textureId = srcTexture->GetTextureId()->newTextureView(mtlFormat, 
                                                            srcTexture->GetTextureId()->textureType(),
                                                            levels,
                                                            slices);
    
    // Update the texture descriptor to reflect the above
    _descriptor.debugName = desc.debugName;
    _descriptor.format = desc.format;
    _descriptor.layerCount = desc.layerCount;
    _descriptor.mipLevels = desc.mipLevels;
}

HgiMetalTexture::~HgiMetalTexture()
{
    if (_textureId != nil) {
        _textureId->release();
        _textureId = nil;
    }
}

size_t
HgiMetalTexture::GetByteSizeOfResource() const
{
    return _GetByteSizeOfResource(_descriptor);
}

uint64_t
HgiMetalTexture::GetRawResource() const
{
    return (uint64_t) _textureId;
}

MTL::Texture*
HgiMetalTexture::GetTextureId() const
{
    return _textureId;
}

PXR_NAMESPACE_CLOSE_SCOPE
