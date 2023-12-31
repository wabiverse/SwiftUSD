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
#include "UsdShade/nodeGraph.h"
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
_Repr(const UsdShadeNodeGraph &self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdShade.NodeGraph(%s)",
        primRepr.c_str());
}

} // anonymous namespace

void wrapUsdShadeNodeGraph()
{
    typedef UsdShadeNodeGraph This;

    class_<This, bases<UsdTyped> >
        cls("NodeGraph");

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

#include "UsdShade/connectableAPI.h"

namespace {

static object
_WrapComputeOutputSource(const UsdShadeNodeGraph &self, 
                         const TfToken &outputName)
{
    TfToken sourceName;
    UsdShadeAttributeType sourceType;
    UsdShadeShader source = self.ComputeOutputSource(outputName, &sourceName, 
            &sourceType);
    return boost::python::make_tuple (source, sourceName, sourceType);
}

WRAP_CUSTOM {
    _class
        .def(init<UsdShadeConnectableAPI>(arg("connectable")))
        .def("ConnectableAPI", &UsdShadeNodeGraph::ConnectableAPI)

        .def("CreateOutput", 
             &UsdShadeNodeGraph::CreateOutput,
             (arg("name"), arg("typeName")))
        .def("GetOutput",
             &UsdShadeNodeGraph::GetOutput,
             (arg("name")))
        .def("GetOutputs",
             &UsdShadeNodeGraph::GetOutputs,
             (arg("onlyAuthored") = true),
             return_value_policy<TfPySequenceToList>())
        .def("ComputeOutputSource", _WrapComputeOutputSource, 
             (arg("outputName")))

        .def("CreateInput", &UsdShadeNodeGraph::CreateInput,
             (arg("name"), arg("type")))
        .def("GetInput", &UsdShadeNodeGraph::GetInput, arg("name"))
        .def("GetInputs", &UsdShadeNodeGraph::GetInputs,
             (arg("onlyAuthored") = true),
             return_value_policy<TfPySequenceToList>())
        .def("GetInterfaceInputs", &UsdShadeNodeGraph::GetInterfaceInputs,
             return_value_policy<TfPySequenceToList>())

        .def("ComputeInterfaceInputConsumersMap",
             &UsdShadeNodeGraph::ComputeInterfaceInputConsumersMap,
             return_value_policy<TfPyMapToDictionary>(),
             (arg("computeTransitiveConsumers")=false))

    ;
}

} // anonymous namespace
