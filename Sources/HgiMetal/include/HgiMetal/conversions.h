//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_CONVERSIONS_H
#define PXR_IMAGING_HGI_METAL_CONVERSIONS_H

#include "Hgi/enums.h"
#include "Hgi/types.h"
#include "HgiMetal/api.h"
#include "pxr/pxrns.h"
#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

///
/// \class HgiMetalConversions
///
/// Converts from Hgi types to Metal types.
///
class HgiMetalConversions final {
 public:
  //
  // Hgi to Metal conversions
  //

  HGIMETAL_API
  static MTL::PixelFormat GetPixelFormat(HgiFormat inFormat, HgiTextureUsage inUsage);

  HGIMETAL_API
  static MTL::VertexFormat GetVertexFormat(HgiFormat inFormat);

  HGIMETAL_API
  static MTL::CullMode GetCullMode(HgiCullMode cm);

  HGIMETAL_API
  static MTL::TriangleFillMode GetPolygonMode(HgiPolygonMode pm);

  HGIMETAL_API
  static MTL::BlendFactor GetBlendFactor(HgiBlendFactor bf);

  HGIMETAL_API
  static MTL::BlendOperation GetBlendEquation(HgiBlendOp bo);

  HGIMETAL_API
  static MTL::Winding GetWinding(HgiWinding winding);

  HGIMETAL_API
  static MTL::LoadAction GetAttachmentLoadOp(HgiAttachmentLoadOp loadOp);

  HGIMETAL_API
  static MTL::StoreAction GetAttachmentStoreOp(HgiAttachmentStoreOp storeOp);

  HGIMETAL_API
  static MTL::CompareFunction GetCompareFunction(HgiCompareFunction cf);

  HGIMETAL_API
  static MTL::StencilOperation GetStencilOp(HgiStencilOp op);

  HGIMETAL_API
  static MTL::TextureType GetTextureType(HgiTextureType tt);

  HGIMETAL_API
  static MTL::SamplerAddressMode GetSamplerAddressMode(HgiSamplerAddressMode a);

  HGIMETAL_API
  static MTL::SamplerMinMagFilter GetMinMagFilter(HgiSamplerFilter mf);

  HGIMETAL_API
  static MTL::SamplerMipFilter GetMipFilter(HgiMipFilter mf);

  HGIMETAL_API
  static MTL::SamplerBorderColor GetBorderColor(HgiBorderColor bc);

#if (defined(__MAC_10_15) && __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_15) || \
    __IPHONE_OS_VERSION_MAX_ALLOWED >= 130000
  HGIMETAL_API
  static MTL::TextureSwizzle GetComponentSwizzle(HgiComponentSwizzle);
#endif

  HGIMETAL_API
  static MTL::PrimitiveTopologyClass GetPrimitiveClass(HgiPrimitiveType pt);

  HGIMETAL_API
  static MTL::PrimitiveType GetPrimitiveType(HgiPrimitiveType pt);

  HGIMETAL_API
  static MTL::ColorWriteMask GetColorWriteMask(HgiColorMask mask);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
