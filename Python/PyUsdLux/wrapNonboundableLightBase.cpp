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
#include "UsdLux/nonboundableLightBase.h"
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


static std::string
_Repr(const UsdLuxNonboundableLightBase &self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdLux.NonboundableLightBase(%s)",
        primRepr.c_str());
}

} // anonymous namespace

void wrapUsdLuxNonboundableLightBase()
{
    typedef UsdLuxNonboundableLightBase This;

    class_<This, bases<UsdGeomXformable> >
        cls("NonboundableLightBase");

    cls
        .def(init<UsdPrim>(arg("prim")))
        .def(init<UsdSchemaBase const&>(arg("schemaObj")))
        .def(TfTypePythonClass())

        .def("Get", &This::Get, (arg("stage"), arg("path")))
        .staticmethod("Get")

        .def("GetSchemaAttributeNames",
             &This::GetSchemaAttributeNames,
             arg("includeInherited")=true,
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetSchemaAttributeNames")

        .def("_GetStaticTfType", (TfType const &(*)()) TfType::Find<This>,
             return_value_policy<return_by_value>())
        .staticmethod("_GetStaticTfType")

        .def(!self)


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

static UsdAttribute
_CreateIntensityAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateIntensityAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float), writeSparsely);
}
        
static UsdAttribute
_CreateExposureAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateExposureAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float), writeSparsely);
}
        
static UsdAttribute
_CreateDiffuseAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateDiffuseAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float), writeSparsely);
}
        
static UsdAttribute
_CreateSpecularAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateSpecularAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float), writeSparsely);
}
        
static UsdAttribute
_CreateNormalizeAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateNormalizeAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool), writeSparsely);
}
        
static UsdAttribute
_CreateColorAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateColorAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Color3f), writeSparsely);
}
        
static UsdAttribute
_CreateEnableColorTemperatureAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateEnableColorTemperatureAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool), writeSparsely);
}
        
static UsdAttribute
_CreateColorTemperatureAttr(UsdLuxNonboundableLightBase &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateColorTemperatureAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float), writeSparsely);
}

namespace {

WRAP_CUSTOM {
    typedef UsdLuxNonboundableLightBase This;

    _class
        .def("GetIntensityAttr",
             &This::GetIntensityAttr)
        .def("CreateIntensityAttr",
             &_CreateIntensityAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetExposureAttr",
             &This::GetExposureAttr)
        .def("CreateExposureAttr",
             &_CreateExposureAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetDiffuseAttr",
             &This::GetDiffuseAttr)
        .def("CreateDiffuseAttr",
             &_CreateDiffuseAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetSpecularAttr",
             &This::GetSpecularAttr)
        .def("CreateSpecularAttr",
             &_CreateSpecularAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetNormalizeAttr",
             &This::GetNormalizeAttr)
        .def("CreateNormalizeAttr",
             &_CreateNormalizeAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetColorAttr",
             &This::GetColorAttr)
        .def("CreateColorAttr",
             &_CreateColorAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetEnableColorTemperatureAttr",
             &This::GetEnableColorTemperatureAttr)
        .def("CreateEnableColorTemperatureAttr",
             &_CreateEnableColorTemperatureAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetColorTemperatureAttr",
             &This::GetColorTemperatureAttr)
        .def("CreateColorTemperatureAttr",
             &_CreateColorTemperatureAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("GetFiltersRel",
             &This::GetFiltersRel)
        .def("CreateFiltersRel",
             &This::CreateFiltersRel)

        .def("LightAPI", &This::LightAPI)
        ;
}

}
