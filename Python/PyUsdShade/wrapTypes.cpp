//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "UsdShade/types.h"
#include "UsdShade/connectableAPI.h"

#include "Tf/pyContainerConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/enum.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdShadeTypes()
{
    enum_<UsdShadeAttributeType>("AttributeType")
        .value("Invalid", UsdShadeAttributeType::Invalid)
        .value("Input", UsdShadeAttributeType::Input)
        .value("Output", UsdShadeAttributeType::Output)
        ;

    enum_<UsdShadeConnectionModification>("ConnectionModification")
        .value("Replace", UsdShadeConnectionModification::Replace)
        .value("Prepend", UsdShadeConnectionModification::Prepend)
        .value("Append", UsdShadeConnectionModification::Append)
        ;

    to_python_converter<
        UsdShadeAttributeVector,
        TfPySequenceToPython<UsdShadeAttributeVector>>();
    TfPyContainerConversions::from_python_sequence<
        UsdShadeAttributeVector,
        TfPyContainerConversions::variable_capacity_policy>();

    to_python_converter<
        UsdShadeSourceInfoVector,
        TfPySequenceToPython<UsdShadeSourceInfoVector>>();
    TfPyContainerConversions::from_python_sequence<
        UsdShadeSourceInfoVector,
        TfPyContainerConversions::variable_capacity_policy>();
}
