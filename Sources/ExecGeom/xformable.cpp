//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "ExecGeom/tokens.h"

#include "Exec/registerSchema.h"

#include "Gf/matrix4d.h"
#include "Tf/staticTokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,

    ((xformOpTransform, "xformOp:transform"))
);

static GfMatrix4d
_ComputeLocalToWorldTransform(const VdfContext &ctx)
{
    const GfMatrix4d *const localToParent =
        ctx.GetInputValuePtr<GfMatrix4d>(
            _tokens->xformOpTransform);

    const GfMatrix4d *const parentToWorld =
        ctx.GetInputValuePtr<GfMatrix4d>(
            ExecGeomXformableTokens->computeLocalToWorldTransform);

    // The computed local-to-world matrix is the local matrix multiplied with
    // the parent local-to-world, if we have both. If we are missing either
    // value, then the matrix we have provides the local-to-world transform. And
    // if we have neither, we fall back to the identity matrix.
    if (parentToWorld) {
        return localToParent
            ? (*localToParent) * (*parentToWorld)
            : (*parentToWorld);
    } else {
        return localToParent
            ? (*localToParent)
            : GfMatrix4d(1.0);
    }
}

EXEC_REGISTER_COMPUTATIONS_FOR_SCHEMA(UsdGeomXformable)
{
    self.PrimComputation(ExecGeomXformableTokens->computeLocalToWorldTransform)
        .Callback<GfMatrix4d>(&_ComputeLocalToWorldTransform)
        .Inputs(
            AttributeValue<GfMatrix4d>(
                _tokens->xformOpTransform),
            NamespaceAncestor<GfMatrix4d>(
                ExecGeomXformableTokens->computeLocalToWorldTransform)
        );
}

