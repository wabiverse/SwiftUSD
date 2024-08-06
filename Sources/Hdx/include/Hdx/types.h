//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDX_TYPES_H
#define PXR_IMAGING_HDX_TYPES_H

#include "Hdx/api.h"
#include "Hdx/version.h"
#include "Hgi/types.h"
#include "Hio/types.h"
#include "Tf/token.h"
#include "Vt/dictionary.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

// Struct used to send shader inputs from Presto and send them to Hydra
struct HdxShaderInputs {
  VtDictionary parameters;
  VtDictionary textures;
  VtDictionary textureFallbackValues;
  TfTokenVector attributes;
  VtDictionary metaData;
};

HDX_API
bool operator==(const HdxShaderInputs &lhs, const HdxShaderInputs &rhs);
HDX_API
bool operator!=(const HdxShaderInputs &lhs, const HdxShaderInputs &rhs);
HDX_API
std::ostream &operator<<(std::ostream &out, const HdxShaderInputs &pv);

/// Returns the HioFormat for the given HgiFormat
HDX_API
HioFormat HdxGetHioFormat(HgiFormat hgiFormat);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HDX_TYPES_H
