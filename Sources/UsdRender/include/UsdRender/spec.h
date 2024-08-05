//
// Copyright 2016 Pixar
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
#ifndef PXR_USD_USD_RENDER_SPEC_H
#define PXR_USD_USD_RENDER_SPEC_H

/// \file usdRender/spec.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdRender/api.h"
#include "UsdRender/settingsBase.h"
#include "UsdRender/tokens.h"
#include <pxr/pxrns.h>

#include "Gf/frustum.h"

#include "Vt/dictionary.h"
#include "Vt/value.h"

#include "Gf/matrix4d.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdRenderSettings;

/// A self-contained specification of render settings.
/// \note This is preliminary API and is likely to change.
struct UsdRenderSpec {
  /// Specification of a product.  See UsdRenderProduct.
  struct Product {
    /// The path of this product, which uniquely identifies it.
    SdfPath renderProductPath;
    /// The type of product, ex: "raster".
    TfToken type;
    /// The name of the product, which uniquely identifies it.
    TfToken name;
    /// Path to the primary UsdGeomCamera camera to use for this product.
    SdfPath cameraPath;
    /// If set to true, disables motion blur.
    bool disableMotionBlur;
    /// The pixel resolution of the product.
    GfVec2i resolution;
    /// The pixel aspect ratio as adjusted by aspectRatioConformPolicy.
    float pixelAspectRatio;
    /// The policy that was applied to conform aspect ratio
    /// mismatches between the aperture and image.
    TfToken aspectRatioConformPolicy;
    /// The camera aperture size as adjusted by aspectRatioConformPolicy.
    GfVec2f apertureSize;
    /// The data window, in NDC terms relative to the aperture.
    /// (0,0) corresponds to bottom-left and (1,1) corresponds to
    /// top-right.  Note that the data window can partially cover
    /// or extend beyond the unit range, for representing overscan
    /// or cropped renders.
    GfRange2f dataWindowNDC;
    /// The render vars used by this product, as indices into the
    /// top-level renderVars array.
    std::vector<size_t> renderVarIndices;
    /// Any extra settings values discovered in requested namespaces.
    VtDictionary namespacedSettings;
  };
  /// Specification of a render variable (aka AOV).  See UsdRenderVar.
  struct RenderVar {
    /// The path of this render var, which uniquely identifies it.
    SdfPath renderVarPath;
    /// The value data type of the variable, as a USD type name.
    TfToken dataType;
    std::string sourceName;
    TfToken sourceType;
    /// Any extra settings values discovered in requested namespaces.
    VtDictionary namespacedSettings;
  };
  /// The full list of products requested by this render.
  std::vector<Product> products;
  /// The full list of render vars requested by products in this render.
  std::vector<RenderVar> renderVars;
  /// List of purposes to use to filter scene contents.
  VtArray<TfToken> includedPurposes;
  /// List of material binding purposes.
  VtArray<TfToken> materialBindingPurposes;
  /// Any extra settings values discovered in requested namespaces.
  VtDictionary namespacedSettings;
};

/// Computes the specification of the render settings.
/// For each product, applies the aspectRatioConformPolicy
/// and computes a final screenWindow and pixelAspectRatio.
///
/// Any other attributes encountered are returned in namespacedSettings.
/// If a non-empty list of namespaces is provided, only attributes
/// within those namespaces are returned.
/// If an empty list of namespaces is provided, all custom
/// (non-schema) attributes are returned.
/// The same list of namespaces is used for finding namespacedSettings
/// in all UsdRender prim types.
USDRENDER_API
UsdRenderSpec UsdRenderComputeSpec(UsdRenderSettings const &settings,
                                   TfTokenVector const &namespaces);

/// Returns a dictionary populated with attributes filtered by the namespaces.
/// If a non-empty list of namespaces is provided, only authored attributes
/// within those namespaces are returned.
/// If an empty list of namespaces is provided, all custom (non-schema)
/// attributes are returned.
/// \note Special handling is provided for connectable attributes that are used
///       to represent node graph outputs.
USDRENDER_API
VtDictionary UsdRenderComputeNamespacedSettings(UsdPrim const &prim,
                                                TfTokenVector const &namespaces);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
