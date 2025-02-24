//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/udimTextureObject.h"

#include "HdSt/subtextureIdentifier.h"
#include "HdSt/textureIdentifier.h"
#include "HdSt/textureUtils.h"

#include "Hgi/hgiImpl.h"
#include "Hgi/texture.h"
#include "Hgi/types.h"

#include "Hio/image.h"

#include "Tf/iterator.h"
#include "Trace/traceImpl.h"
#include "Work/loops.h"

#include "Ar/resolver.h"

PXR_NAMESPACE_OPEN_SCOPE

bool HdStIsSupportedUdimTexture(std::string const &imageFilePath)
{
  return TfStringContains(imageFilePath, "<UDIM>");
}

///////////////////////////////////////////////////////////////////////////////
// Udim texture

namespace {

static const char UDIM_PATTERN[] = "<UDIM>";
static const int UDIM_START_TILE = 1001;
static const int UDIM_END_TILE = 1100;

// Split a udim file path such as /someDir/myFile.<UDIM>.exr into a
// prefix (/someDir/myFile.) and suffix (.exr).
static std::pair<std::string, std::string> _SplitUdimPattern(const std::string &path)
{
  static const std::string pattern(UDIM_PATTERN);

  const std::string::size_type pos = path.find(pattern);

  if (pos != std::string::npos) {
    return {path.substr(0, pos), path.substr(pos + pattern.size())};
  }

  return {std::string(), std::string()};
}

// Find all udim tiles for a given udim file path /someDir/myFile.<UDIM>.exr as
// pairs, e.g., (0, /someDir/myFile.1001.exr), ...
//
// The scene delegate is assumed to already have resolved the asset path with
// the <UDIM> pattern to a "file path" with the <UDIM> pattern as above.
// This function will replace <UDIM> by different integers and check whether
// the "file" exists using an ArGetResolver.
//
// Note that the ArGetResolver is still needed, for, e.g., usdz file
// where the path we get from the scene delegate is
// /someDir/myFile.usdz[myImage.<UDIM>.EXR] and we need to use the
// ArGetResolver to check whether, e.g., myImage.1001.EXR exists in
// the zip file /someDir/myFile.usdz by calling
// resolver.Resolve(/someDir/myFile.usdz[myImage.1001.EXR]).
// However, we don't need to bind, e.g., the usd stage's resolver context
// because that part of the resolution will be done by the scene delegate
// for us already.
//
static std::vector<std::tuple<int, TfToken>> _FindUdimTiles(const std::string &filePath)
{
  std::vector<std::tuple<int, TfToken>> result;

  // Get prefix and suffix from udim pattern.
  const std::pair<std::string, std::string> splitPath = _SplitUdimPattern(filePath);
  if (splitPath.first.empty() && splitPath.second.empty()) {
    TF_WARN("Expected udim pattern but got '%s'.", filePath.c_str());
    return result;
  }

  ArResolver &resolver = ArGetResolver();

  for (int i = UDIM_START_TILE; i <= UDIM_END_TILE; i++) {
    // Add integer between prefix and suffix and see whether
    // the tile exists by consulting the resolver.
    const std::string resolvedPath = resolver.Resolve(splitPath.first + std::to_string(i) +
                                                      splitPath.second);
    if (!resolvedPath.empty()) {
      // Record pair in result.
      result.emplace_back(i - UDIM_START_TILE, resolvedPath);
    }
  }

  return result;
}
}  // anonymous namespace

HdStUdimTextureObject::HdStUdimTextureObject(
    const HdStTextureIdentifier &textureId,
    HdSt_TextureObjectRegistry *const textureObjectRegistry)
    : HdStTextureObject(textureId, textureObjectRegistry),
      _dimensions(0),
      _mipCount(0),
      _hgiFormat(HgiFormatInvalid)
{
}

HdStUdimTextureObject::~HdStUdimTextureObject()
{
  _DestroyTextures();
}

void HdStUdimTextureObject::_DestroyTextures()
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

static const HioImageSharedPtr &_GetSmallestImageLargerThan(
    const std::vector<HioImageSharedPtr> &images, const GfVec3i &dimensions)
{
  for (auto it = images.rbegin(); it != images.rend(); ++it) {
    if (dimensions[0] <= (*it)->GetWidth() && dimensions[1] <= (*it)->GetHeight()) {
      return *it;
    }
  }
  return images.front();
}

void HdStUdimTextureObject::_Load()
{
  const std::vector<std::tuple<int, TfToken>> tiles = _FindUdimTiles(
      GetTextureIdentifier().GetFilePath());
  if (tiles.empty()) {
    return;
  }

  const HdStSubtextureIdentifier *const subId = GetTextureIdentifier().GetSubtextureIdentifier();

  const HioImage::SourceColorSpace sourceColorSpace = _GetSourceColorSpace(subId);
  const std::vector<HioImageSharedPtr> firstImageMips = HdStTextureUtils::GetAllMipImages(
      std::get<1>(tiles[0]), sourceColorSpace);
  if (firstImageMips.empty()) {
    return;
  }

  // Determine Hio and corresponding Hgi format from first tile.
  const HioFormat hioFormat = firstImageMips[0]->GetFormat();
  const bool premultiplyAlpha = _GetPremultiplyAlpha(subId);
  _hgiFormat = HdStTextureUtils::GetHgiFormat(hioFormat, premultiplyAlpha);

  if (_hgiFormat == HgiFormatInvalid || HgiIsCompressed(_hgiFormat)) {
    TF_WARN("Unsupported texture format for UDIM");
    return;
  }

  _tileCount = static_cast<int>(tiles.size());

  _dimensions = HdStTextureUtils::ComputeDimensionsFromTargetMemory(
      firstImageMips, _hgiFormat, _tileCount, GetTargetMemory());

  // Texture array queries will use a float as the array specifier.
  const unsigned int maxTileId = std::get<0>(tiles.back()) + 1;
  _layoutData.resize(maxTileId, 0);

  // Use Hgi to compute the mip sizes from the dimensions
  const std::vector<HgiMipInfo> mipInfos = HgiGetMipInfos(_hgiFormat, _dimensions, _tileCount);
  _mipCount = mipInfos.size();

  const HgiMipInfo &lastMipInfo = mipInfos.back();

  // Allocate memory for the mipData, ready for upload to GPU
  _textureData.resize(lastMipInfo.byteOffset + _tileCount * lastMipInfo.byteSizePerLayer);

  WorkParallelForN(
      tiles.size(),
      [&](size_t begin, size_t end) {
        for (size_t tileId = begin; tileId < end; ++tileId) {
          std::tuple<int, TfToken> const &tile = tiles[tileId];
          _layoutData[std::get<0>(tile)] = tileId + 1;
          const std::vector<HioImageSharedPtr> images = HdStTextureUtils::GetAllMipImages(
              std::get<1>(tile), sourceColorSpace);
          if (images.empty()) {
            continue;
          }
          for (const HgiMipInfo &mipInfo : mipInfos) {
            HioImageSharedPtr const &image = _GetSmallestImageLargerThan(images,
                                                                         mipInfo.dimensions);
            HdStTextureUtils::ReadAndConvertImage(image,
                                                  /* flipped = */ true,
                                                  premultiplyAlpha,
                                                  mipInfo,
                                                  tileId,
                                                  _textureData.data());
          }
        }
      },
      1);
}

void HdStUdimTextureObject::_Commit()
{
  TRACE_FUNCTION();

  Hgi *const hgi = _GetHgi();
  if (!TF_VERIFY(hgi)) {
    return;
  }

  _DestroyTextures();

  if (_hgiFormat == HgiFormatInvalid) {
    // Create 1x1x1 black fallback texture.
    HgiTextureDesc texDesc;
    texDesc.debugName = "UdimTextureFallback";
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
    layoutTexDesc.debugName = "UdimLayoutTextureFallback";
    layoutTexDesc.usage = HgiTextureUsageBitsShaderRead;
    layoutTexDesc.type = HgiTextureType1D;
    layoutTexDesc.dimensions = GfVec3i(1, 1, 1);
    layoutTexDesc.format = HgiFormatFloat32;
    layoutTexDesc.layerCount = 1;
    layoutTexDesc.mipLevels = 1;
    layoutTexDesc.pixelsByteSize = sizeof(float);
    const float layoutData[1] = {1};
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
    texDesc.dimensions = _dimensions;
    texDesc.layerCount = _tileCount;
    texDesc.format = _hgiFormat;
    texDesc.mipLevels = _mipCount;
    texDesc.initialData = _textureData.data();
    texDesc.pixelsByteSize = _textureData.size();
    _texelTexture = hgi->CreateTexture(texDesc);
  }

  // Layout GPU texture creation
  {
    HgiTextureDesc texDesc;
    texDesc.debugName = _GetDebugName(GetTextureIdentifier());
    texDesc.usage = HgiTextureUsageBitsShaderRead;
    texDesc.type = HgiTextureType1D;
    texDesc.dimensions = GfVec3i(_layoutData.size(), 1, 1);
    texDesc.format = HgiFormatFloat32;
    texDesc.initialData = _layoutData.data();
    texDesc.pixelsByteSize = _layoutData.size() * sizeof(float);
    _layoutTexture = hgi->CreateTexture(texDesc);
  }

  // Free CPU memory after transfer to GPU
  _textureData.clear();
  _layoutData.clear();
}

bool HdStUdimTextureObject::IsValid() const
{
  return _hgiFormat != HgiFormatInvalid;
}

HdStTextureType HdStUdimTextureObject::GetTextureType() const
{
  return HdStTextureType::Udim;
}

PXR_NAMESPACE_CLOSE_SCOPE
