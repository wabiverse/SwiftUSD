//
// Copyright 2016 Pixar
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
#include "UsdGeom/hermiteCurves.h"
#include "Usd/schemaBase.h"

#include "Sdf/primSpec.h"

#include "Usd/pyConversions.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

#define WRAP_CUSTOM                                                     \
    template <class Cls> static void _CustomWrapCode(Cls &_class)

// fwd decl.
WRAP_CUSTOM;

        
static UsdAttribute
_CreateTangentsAttr(UsdGeomHermiteCurves &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateTangentsAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Vector3fArray), writeSparsely);
}

static std::string
_Repr(const UsdGeomHermiteCurves &self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdGeom.HermiteCurves(%s)",
        primRepr.c_str());
}

} // anonymous namespace

void wrapUsdGeomHermiteCurves()
{
    typedef UsdGeomHermiteCurves This;

    class_<This, bases<UsdGeomCurves> >
        cls("HermiteCurves");

    cls
        .def(init<UsdPrim>(arg("prim")))
        .def(init<UsdSchemaBase const&>(arg("schemaObj")))
        .def(TfTypePythonClass())

        .def("Get", &This::Get, (arg("stage"), arg("path")))
        .staticmethod("Get")

        .def("Define", &This::Define, (arg("stage"), arg("path")))
        .staticmethod("Define")

        .def("GetSchemaAttributeNames",
             &This::GetSchemaAttributeNames,
             arg("includeInherited")=true,
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetSchemaAttributeNames")

        .def("_GetStaticTfType", (TfType const &(*)()) TfType::Find<This>,
             return_value_policy<return_by_value>())
        .staticmethod("_GetStaticTfType")

        .def(!self)

        
        .def("GetTangentsAttr",
             &This::GetTangentsAttr)
        .def("CreateTangentsAttr",
             &_CreateTangentsAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("__repr__", ::_Repr)
    ;

    _CustomWrapCode(cls);
}

// ===================================================================== //
// Feel free to add custom code below this line, it will be preserved by 
// the code generator.  The entry point for your custom code should look
// minimally like the following:
//
// WRAP_CUSTOM {
//     _class
//         .def("MyCustomMethod", ...)
//     ;
// }
//
// Of course any other ancillary or support code may be provided.
// 
// Just remember to wrap code in the appropriate delimiters:
// 'namespace {', '}'.
//
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

namespace {

static std::string _PointAndTangentsRepr(
    const UsdGeomHermiteCurves::PointAndTangentArrays &arrays) {
    return TfStringPrintf("UsdGeom.HermiteCurves(%s, %s)",
                          TfPyRepr(arrays.GetPoints()).c_str(),
                          TfPyRepr(arrays.GetTangents()).c_str());
}

WRAP_CUSTOM {
    typedef UsdGeomHermiteCurves This;
    {
        typedef UsdGeomHermiteCurves::PointAndTangentArrays ThisStruct;
        scope obj = _class;
        class_<ThisStruct>("PointAndTangentArrays", init<>())
            .def(init<const VtVec3fArray&,const VtVec3fArray&>())
            .def("GetPoints", &ThisStruct::GetPoints,
                 return_value_policy<copy_const_reference>())
            .def("GetTangents", &ThisStruct::GetTangents,
                 return_value_policy<copy_const_reference>())
            .def("IsEmpty", &ThisStruct::IsEmpty)
            .def("Interleave", &ThisStruct::Interleave)
            .def("Separate", &ThisStruct::Separate)
            .staticmethod("Separate")
            .def("__repr__", &::_PointAndTangentsRepr)
            .def(!self)
            .def(self == self)
            .def(self != self);
    }
}

}
