//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/ptexTextureObject.h"

#include "HdSt/subtextureIdentifier.h"
#include "HdSt/textureIdentifier.h"
#include "HdSt/textureUtils.h"

#include "Hgi/hgiImpl.h"
#include "Hgi/texture.h"
#include "Hgi/types.h"

#include "Hio/types.h"

#include "Trace/traceImpl.h"

#ifdef PXR_PTEX_SUPPORT_ENABLED
#  include <PtexUtils.h>
#  include <Ptexture.h>
#endif

PXR_NAMESPACE_OPEN_SCOPE

///////////////////////////////////////////////////////////////////////////////
// Helpers

namespace {

// Implements Deleter for std::unique_ptr calling release.
template<typename T> struct _ReleaseDeleter {
  void operator()(T *const obj)
  {
    return obj->release();
  }
};

// unique_ptr calling release instead of d'tor.
template<typename T> using _ReleaseUniquePtr = std::unique_ptr<T, _ReleaseDeleter<T>>;

}  // anonymous namespace

bool HdStIsSupportedPtexTexture(std::string const &imageFilePath)
{
#ifdef PXR_PTEX_SUPPORT_ENABLED
  return (TfStringEndsWith(imageFilePath, ".ptx") || TfStringEndsWith(imageFilePath, ".ptex"));
#else
  return false;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Ptex texture

HdStPtexTextureObject::HdStPtexTextureObject(
    const HdStTextureIdentifier &textureId,
    HdSt_TextureObjectRegistry *const textureObjectRegistry)
    : HdStTextureObject(textureId, textureObjectRegistry),
      _format(HgiFormatInvalid),
      _texelDimensions(0),
      _texelLayers(0),
      _texelDataSize(0),
      _layoutDimensions(0),
      _layoutDataSize(0)
{
}

HdStPtexTextureObject::~HdStPtexTextureObject()
{
  _DestroyTextures();
}

void HdStPtexTextureObject::_DestroyTextures()
{
  if (Hgi *hgi = _GetHgi()) {
    if (_texelTexture) {
      hgi->DestroyTexture(&_texelTexture);
    }
    if (_layoutTexture) {
      hgi->DestroyTexture(&_layoutTexture);
    }
  }
}

#ifdef PXR_PTEX_SUPPORT_ENABLED
static HioType _GetHioType(const Ptex::DataType t)
{
  switch (t) {
    case Ptex::dt_float:
      return HioTypeFloat;
    case Ptex::dt_half:
      return HioTypeHalfFloat;
    case Ptex::dt_uint16:
      return HioTypeUnsignedShort;
    case Ptex::dt_uint8:
      return HioTypeUnsignedByte;
  }
  return HioTypeUnsignedByte;
}
#endif

void HdStPtexTextureObject::_Load()
{
  TRACE_FUNCTION();

  _DestroyTextures();

  TRACE_SCOPE("HdStPtexTextureObject::_Load() (read ptex)");

  _format = HgiFormatInvalid;

#ifdef PXR_PTEX_SUPPORT_ENABLED
  const std::string &filename = GetTextureIdentifier().GetFilePath();

  const bool premultiplyAlpha = _GetPremultiplyAlpha(
      GetTextureIdentifier().GetSubtextureIdentifier());

  // create a temporary ptex cache
  // (required to build guttering pixels efficiently)
  constexpr int PTEX_MAX_CACHE_SIZE = 128 * 1024 * 1024;
  // Held by std::unique_ptr calling release instead of d'tor
  const _ReleaseUniquePtr<PtexCache> cache(
      PtexCache::create(1, PTEX_MAX_CACHE_SIZE, premultiplyAlpha));
  if (!cache) {
    TF_WARN("Unable to create PtexCache");
    return;
  }

  // load
  Ptex::String ptexError;
  // Held by std::unique_ptr calling release instead of d'tor
  const _ReleaseUniquePtr<PtexTexture> reader(cache->get(filename.c_str(), ptexError));
  if (!reader) {
    TF_WARN("Unable to open ptex %s : %s", filename.c_str(), ptexError.c_str());
    return;
  }

  // Read the ptexture data and pack the texels

  TRACE_SCOPE("HdStPtexTextureObject::_Load() (generate texture)");

  // This is the minimum texture layers guaranteed by OpenGL 4.5 and Metal
  constexpr size_t maxNumPages = 2048;

  // maxLevels = -1 : load all mip levels
  // maxLevels = 0  : load only the highest resolution
  constexpr int maxLevels = -1;
  HdStPtexMipmapTextureLoader loader(reader.get(), maxNumPages, maxLevels, GetTargetMemory());

  const unsigned char *const loaderLayoutBuffer = loader.GetLayoutBuffer();
  if (!loaderLayoutBuffer) {
    return;
  }
  const size_t numFaces = loader.GetNumFaces();

  // Layout data in memory buffer after load
  constexpr size_t maxTextureWidth = 16384;
  constexpr size_t layoutTexelsPerFace = 3;
  constexpr size_t maxFacesPerLayer = maxTextureWidth / layoutTexelsPerFace;

  _layoutDimensions = GfVec2i(maxFacesPerLayer * layoutTexelsPerFace,
                              (numFaces + maxFacesPerLayer - 1) / maxFacesPerLayer);

  const unsigned char *const loaderTexelBuffer = loader.GetTexelBuffer();
  if (!loaderTexelBuffer) {
    return;
  }

  const HioFormat hioFormat = HioGetFormat(reader->numChannels(),
                                           _GetHioType(reader->dataType()),
                                           /* isSRGB = */ false);

  // Texel data in memory buffer after load
  _texelDimensions = GfVec3i(loader.GetPageWidth(), loader.GetPageHeight(), 1);
  _texelLayers = loader.GetNumPages();

  // premultiplyAlpha = false since Ptex cache already premultiplied.
  _format = HdStTextureUtils::GetHgiFormat(hioFormat,
                                           /* premultiplyAlpha = */ false);

  if (_format == HgiFormatInvalid) {
    TF_WARN("Unsupported texture format for PTEX");
    return;
  }

  const HdStTextureUtils::ConversionFunction conversionFunction =
      HdStTextureUtils::GetHioToHgiConversion(hioFormat,
                                              /* premultiplyAlpha = */ false);

  _texelDataSize = _texelLayers * HgiGetDataSize(_format, _texelDimensions);

  _texelData = std::make_unique<uint8_t[]>(_texelDataSize);
  if (conversionFunction) {
    const size_t numTexels = _texelLayers * _texelDimensions[0] * _texelDimensions[1];
    conversionFunction(loaderTexelBuffer, numTexels, _texelData.get());
  }
  else {
    memcpy(_texelData.get(), loaderTexelBuffer, _texelDataSize);
  }

  static const size_t layoutBytesPerTexel = HgiGetDataSizeOfFormat(HgiFormatUInt16Vec2);

  _layoutDataSize = _layoutDimensions[0] * _layoutDimensions[1] * layoutBytesPerTexel;
  _layoutData = std::make_unique<uint8_t[]>(_layoutDataSize);
  memcpy(
      _layoutData.get(), loaderLayoutBuffer, numFaces * layoutTexelsPerFace * layoutBytesPerTexel);
#endif
}

void HdStPtexTextureObject::_Commit()
{
  TRACE_FUNCTION();

  Hgi *const hgi = _GetHgi();
  if (!TF_VERIFY(hgi)) {
    return;
  }

  _DestroyTextures();

  if (_format == HgiFormatInvalid) {
    // Create 1x1x1 black fallback texture.
    HgiTextureDesc texDesc;
    texDesc.debugName = "PtexTextureFallback";
    texDesc.usage = HgiTextureUsageBitsShaderRead;
    texDesc.format = HgiFormatUNorm8Vec4;
    texDesc.type = HgiTextureType2DArray;
    texDesc.dimensions = GfVec3i(1, 1, 1);
    ;
    texDesc.layerCount = 1;
    texDesc.mipLevels = 1;
    texDesc.pixelsByteSize = 4 * sizeof(unsigned char);
    const unsigned char data[4] = {0, 0, 0, 255};
    texDesc.initialData = &data[0];
    _texelTexture = hgi->CreateTexture(texDesc);

    HgiTextureDesc layoutTexDesc;
    layoutTexDesc.debugName = "PtexLayoutTextureFallback";
    layoutTexDesc.usage = HgiTextureUsageBitsShaderRead;
    layoutTexDesc.type = HgiTextureType1DArray;
    layoutTexDesc.dimensions = GfVec3i(1, 1, 1);
    layoutTexDesc.format = HgiFormatUInt16Vec2;
    layoutTexDesc.layerCount = 1;
    layoutTexDesc.mipLevels = 1;
    layoutTexDesc.pixelsByteSize = 2 * sizeof(uint16_t);
    const uint16_t layoutData[2] = {0, 0};
    layoutTexDesc.initialData = &layoutData[0];
    _layoutTexture = hgi->CreateTexture(layoutTexDesc);

    return;
  }

  // Texel GPU texture creation
  {
    HgiTextureDesc texDesc;
    texDesc.debugName = _GetDebugName(GetTextureIdentifier());
    texDesc.usage = HgiTextureUsageBitsShaderRead;
    texDesc.type = HgiTextureType2DArray;
    texDesc.dimensions = _texelDimensions;
    texDesc.layerCount = _texelLayers;
    texDesc.format = _format;
    texDesc.mipLevels = 1;
    texDesc.initialData = _texelData.get();
    texDesc.pixelsByteSize = _texelDataSize;
    _texelTexture = hgi->CreateTexture(texDesc);
  }

  // Layout GPU texture creation
  {
    // ptex layout struct (6 * uint16_t)
    // struct Layout {
    //     uint16_t page;
    //     uint16_t nMipmap;
    //     uint16_t u;
    //     uint16_t v;
    //     uint16_t adjSizeDiffs; //(4:4:4:4)
    //     uint8_t  width log2;
    //     uint8_t  height log2;
    // };

    HgiTextureDesc texDesc;
    texDesc.debugName = _GetDebugName(GetTextureIdentifier());
    texDesc.usage = HgiTextureUsageBitsShaderRead;
    texDesc.type = HgiTextureType1DArray;
    texDesc.dimensions = GfVec3i(_layoutDimensions[0], 1, 1);
    texDesc.layerCount = _layoutDimensions[1];
    texDesc.format = HgiFormatUInt16Vec2;
    texDesc.mipLevels = 1;
    texDesc.initialData = _layoutData.get();
    texDesc.pixelsByteSize = _layoutDataSize;
    _layoutTexture = hgi->CreateTexture(texDesc);
  }

  // Free CPU data
  _texelData.reset();
  _layoutData.reset();
}

bool HdStPtexTextureObject::IsValid() const
{
  return _format != HgiFormatInvalid;
}

HdStTextureType HdStPtexTextureObject::GetTextureType() const
{
  return HdStTextureType::Ptex;
}

PXR_NAMESPACE_CLOSE_SCOPE
