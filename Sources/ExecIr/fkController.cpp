//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "ExecIr/controllerBuilder.h"
#include "ExecIr/tokens.h"
#include "ExecIr/types.h"
#include "ExecIr/utils.h"

#include "Exec/registerSchema.h"
#include "Vdf/context.h"

#include "Gf/matrix4d.h"
#include "Tf/staticTokens.h"
#include "Tf/token.h"

PXR_NAMESPACE_USING_DIRECTIVE

static ExecIrResult _Compute(const VdfContext &ctx);
static ExecIrResult _Invert(const VdfContext &ctx);

EXEC_REGISTER_COMPUTATIONS_FOR_SCHEMA(ExecIrFkController)
{
    ExecIrControllerBuilder builder(self, &_Compute, &_Invert);

    builder.InvertibleInputAttribute<double>(ExecIrTokens->txToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->tyToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->tzToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->rxToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->ryToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->rzToken);
    builder.InvertibleInputAttribute<double>(ExecIrTokens->rspinToken);

    builder.NonInvertibleInputAttribute<GfMatrix4d>(
        ExecIrTokens->parentSpaceToken);

    builder.InvertibleOutputAttribute<GfMatrix4d>(ExecIrTokens->outSpaceToken);

    builder.SwitchAttribute<TfToken>(
        ExecIrTokens->rotationOrderToken);

    builder.PassthroughAttribute<GfMatrix4d>(
        ExecIrTokens->defaultSpaceToken);
}

// Returns the forward-computed result for Out:Space.
//
static ExecIrResult
_Compute(const VdfContext &ctx)
{
    const GfMatrix4d startingSpace =
        ExecIr_UtilsComputeStandardStartingSpace(ctx);

    const ExecIr_UtilsParams params = {
        startingSpace,
        ExecIr_UtilsComputeStandardTranslationOrientation(ctx, startingSpace),
        ExecIr_UtilsComputeStandardRotationOrientation(ctx, startingSpace)
    };

    const GfMatrix4d outSpaceValue = ExecIr_UtilsCompute(
        params,
        ExecIr_UtilsComputeLocalTranslation(ctx),
        ExecIr_UtilsComputeLocalRotation(ctx));

    return ExecIrResult({
        {ExecIrTokens->outSpaceToken, VtValue(outSpaceValue)}});
}

// Populates \p resultMap with inverted values that attempt to satisfy the given
// \p posedSpace.
//
static ExecIrResult
_Invert(const VdfContext &ctx)
{
    const GfMatrix4d &posedSpace =
        ctx.GetInputValue<GfMatrix4d>(ExecIrTokens->outSpaceToken);

    const GfMatrix4d startingSpace =
        ExecIr_UtilsComputeStandardStartingSpace(ctx);

    const ExecIr_UtilsParams params = {
        startingSpace,
        ExecIr_UtilsComputeStandardTranslationOrientation(ctx, startingSpace),
        ExecIr_UtilsComputeStandardRotationOrientation(ctx, startingSpace)
    };

    ExecIrResult resultMap;
    ExecIr_UtilsInvert(ctx, posedSpace, params, &resultMap);
    return resultMap;
}
