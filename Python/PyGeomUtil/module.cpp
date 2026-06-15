//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Tf/pyModule.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
    TF_WRAP(Tokens);
    TF_WRAP(CapsuleMeshGenerator);
    TF_WRAP(ConeMeshGenerator);
    TF_WRAP(CuboidMeshGenerator);
    TF_WRAP(CylinderMeshGenerator);
    TF_WRAP(DiskMeshGenerator);
    TF_WRAP(PlaneMeshGenerator);
    TF_WRAP(SphereMeshGenerator);
}
