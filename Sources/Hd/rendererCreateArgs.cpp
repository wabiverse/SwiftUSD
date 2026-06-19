//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Hd/rendererCreateArgs.h"

#include "Hd/rendererCreateArgsSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

HdRendererCreateArgs::HdRendererCreateArgs(
    const HdRendererCreateArgsSchema &schema)
{
    if (HdBoolDataSourceHandle const ds = schema.GetGpuEnabled()) {
        gpuEnabled = ds->GetTypedValue(0.0f);
    }

    if (auto const ds =
            HdTypedSampledDataSource<Hgi*>::Cast(
                schema
                    .GetDrivers()
                    .Get(HdRendererCreateArgsSchemaTokens->hgi))) {
        hgi = ds->GetTypedValue(0.0f);
    }
    
}

PXR_NAMESPACE_CLOSE_SCOPE

