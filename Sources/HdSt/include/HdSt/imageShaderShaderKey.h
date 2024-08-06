//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_IMAGE_SHADER_SHADER_KEY_H
#define PXR_IMAGING_HD_ST_IMAGE_SHADER_SHADER_KEY_H

#include "Hd/enums.h"
#include "Hd/version.h"
#include "HdSt/geometricShader.h"
#include "HdSt/shaderKey.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

struct HdSt_ImageShaderShaderKey : public HdSt_ShaderKey {
  HdSt_ImageShaderShaderKey();
  ~HdSt_ImageShaderShaderKey();

  TfToken const &GetGlslfxFilename() const override
  {
    return glslfx;
  }
  TfToken const *GetVS() const override
  {
    return VS;
  }
  TfToken const *GetFS() const override
  {
    return FS;
  }

  HdSt_GeometricShader::PrimitiveType GetPrimitiveType() const override
  {
    return HdSt_GeometricShader::PrimitiveType::PRIM_MESH_COARSE_TRIANGLES;
  }

  TfToken glslfx;
  TfToken VS[2];
  TfToken FS[2];
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
