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
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "HgiMetal/conversions.h"

#include "Tf/iterator.h"
#include "Tf/staticTokens.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

//
// HgiFormat
//
static const MTL::PixelFormat _PIXEL_FORMAT_DESC[] = {
    MTL::PixelFormatR8Unorm,   // HgiFormatUNorm8,
    MTL::PixelFormatRG8Unorm,  // HgiFormatUNorm8Vec2,
    // MTL::PixelFormatInvalid,          // Unsupported by HgiFormat
    MTL::PixelFormatRGBA8Unorm,  // HgiFormatUNorm8Vec4,

    MTL::PixelFormatR8Snorm,   // HgiFormatSNorm8,
    MTL::PixelFormatRG8Snorm,  // HgiFormatSNorm8Vec2,
    // MTL::PixelFormatInvalid,          // Unsupported by HgiFormat
    MTL::PixelFormatRGBA8Snorm,  // HgiFormatSNorm8Vec4,

    MTL::PixelFormatR16Float,     // HgiFormatFloat16,
    MTL::PixelFormatRG16Float,    // HgiFormatFloat16Vec2,
    MTL::PixelFormatInvalid,      // Unsupported by Metal
    MTL::PixelFormatRGBA16Float,  // HgiFormatFloat16Vec4,

    MTL::PixelFormatR32Float,     // HgiFormatFloat32,
    MTL::PixelFormatRG32Float,    // HgiFormatFloat32Vec2,
    MTL::PixelFormatInvalid,      // Unsupported by Metal
    MTL::PixelFormatRGBA32Float,  // HgiFormatFloat32Vec4,

    MTL::PixelFormatR16Sint,     // HgiFormatInt16,
    MTL::PixelFormatRG16Sint,    // HgiFormatInt16Vec2,
    MTL::PixelFormatInvalid,     // Unsupported by Metal
    MTL::PixelFormatRGBA16Sint,  // HgiFormatInt16Vec4,

    MTL::PixelFormatR16Uint,     // HgiFormatUInt16,
    MTL::PixelFormatRG16Uint,    // HgiFormatUInt16Vec2,
    MTL::PixelFormatInvalid,     // Unsupported by Metal
    MTL::PixelFormatRGBA16Uint,  // HgiFormatUInt16Vec4,

    MTL::PixelFormatR32Sint,     // HgiFormatInt32,
    MTL::PixelFormatRG32Sint,    // HgiFormatInt32Vec2,
    MTL::PixelFormatInvalid,     // Unsupported by Metal
    MTL::PixelFormatRGBA32Sint,  // HgiFormatInt32Vec4,

    // MTL::PixelFormatRGB8Unorm_sRGB,   // Unsupported by HgiFormat
    MTL::PixelFormatRGBA8Unorm_sRGB,  // HgiFormatUNorm8Vec4srgb,

    MTL::PixelFormatBC6H_RGBFloat,       // HgiFormatBC6FloatVec3
    MTL::PixelFormatBC6H_RGBUfloat,      // HgiFormatBC6UFloatVec3
    MTL::PixelFormatBC7_RGBAUnorm,       // HgiFormatBC7UNorm8Vec4
    MTL::PixelFormatBC7_RGBAUnorm_sRGB,  // HgiFormatBC7UNorm8Vec4srgb
    MTL::PixelFormatBC1_RGBA,            // HgiFormatBC1UNorm8Vec4
    MTL::PixelFormatBC3_RGBA,            // HgiFormatBC3UNorm8Vec4

    MTL::PixelFormatDepth32Float_Stencil8,  // HgiFormatFloat32UInt8

    MTL::PixelFormatInvalid,  // Unsupported by Metal

    // Note: Update _VERTEX_FORMAT_DESC as well.
};

// A few random format validations to make sure out GL table stays aligned
// with the HgiFormat table.
constexpr bool _CompileTimeValidateHgiFormatTable()
{
  return (TfArraySize(_PIXEL_FORMAT_DESC) == HgiFormatCount && HgiFormatUNorm8 == 0 &&
          HgiFormatFloat16Vec4 == 9 && HgiFormatFloat32Vec4 == 13 && HgiFormatUInt16Vec4 == 21 &&
          HgiFormatUNorm8Vec4srgb == 26 && HgiFormatBC3UNorm8Vec4 == 32) ?
             true :
             false;
}

static_assert(_CompileTimeValidateHgiFormatTable(),
              "_PIXEL_FORMAT_DESC array out of sync with HgiFormat enum");

//
// MTL::VertexFormat
//
static const MTL::VertexFormat _VERTEX_FORMAT_DESC[] = {
    MTL::VertexFormatUCharNormalized,   // HgiFormatUNorm8,
    MTL::VertexFormatUChar2Normalized,  // HgiFormatUNorm8Vec2,
    // MTL::VertexFormatUChar3Normalized,  // Unsupported by HgiFormat,
    MTL::VertexFormatUChar4Normalized,  // HgiFormatUNorm8Vec4,

    MTL::VertexFormatCharNormalized,   // HgiFormatSNorm8,
    MTL::VertexFormatChar2Normalized,  // HgiFormatSNorm8Vec2,
    // MTL::VertexFormatChar3Normalized,   // Unsupported by HgiFormat,
    MTL::VertexFormatChar4Normalized,  // HgiFormatSNorm8Vec4,

    MTL::VertexFormatHalf,   // HgiFormatFloat16,
    MTL::VertexFormatHalf2,  // HgiFormatFloat16Vec2,
    MTL::VertexFormatHalf3,  // HgiFormatFloat16Vec3,
    MTL::VertexFormatHalf4,  // HgiFormatFloat16Vec4,

    MTL::VertexFormatFloat,   // HgiFormatFloat32,
    MTL::VertexFormatFloat2,  // HgiFormatFloat32Vec2,
    MTL::VertexFormatFloat3,  // HgiFormatFloat32Vec3,
    MTL::VertexFormatFloat4,  // HgiFormatFloat32Vec4,

    MTL::VertexFormatShort,   // HgiFormatInt16,
    MTL::VertexFormatShort2,  // HgiFormatInt16Vec2,
    MTL::VertexFormatShort3,  // HgiFormatInt16Vec3,
    MTL::VertexFormatShort4,  // HgiFormatInt16Vec4,

    MTL::VertexFormatUShort,   // HgiFormatUInt16,
    MTL::VertexFormatUShort2,  // HgiFormatUInt16Vec2,
    MTL::VertexFormatUShort3,  // HgiFormatUInt16Vec3,
    MTL::VertexFormatUShort4,  // HgiFormatUInt16Vec4,

    MTL::VertexFormatInt,   // HgiFormatInt32,
    MTL::VertexFormatInt2,  // HgiFormatInt32Vec2,
    MTL::VertexFormatInt3,  // HgiFormatInt32Vec3,
    MTL::VertexFormatInt4,  // HgiFormatInt32Vec4,

    // MTL::VertexFormatUChar4Normalized,  // Unsupported by HgiFormat
    MTL::VertexFormatUChar4Normalized,  // HgiFormatUNorm8Vec4sRGB,

    MTL::VertexFormatInvalid,  // HgiFormatBC6FloatVec3
    MTL::VertexFormatInvalid,  // HgiFormatBC6UFloatVec3
    MTL::VertexFormatInvalid,  // HgiFormatBC7UNorm8Vec4
    MTL::VertexFormatInvalid,  // HgiFormatBC7UNorm8Vec4srgb
    MTL::VertexFormatInvalid,  // HgiFormatBC1UNorm8Vec4
    MTL::VertexFormatInvalid,  // HgiFormatBC3UNorm8Vec4

    MTL::VertexFormatInvalid,  // HgiFormatFloat32UInt8

    MTL::VertexFormatInt1010102Normalized,  // HgiFormatPackedInt1010102
};

constexpr bool _CompileTimeValidateHgiVertexFormatTable()
{
  return (TfArraySize(_VERTEX_FORMAT_DESC) == HgiFormatCount && HgiFormatUNorm8 == 0 &&
          HgiFormatFloat16Vec4 == 9 && HgiFormatFloat32Vec4 == 13 && HgiFormatUInt16Vec4 == 21 &&
          HgiFormatUNorm8Vec4srgb == 26 && HgiFormatBC3UNorm8Vec4 == 32) ?
             true :
             false;
}

static_assert(_CompileTimeValidateHgiVertexFormatTable(),
              "_VertexFormatDesc array out of sync with HgiFormat enum");

//
// HgiCullMode
//
struct {
  HgiCullMode hgiCullMode;
  MTL::CullMode metalCullMode;
} static const _CullModeTable[] = {
    {HgiCullModeNone, MTL::CullModeNone},
    {HgiCullModeFront, MTL::CullModeFront},
    {HgiCullModeBack, MTL::CullModeBack},
    {HgiCullModeFrontAndBack, MTL::CullModeNone}  // Unsupported
};

static_assert(TfArraySize(_CullModeTable) == HgiCullModeCount,
              "_CullModeTable array out of sync with HgiFormat enum");

//
// HgiPolygonMode
//
struct {
  HgiPolygonMode hgiFillMode;
  MTL::TriangleFillMode metalFillMode;
} static const _PolygonModeTable[] = {
    {HgiPolygonModeFill, MTL::TriangleFillModeFill},
    {HgiPolygonModeLine, MTL::TriangleFillModeLines},
    {HgiPolygonModePoint, MTL::TriangleFillModeFill},  // Unsupported
};

static_assert(TfArraySize(_PolygonModeTable) == HgiPolygonModeCount,
              "_PolygonModeTable array out of sync with HgiFormat enum");

//
// HgiBlendOp
//
struct {
  HgiBlendOp hgiBlendOp;
  MTL::BlendOperation metalBlendOp;
} static const _blendEquationTable[] = {
    {HgiBlendOpAdd, MTL::BlendOperationAdd},
    {HgiBlendOpSubtract, MTL::BlendOperationSubtract},
    {HgiBlendOpReverseSubtract, MTL::BlendOperationReverseSubtract},
    {HgiBlendOpMin, MTL::BlendOperationMin},
    {HgiBlendOpMax, MTL::BlendOperationMax},
};

static_assert(TfArraySize(_blendEquationTable) == HgiBlendOpCount,
              "_blendEquationTable array out of sync with HgiFormat enum");

//
// HgiBlendFactor
//
struct {
  HgiBlendFactor hgiBlendFactor;
  MTL::BlendFactor metalBlendFactor;
} static const _blendFactorTable[] = {
    {HgiBlendFactorZero, MTL::BlendFactorZero},
    {HgiBlendFactorOne, MTL::BlendFactorOne},
    {HgiBlendFactorSrcColor, MTL::BlendFactorSourceColor},
    {HgiBlendFactorOneMinusSrcColor, MTL::BlendFactorOneMinusSourceColor},
    {HgiBlendFactorDstColor, MTL::BlendFactorDestinationColor},
    {HgiBlendFactorOneMinusDstColor, MTL::BlendFactorOneMinusDestinationColor},
    {HgiBlendFactorSrcAlpha, MTL::BlendFactorSourceAlpha},
    {HgiBlendFactorOneMinusSrcAlpha, MTL::BlendFactorOneMinusSourceAlpha},
    {HgiBlendFactorDstAlpha, MTL::BlendFactorDestinationAlpha},
    {HgiBlendFactorOneMinusDstAlpha, MTL::BlendFactorOneMinusDestinationAlpha},
    {HgiBlendFactorConstantColor, MTL::BlendFactorZero},          // Unsupported
    {HgiBlendFactorOneMinusConstantColor, MTL::BlendFactorZero},  // Unsupported
    {HgiBlendFactorConstantAlpha, MTL::BlendFactorZero},          // Unsupported
    {HgiBlendFactorOneMinusConstantAlpha, MTL::BlendFactorZero},  // Unsupported
    {HgiBlendFactorSrcAlphaSaturate, MTL::BlendFactorSourceAlphaSaturated},
    {HgiBlendFactorSrc1Color, MTL::BlendFactorSource1Color},
    {HgiBlendFactorOneMinusSrc1Color, MTL::BlendFactorOneMinusSource1Color},
    {HgiBlendFactorSrc1Alpha, MTL::BlendFactorSourceAlpha},
    {HgiBlendFactorOneMinusSrc1Alpha, MTL::BlendFactorOneMinusSource1Alpha},
};

static_assert(TfArraySize(_blendFactorTable) == HgiBlendFactorCount,
              "_blendFactorTable array out of sync with HgiFormat enum");

//
// HgiWinding
//
struct {
  HgiWinding hgiWinding;
  MTL::Winding metalWinding;
} static const _windingTable[] = {
    // Winding order is inverted because our viewport is inverted.
    // This combination allows us to emulate the OpenGL coordinate space on
    // Metal
    {HgiWindingClockwise, MTL::WindingCounterClockwise},
    {HgiWindingCounterClockwise, MTL::WindingClockwise},
};

static_assert(TfArraySize(_windingTable) == HgiWindingCount,
              "_windingTable array out of sync with HgiFormat enum");

//
// HgiAttachmentLoadOp
//
struct {
  HgiAttachmentLoadOp hgiAttachmentLoadOp;
  MTL::LoadAction metalLoadOp;
} static const _attachmentLoadOpTable[] = {
    {HgiAttachmentLoadOpDontCare, MTL::LoadActionDontCare},
    {HgiAttachmentLoadOpClear, MTL::LoadActionClear},
    {HgiAttachmentLoadOpLoad, MTL::LoadActionLoad},
};

static_assert(TfArraySize(_attachmentLoadOpTable) == HgiAttachmentLoadOpCount,
              "_attachmentLoadOpTable array out of sync with HgiFormat enum");

//
// HgiAttachmentStoreOp
//
struct {
  HgiAttachmentStoreOp hgiAttachmentStoreOp;
  MTL::StoreAction metalStoreOp;
} static const _attachmentStoreOpTable[] = {
    {HgiAttachmentStoreOpDontCare, MTL::StoreActionDontCare},
    {HgiAttachmentStoreOpStore, MTL::StoreActionStore},
};

static_assert(TfArraySize(_attachmentStoreOpTable) == HgiAttachmentStoreOpCount,
              "_attachmentStoreOpTable array out of sync with HgiFormat enum");

//
// HgiCompareFunction
//
struct {
  HgiCompareFunction hgiCompareFunction;
  MTL::CompareFunction metalCF;
} static const _compareFnTable[] = {
    {HgiCompareFunctionNever, MTL::CompareFunctionNever},
    {HgiCompareFunctionLess, MTL::CompareFunctionLess},
    {HgiCompareFunctionEqual, MTL::CompareFunctionEqual},
    {HgiCompareFunctionLEqual, MTL::CompareFunctionLessEqual},
    {HgiCompareFunctionGreater, MTL::CompareFunctionGreater},
    {HgiCompareFunctionNotEqual, MTL::CompareFunctionNotEqual},
    {HgiCompareFunctionGEqual, MTL::CompareFunctionGreaterEqual},
    {HgiCompareFunctionAlways, MTL::CompareFunctionAlways},
};

static_assert(TfArraySize(_compareFnTable) == HgiCompareFunctionCount,
              "_compareFnTable array out of sync with HgiFormat enum");

//
// HgiStencilOp
//
struct {
  HgiStencilOp hgiStencilOp;
  MTL::StencilOperation metalStencilOp;
} static const _stencilOpTable[] = {
    {HgiStencilOpKeep, MTL::StencilOperationKeep},
    {HgiStencilOpZero, MTL::StencilOperationZero},
    {HgiStencilOpReplace, MTL::StencilOperationReplace},
    {HgiStencilOpIncrementClamp, MTL::StencilOperationIncrementClamp},
    {HgiStencilOpDecrementClamp, MTL::StencilOperationDecrementClamp},
    {HgiStencilOpInvert, MTL::StencilOperationInvert},
    {HgiStencilOpIncrementWrap, MTL::StencilOperationIncrementWrap},
    {HgiStencilOpDecrementWrap, MTL::StencilOperationDecrementWrap},
};

static_assert(TfArraySize(_stencilOpTable) == HgiStencilOpCount,
              "_stencilOpTable array out of sync with HgiStencilOp enum");

struct {
  HgiTextureType hgiTextureType;
  MTL::TextureType metalTT;
} static const _textureTypeTable[HgiTextureTypeCount] = {
    {HgiTextureType1D, MTL::TextureType1D},
    {HgiTextureType2D, MTL::TextureType2D},
    {HgiTextureType3D, MTL::TextureType3D},
    {HgiTextureType1DArray, MTL::TextureType1DArray},
    {HgiTextureType2DArray, MTL::TextureType2DArray},
};

static_assert(TfArraySize(_compareFnTable) == HgiCompareFunctionCount,
              "_compareFnTable array out of sync with HgiFormat enum");

struct {
  HgiSamplerAddressMode hgiAddressMode;
  MTL::SamplerAddressMode metalAM;
} static const _samplerAddressModeTable[HgiSamplerAddressModeCount] = {
    {HgiSamplerAddressModeClampToEdge, MTL::SamplerAddressModeClampToEdge},
    {HgiSamplerAddressModeMirrorClampToEdge, MTL::SamplerAddressModeMirrorClampToEdge},
    {HgiSamplerAddressModeRepeat, MTL::SamplerAddressModeRepeat},
    {HgiSamplerAddressModeMirrorRepeat, MTL::SamplerAddressModeMirrorRepeat},
    {HgiSamplerAddressModeClampToBorderColor, MTL::SamplerAddressModeClampToBorderColor}};

struct {
  HgiSamplerFilter hgiSamplerFilter;
  MTL::SamplerMinMagFilter metalSF;
} static const _samplerFilterTable[HgiSamplerFilterCount] = {
    {HgiSamplerFilterNearest, MTL::SamplerMinMagFilterNearest},
    {HgiSamplerFilterLinear, MTL::SamplerMinMagFilterLinear}};

struct {
  HgiMipFilter hgiMipFilter;
  MTL::SamplerMipFilter metalMF;
} static const _mipFilterTable[HgiMipFilterCount] = {
    {HgiMipFilterNotMipmapped, MTL::SamplerMipFilterNotMipmapped},
    {HgiMipFilterNearest, MTL::SamplerMipFilterNearest},
    {HgiMipFilterLinear, MTL::SamplerMipFilterLinear}};

struct {
  HgiBorderColor hgiBorderColor;
  MTL::SamplerBorderColor metalBC;
} static const _borderColorTable[HgiBorderColorCount] = {
    {HgiBorderColorTransparentBlack, MTL::SamplerBorderColorTransparentBlack},
    {HgiBorderColorOpaqueBlack, MTL::SamplerBorderColorOpaqueBlack},
    {HgiBorderColorOpaqueWhite, MTL::SamplerBorderColorOpaqueWhite}};

#if (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) || \
    __IPHONE_OS_VERSION_MAX_ALLOWED >= 130000
struct {
  HgiComponentSwizzle hgiComponentSwizzle;
  MTL::TextureSwizzle metalCS;
} static const _componentSwizzleTable[HgiComponentSwizzleCount] = {
    {HgiComponentSwizzleZero, MTL::TextureSwizzleZero},
    {HgiComponentSwizzleOne, MTL::TextureSwizzleOne},
    {HgiComponentSwizzleR, MTL::TextureSwizzleRed},
    {HgiComponentSwizzleG, MTL::TextureSwizzleGreen},
    {HgiComponentSwizzleB, MTL::TextureSwizzleBlue},
    {HgiComponentSwizzleA, MTL::TextureSwizzleAlpha}};
#endif

struct {
  HgiPrimitiveType hgiPrimitiveType;
  MTL::PrimitiveTopologyClass metalTC;
} static const _primitiveClassTable[HgiPrimitiveTypeCount] = {
    {HgiPrimitiveTypePointList, MTL::PrimitiveTopologyClassPoint},
    {HgiPrimitiveTypeLineList, MTL::PrimitiveTopologyClassLine},
    {HgiPrimitiveTypeLineStrip, MTL::PrimitiveTopologyClassLine},
    {HgiPrimitiveTypeTriangleList, MTL::PrimitiveTopologyClassTriangle},
    {HgiPrimitiveTypePatchList, MTL::PrimitiveTopologyClassTriangle},
    {HgiPrimitiveTypeLineListWithAdjacency, MTL::PrimitiveTopologyClassUnspecified}};

struct {
  HgiPrimitiveType hgiPrimitiveType;
  MTL::PrimitiveType metalPT;
} static const _primitiveTypeTable[HgiPrimitiveTypeCount] = {
    {HgiPrimitiveTypePointList, MTL::PrimitiveTypePoint},
    {HgiPrimitiveTypeLineList, MTL::PrimitiveTypeLine},
    {HgiPrimitiveTypeLineStrip, MTL::PrimitiveTypeLineStrip},
    {HgiPrimitiveTypeTriangleList, MTL::PrimitiveTypeTriangle},
    {HgiPrimitiveTypePatchList, MTL::PrimitiveTypeTriangle /*Invalid*/},
    {HgiPrimitiveTypeLineListWithAdjacency, MTL::PrimitiveTypeTriangle /*Invalid*/}};

MTL::PixelFormat HgiMetalConversions::GetPixelFormat(HgiFormat inFormat, HgiTextureUsage inUsage)
{
  if (inFormat == HgiFormatInvalid) {
    return MTL::PixelFormatInvalid;
  }

  if ((inFormat < 0) || (inFormat >= HgiFormatCount)) {
    TF_CODING_ERROR("Unexpected HgiFormat %d", inFormat);
    return MTL::PixelFormatRGBA8Unorm;
  }

  if (inUsage & HgiTextureUsageBitsDepthTarget) {
    if (inFormat == HgiFormatFloat32UInt8) {
      return MTL::PixelFormatDepth32Float_Stencil8;
    }
    else {
      return MTL::PixelFormatDepth32Float;
    }
  }

  MTL::PixelFormat outFormat = _PIXEL_FORMAT_DESC[inFormat];
  if (outFormat == MTL::PixelFormatInvalid) {
    TF_CODING_ERROR("Unsupported HgiFormat %d", inFormat);
    return MTL::PixelFormatRGBA8Unorm;
  }
  return outFormat;
}

MTL::VertexFormat HgiMetalConversions::GetVertexFormat(HgiFormat inFormat)
{
  if ((inFormat < 0) || (inFormat >= HgiFormatCount)) {
    TF_CODING_ERROR("Unexpected HgiFormat %d", inFormat);
    return MTL::VertexFormatFloat4;
  }

  MTL::VertexFormat outFormat = _VERTEX_FORMAT_DESC[inFormat];
  if (outFormat == MTL::VertexFormatInvalid) {
    TF_CODING_ERROR("Unsupported HgiFormat %d", inFormat);
    return MTL::VertexFormatFloat4;
  }
  return outFormat;
}

MTL::CullMode HgiMetalConversions::GetCullMode(HgiCullMode cm)
{
  return _CullModeTable[cm].metalCullMode;
}

MTL::TriangleFillMode HgiMetalConversions::GetPolygonMode(HgiPolygonMode pm)
{
  return _PolygonModeTable[pm].metalFillMode;
}

MTL::BlendFactor HgiMetalConversions::GetBlendFactor(HgiBlendFactor bf)
{
  return _blendFactorTable[bf].metalBlendFactor;
}

MTL::BlendOperation HgiMetalConversions::GetBlendEquation(HgiBlendOp bo)
{
  return _blendEquationTable[bo].metalBlendOp;
}

MTL::Winding HgiMetalConversions::GetWinding(HgiWinding winding)
{
  return _windingTable[winding].metalWinding;
}

MTL::LoadAction HgiMetalConversions::GetAttachmentLoadOp(HgiAttachmentLoadOp loadOp)
{
  return _attachmentLoadOpTable[loadOp].metalLoadOp;
}

MTL::StoreAction HgiMetalConversions::GetAttachmentStoreOp(HgiAttachmentStoreOp storeOp)
{
  return _attachmentStoreOpTable[storeOp].metalStoreOp;
}

MTL::CompareFunction HgiMetalConversions::GetCompareFunction(HgiCompareFunction cf)
{
  return _compareFnTable[cf].metalCF;
}

MTL::StencilOperation HgiMetalConversions::GetStencilOp(HgiStencilOp op)
{
  return _stencilOpTable[op].metalStencilOp;
}

MTL::TextureType HgiMetalConversions::GetTextureType(HgiTextureType tt)
{
  return _textureTypeTable[tt].metalTT;
}

MTL::SamplerAddressMode HgiMetalConversions::GetSamplerAddressMode(HgiSamplerAddressMode a)
{
  return _samplerAddressModeTable[a].metalAM;
}

MTL::SamplerMinMagFilter HgiMetalConversions::GetMinMagFilter(HgiSamplerFilter mf)
{
  return _samplerFilterTable[mf].metalSF;
}

MTL::SamplerMipFilter HgiMetalConversions::GetMipFilter(HgiMipFilter mf)
{
  return _mipFilterTable[mf].metalMF;
}

MTL::SamplerBorderColor HgiMetalConversions::GetBorderColor(HgiBorderColor bc)
{
  return _borderColorTable[bc].metalBC;
}

#if (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) || \
    __IPHONE_OS_VERSION_MAX_ALLOWED >= 130000
MTL::TextureSwizzle HgiMetalConversions::GetComponentSwizzle(HgiComponentSwizzle componentSwizzle)
{
  return _componentSwizzleTable[componentSwizzle].metalCS;
}
#endif

MTL::PrimitiveTopologyClass HgiMetalConversions::GetPrimitiveClass(HgiPrimitiveType pt)
{
  return _primitiveClassTable[pt].metalTC;
}

MTL::PrimitiveType HgiMetalConversions::GetPrimitiveType(HgiPrimitiveType pt)
{
  return _primitiveTypeTable[pt].metalPT;
}

MTL::ColorWriteMask HgiMetalConversions::GetColorWriteMask(HgiColorMask mask)
{
  MTL::ColorWriteMask mtlMask;

  mtlMask = ((mask & HgiColorMaskRed) ? MTL::ColorWriteMaskRed : 0) |
            ((mask & HgiColorMaskGreen) ? MTL::ColorWriteMaskGreen : 0) |
            ((mask & HgiColorMaskBlue) ? MTL::ColorWriteMaskBlue : 0) |
            ((mask & HgiColorMaskAlpha) ? MTL::ColorWriteMaskAlpha : 0);

  return mtlMask;
}

PXR_NAMESPACE_CLOSE_SCOPE
