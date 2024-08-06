//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_MATERIALX_FILTER_H
#define PXR_IMAGING_HD_ST_MATERIALX_FILTER_H

#include "Hd/material.h"
#include "HdSt/materialNetwork.h"
#include "HdSt/tokens.h"
#include "Sdf/path.h"
#include "pxr/pxrns.h"
#include <MaterialX/MXCoreDocument.h>
#include <MaterialX/MXFormatUtil.h>
#include <MaterialXGenShader/Shader.h>

PXR_NAMESPACE_OPEN_SCOPE

// Storing MaterialX-Hydra counterparts and other Hydra specific information
struct HdSt_MxShaderGenInfo {
  HdSt_MxShaderGenInfo()
      : textureMap(MaterialX::StringMap()),
        primvarMap(MaterialX::StringMap()),
        primvarDefaultValueMap(MaterialX::StringMap()),
        defaultTexcoordName("st"),
        materialTag(HdStMaterialTagTokens->defaultMaterialTag.GetString()),
        bindlessTexturesEnabled(false)
  {
  }
  MaterialX::StringMap textureMap;
  MaterialX::StringMap primvarMap;
  MaterialX::StringMap primvarDefaultValueMap;
  std::string defaultTexcoordName;
  std::string materialTag;
  bool bindlessTexturesEnabled;
};

/// MaterialX Filter
/// Converting a MaterialX node to one with a generated MaterialX glslfx file
MaterialX::ShaderPtr HdSt_ApplyMaterialXFilter(HdMaterialNetwork2 *hdNetwork,
                                               SdfPath const &materialPath,
                                               HdMaterialNode2 const &terminalNode,
                                               SdfPath const &terminalNodePath,
                                               HdSt_MaterialParamVector *materialParams,
                                               HdStResourceRegistry *resourceRegistry);

// Generates the glsfx shader for the given MaterialX Document
MaterialX::ShaderPtr HdSt_GenMaterialXShader(
    MaterialX::DocumentPtr const &mxDoc,
    MaterialX::DocumentPtr const &stdLibraries,
    MaterialX::FileSearchPath const &searchPath,
    HdSt_MxShaderGenInfo const &mxHdInfo = HdSt_MxShaderGenInfo(),
    TfToken const &apiName = TfToken());

PXR_NAMESPACE_CLOSE_SCOPE

#endif
