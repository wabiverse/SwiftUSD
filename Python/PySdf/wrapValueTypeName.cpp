//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Sdf/valueTypeName.h"
#include "Tf/type.h"
#include "Vt/value.h"
#include "Tf/pyResultConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void
wrapValueType()
{
    class_<SdfValueTypeName>("ValueTypeName", no_init)
        .def(init<>())
        .def(!self)
        .def(self == std::string())
        .def(self != std::string())
        .def(self == self)
        .def(self != self)
        .def("__hash__", &SdfValueTypeName::GetHash)
        .def("__str__", &SdfValueTypeName::GetAsToken)
        .add_property("type",
            make_function(&SdfValueTypeName::GetType,
                          return_value_policy<return_by_value>()))
        .add_property("cppTypeName",
            make_function(&SdfValueTypeName::GetCPPTypeName,
                          return_value_policy<return_by_value>()))
        .add_property("role",
            make_function(&SdfValueTypeName::GetRole,
                          return_value_policy<return_by_value>()))
        .add_property("defaultValue",
            make_function(&SdfValueTypeName::GetDefaultValue,
                          return_value_policy<return_by_value>()))
        .add_property("defaultUnit",
            make_function(&SdfValueTypeName::GetDefaultUnit,
                          return_value_policy<return_by_value>()))
        .add_property("scalarType", &SdfValueTypeName::GetScalarType)
        .add_property("arrayType", &SdfValueTypeName::GetArrayType)
        .add_property("isScalar", &SdfValueTypeName::IsScalar)
        .add_property("isArray", &SdfValueTypeName::IsArray)
        .add_property("aliasesAsStrings",
            make_function(&SdfValueTypeName::GetAliasesAsTokens,
                          return_value_policy<return_by_value>()))
        ;
}
