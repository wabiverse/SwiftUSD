//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_GL_CONVERSIONS_H
#define PXR_IMAGING_HD_ST_GL_CONVERSIONS_H

#include "Garch/glApi.h"
#include "Hd/enums.h"
#include "Hd/types.h"
#include "HdSt/api.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSt_GeometricShader;

class HdStGLConversions {
 public:
  HDST_API
  static GLenum GetGlDepthFunc(HdCompareFunction func);

  HDST_API
  static GLenum GetGlStencilFunc(HdCompareFunction func);

  HDST_API
  static GLenum GetGlStencilOp(HdStencilOp op);

  HDST_API
  static GLenum GetGlBlendOp(HdBlendOp op);

  HDST_API
  static GLenum GetGlBlendFactor(HdBlendFactor factor);

  HDST_API
  static GLenum GetGLAttribType(HdType type);

  HDST_API
  static GLenum GetPrimitiveMode(HdSt_GeometricShader const *geometricShader);

  /// Return the name of the given type as represented in GLSL.
  HDST_API
  static TfToken GetGLSLTypename(HdType type);

  /// Return a GLSL-safe, mangled name identifier.
  HDST_API
  static TfToken GetGLSLIdentifier(TfToken const &identifier);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_GL_CONVERSIONS_H
