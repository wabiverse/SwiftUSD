//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Hd/flattenedDataSourceProviders.h"

#include "Hd/coordSysBindingSchema.h"
#include "Hd/flattenedOverlayDataSourceProvider.h"
#include "Hd/flattenedPrimvarsDataSourceProvider.h"
#include "Hd/flattenedPurposeDataSourceProvider.h"
#include "Hd/flattenedVisibilityDataSourceProvider.h"
#include "Hd/flattenedXformDataSourceProvider.h"
#include "Hd/materialBindingsSchema.h"
#include "Hd/primvarSchema.h"
#include "Hd/primvarsSchema.h"
#include "Hd/purposeSchema.h"
#include "Hd/visibilitySchema.h"
#include "Hd/xformSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

HdContainerDataSourceHandle HdFlattenedDataSourceProviders()
{
  using namespace HdMakeDataSourceContainingFlattenedDataSourceProvider;

  static HdContainerDataSourceHandle const result = HdRetainedContainerDataSource::New(
      HdCoordSysBindingSchema::GetSchemaToken(),
      Make<HdFlattenedOverlayDataSourceProvider>(),
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
