//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_POINTS_SHADER_KEY_H
#define PXR_IMAGING_HD_ST_POINTS_SHADER_KEY_H

#include "Hd/enums.h"
#include "Hd/version.h"
#include "HdSt/geometricShader.h"
#include "HdSt/shaderKey.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

struct HdSt_PointsShaderKey : public HdSt_ShaderKey {
  HDST_API
  HdSt_PointsShaderKey();
  HDST_API
  ~HdSt_PointsShaderKey();

  TfToken const &GetGlslfxFilename() const override
  {
    return glslfx;
  }
  TfToken const *GetVS() const override
  {
    return VS;
  }
  // Skip TCS, TES and GS stages
  TfToken const *GetFS() const override
  {
    return FS;
  }

  HdSt_GeometricShader::PrimitiveType GetPrimitiveType() const override
  {
    return HdSt_GeometricShader::PrimitiveType::PRIM_POINTS;
  }

  TfToken glslfx;
  TfToken VS[6];
  TfToken FS[6];
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // HDST_POINTS_SHADER_KEY
