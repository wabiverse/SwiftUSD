//
// Copyright 2023 Pixar
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

#include "Hd/flattenedDataSourceProviders.h"

#include "Hd/flattenedMaterialBindingsDataSourceProvider.h"
#include "Hd/flattenedOverlayDataSourceProvider.h"
#include "Hd/flattenedPrimvarsDataSourceProvider.h"
#include "Hd/flattenedPurposeDataSourceProvider.h"
#include "Hd/flattenedVisibilityDataSourceProvider.h"
#include "Hd/flattenedXformDataSourceProvider.h"
#include "Hd/coordSysBindingSchema.h"
#include "Hd/materialBindingsSchema.h"
#include "Hd/primvarSchema.h"
#include "Hd/primvarsSchema.h"
#include "Hd/purposeSchema.h"
#include "Hd/visibilitySchema.h"
#include "Hd/xformSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

HdContainerDataSourceHandle
HdFlattenedDataSourceProviders()
{
    using namespace HdMakeDataSourceContainingFlattenedDataSourceProvider;

    static HdContainerDataSourceHandle const result =
        HdRetainedContainerDataSource::New(
            HdCoordSysBindingSchema::GetSchemaToken(),
            Make<HdFlattenedOverlayDataSourceProvider>(),
            HdMaterialBindingsSchema::GetSchemaToken(),
            Make<HdFlattenedMaterialBindingsDataSourceProvider>(),
            HdPrimvarsSchema::GetSchemaToken(),
            Make<HdFlattenedPrimvarsDataSourceProvider>(),
            HdPurposeSchema::GetSchemaToken(),
            Make<HdFlattenedPurposeDataSourceProvider>(),
            HdVisibilitySchema::GetSchemaToken(),
            Make<HdFlattenedVisibilityDataSourceProvider>(),
            HdXformSchema::GetSchemaToken(),
            Make<HdFlattenedXformDataSourceProvider>());

    return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
