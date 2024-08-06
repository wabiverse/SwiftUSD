//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_MATERIAL_PARAM_H
#define PXR_IMAGING_HD_ST_MATERIAL_PARAM_H

#include "Hd/types.h"
#include "HdSt/api.h"
#include "HdSt/enums.h"
#include "Sdf/path.h"
#include "Vt/value.h"
#include "pxr/pxrns.h"

#include "Tf/token.h"

#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

using HdSt_MaterialParamVector = std::vector<class HdSt_MaterialParam>;

// XXX: Docs
class HdSt_MaterialParam final {
 public:
  typedef size_t ID;

  // Indicates the kind of material parameter.
  enum ParamType {
    // This is a shader specified fallback value that is
    // not connected to either a primvar or texture.
    ParamTypeFallback,
    // This is a parameter that is connected to a texture.
    ParamTypeTexture,
    // Creates an accessor HdGet_name() that either reads a
    // primvar with a potentially different name (given in
    // samplerCoords) if it exists or uses the fallback value.
    // It corresponds to a primvar reader shading node.
    ParamTypePrimvarRedirect,
    // Creates an accessor HdGet_name(vec3) that either reads
    // from a field texture with a potentially different name (given
    // in samplerCoords) if it exists or uses the fallback value.
    // It corresponds to a field reader shading node.
    ParamTypeFieldRedirect,
    // Additional primvar needed by material. One that is not connected to
    // a input parameter (ParamTypePrimvar).
    ParamTypeAdditionalPrimvar,
    // This is a parameter that is connected to a transform2d node
    ParamTypeTransform2d
  };

  HDST_API
  HdSt_MaterialParam();

  HDST_API
  HdSt_MaterialParam(ParamType paramType,
                     TfToken const &name,
                     VtValue const &fallbackValue,
                     TfTokenVector const &samplerCoords = TfTokenVector(),
                     HdStTextureType textureType = HdStTextureType::Uv,
                     std::string const &swizzle = std::string(),
                     bool const isPremultiplied = false,
                     size_t const arrayOfTexturesSize = 0);

  // No d'tor so that we pick up the implicitly declared default
  // move c'tor.

  /// Computes a hash for all parameters using structural information
  /// (name, texture type, primvar names) but not the fallback value.
  HDST_API
  static ID ComputeHash(HdSt_MaterialParamVector const &shaders);

  HDST_API
  HdTupleType GetTupleType() const;

  bool IsTexture() const
  {
    return paramType == ParamTypeTexture;
  }
  bool IsPrimvarRedirect() const
  {
    return paramType == ParamTypePrimvarRedirect;
  }
  bool IsFieldRedirect() const
  {
    return paramType == ParamTypeFieldRedirect;
  }
  bool IsFallback() const
  {
    return paramType == ParamTypeFallback;
  }
  bool IsAdditionalPrimvar() const
  {
    return paramType == ParamTypeAdditionalPrimvar;
  }
  bool IsTransform2d() const
  {
    return paramType == ParamTypeTransform2d;
  }
  bool IsArrayOfTextures() const
  {
    return IsTexture() && arrayOfTexturesSize > 0;
  }

  ParamType paramType;
  TfToken name;
  VtValue fallbackValue;
  TfTokenVector samplerCoords;
  HdStTextureType textureType;
  std::string swizzle;
  bool isPremultiplied;

  // If paramType is ParamTypeTexture, this indicates both if the textures
  // should be bound as an array of textures and the size of the array. If
  // arrayOfTexturesSize is 0, then do not bind as an array of textures, but
  // rather a single texture (whereas arrayOfTexturesSize = 1 indicates an
  // array of textures of size 1).
  size_t arrayOfTexturesSize;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_MATERIAL_PARAM_H
