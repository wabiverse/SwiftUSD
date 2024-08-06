//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/flattenedDataSourceProviders.h"

#include "UsdImaging/directMaterialBindingsSchema.h"
#include "UsdImaging/flattenedDirectMaterialBindingsDataSourceProvider.h"
#include "UsdImaging/flattenedGeomModelDataSourceProvider.h"
#include "UsdImaging/geomModelSchema.h"
#include "UsdImaging/modelSchema.h"

#include "Hd/flattenedDataSourceProviders.h"
#include "Hd/flattenedOverlayDataSourceProvider.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/retainedDataSource.h"

PXR_NAMESPACE_OPEN_SCOPE

HdContainerDataSourceHandle UsdImagingFlattenedDataSourceProviders()
{
  using namespace HdMakeDataSourceContainingFlattenedDataSourceProvider;

  static HdContainerDataSourceHandle const result = HdOverlayContainerDataSource::New(
      {HdRetainedContainerDataSource::New(
           UsdImagingDirectMaterialBindingsSchema::GetSchemaToken(),
           Make<UsdImagingFlattenedDirectMaterialBindingsDataSourceProvider>()),

       HdRetainedContainerDataSource::New(UsdImagingGeomModelSchema::GetSchemaToken(),
                                          Make<UsdImagingFlattenedGeomModelDataSourceProvider>()),

       HdRetainedContainerDataSource::New(UsdImagingModelSchema::GetSchemaToken(),
                                          Make<HdFlattenedOverlayDataSourceProvider>()),

       HdFlattenedDataSourceProviders()});

  return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
