//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_FIELD_TEXTURE_CPU_DATA_H
#define PXR_IMAGING_HD_ST_FIELD_TEXTURE_CPU_DATA_H

#include "HdSt/api.h"
#include "pxr/pxrns.h"

#include "HdSt/textureCpuData.h"
#include "Hgi/texture.h"

#include "Tf/declarePtrs.h"

#include <memory>

PXR_NAMESPACE_OPEN_SCOPE

using HioFieldTextureDataSharedPtr = std::shared_ptr<class HioFieldTextureData>;

/// \class HdStTextureCpuData
///
/// An implmentation of HdStTextureCpuData that can be initialized
/// from HioFieldTextureData.
///
class HdSt_FieldTextureCpuData : public HdStTextureCpuData {
 public:
  /// It is assumed that Read(...) has already been called
  /// on textureData.

  HDST_API
  HdSt_FieldTextureCpuData(HioFieldTextureDataSharedPtr const &textureData,
                           const std::string &debugName,
                           bool premultiplyAlpha = true);

  HDST_API
  ~HdSt_FieldTextureCpuData() override;

  HDST_API
  const HgiTextureDesc &GetTextureDesc() const override;

  HDST_API
  bool GetGenerateMipmaps() const override;

  HDST_API
  bool IsValid() const override;

 private:
  // The result, including a pointer to the potentially
  // converted texture data in _textureDesc.initialData.
  HgiTextureDesc _textureDesc;

  // If true, initialData only contains mip level 0 data
  // and the GPU is supposed to generate the other mip levels.
  bool _generateMipmaps;

  // To avoid a copy, hold on to original data if we
  // can use them.
  HioFieldTextureDataSharedPtr _textureData;

  // Buffer if we had to convert the data.
  std::unique_ptr<const unsigned char[]> _convertedData;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
