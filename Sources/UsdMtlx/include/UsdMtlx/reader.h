//
// Copyright 2018 Pixar
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
#ifndef PXR_USD_USDMTLX_READER_H
#define PXR_USD_USDMTLX_READER_H

#include <pxr/pxrns.h>
#include "UsdMtlx/api.h"
#include "Sdf/path.h"
#include "Tf/declarePtrs.h"
#include <MaterialX/MXCoreDocument.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_DECLARE_WEAK_PTRS(UsdStage);

/// Translate the MaterialX document in \p mtlx into the stage \p stage.
/// \p internalPath is a namespace path where converted MaterialX objects
/// will live. \p externalPath is a namespace path of a prim that will
/// have all of the look variants.  It will have references into
/// \p internalPath.  Clients are expected to reference the prim at
/// \p externalPath to apply looks.
///
/// Note that this method will traverse the materialx network following material
/// nodes, and does an early exit if no looks are defined in the mtlx document.
USDMTLX_API
void UsdMtlxRead(const MaterialX::ConstDocumentPtr &mtlx,
                 const UsdStagePtr &stage,
                 const SdfPath &internalPath = SdfPath("/MaterialX"),
                 const SdfPath &externalPath = SdfPath("/ModelRoot"));

/// Translate node graphs in the MaterialX document in \p mtlx into the
/// stage \p stage.  \p internalPath is a namespace path where converted
/// MaterialX objects will live.
///
/// Note that this method will traverse all the nodegraphs in the mtlx document.
USDMTLX_API
void UsdMtlxReadNodeGraphs(const MaterialX::ConstDocumentPtr &mtlx,
                           const UsdStagePtr &stage,
                           const SdfPath &internalPath = SdfPath("/MaterialX"));

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_USD_USDMTLX_READER_H
