//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "ExecUsd/valueKey.h"

#include "Arch/demangle.h"
#include "Tf/diagnostic.h"
#include "Exec/builtinComputations.h"

#include <typeinfo>
#include <utility>
#include <variant>

PXR_NAMESPACE_OPEN_SCOPE

ExecUsdValueKey::ExecUsdValueKey(const UsdAttribute &provider)
    : _key(ExecUsd_AttributeComputationValueKey{
            provider, ExecBuiltinComputations->computeValue})
{}

ExecUsdValueKey::ExecUsdValueKey(
    const UsdAttribute &provider, const TfToken &computation)
    : _key(ExecUsd_AttributeComputationValueKey{provider, computation})
{}

ExecUsdValueKey::ExecUsdValueKey(
    const UsdPrim &provider, const TfToken &computation)
    : _key(ExecUsd_PrimComputationValueKey{provider, computation})
{}

ExecUsdValueKey::~ExecUsdValueKey() = default;

PXR_NAMESPACE_CLOSE_SCOPE
