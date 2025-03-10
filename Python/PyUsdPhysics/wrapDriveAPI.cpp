//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdPhysics/driveAPI.h"

#include "Sdf/primSpec.h"

#include "Tf/pyAnnotatedBoolResult.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"
#include "Usd/pyConversions.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

#define WRAP_CUSTOM template<class Cls> static void _CustomWrapCode(Cls &_class)

// fwd decl.
WRAP_CUSTOM;

static UsdAttribute _CreateTypeAttr(UsdPhysicsDriveAPI &self,
                                    object defaultVal,
                                    bool writeSparsely)
{
  return self.CreateTypeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                             writeSparsely);
}

static UsdAttribute _CreateMaxForceAttr(UsdPhysicsDriveAPI &self,
                                        object defaultVal,
                                        bool writeSparsely)
{
  return self.CreateMaxForceAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                 writeSparsely);
}

static UsdAttribute _CreateTargetPositionAttr(UsdPhysicsDriveAPI &self,
                                              object defaultVal,
                                              bool writeSparsely)
{
  return self.CreateTargetPositionAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                       writeSparsely);
}

static UsdAttribute _CreateTargetVelocityAttr(UsdPhysicsDriveAPI &self,
                                              object defaultVal,
                                              bool writeSparsely)
{
  return self.CreateTargetVelocityAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                       writeSparsely);
}

static UsdAttribute _CreateDampingAttr(UsdPhysicsDriveAPI &self,
                                       object defaultVal,
                                       bool writeSparsely)
{
  return self.CreateDampingAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                writeSparsely);
}

static UsdAttribute _CreateStiffnessAttr(UsdPhysicsDriveAPI &self,
                                         object defaultVal,
                                         bool writeSparsely)
{
  return self.CreateStiffnessAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                  writeSparsely);
}

static bool _WrapIsPhysicsDriveAPIPath(const SdfPath &path)
{
  TfToken collectionName;
  return UsdPhysicsDriveAPI::IsPhysicsDriveAPIPath(path, &collectionName);
}

static std::string _Repr(const UsdPhysicsDriveAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  std::string instanceName = TfPyRepr(self.GetName());
  return TfStringPrintf("UsdPhysics.DriveAPI(%s, '%s')", primRepr.c_str(), instanceName.c_str());
}

struct UsdPhysicsDriveAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdPhysicsDriveAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdPhysicsDriveAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim, const TfToken &name)
{
  std::string whyNot;
  bool result = UsdPhysicsDriveAPI::CanApply(prim, name, &whyNot);
  return UsdPhysicsDriveAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdPhysicsDriveAPI()
{
  typedef UsdPhysicsDriveAPI This;

  UsdPhysicsDriveAPI_CanApplyResult::Wrap<UsdPhysicsDriveAPI_CanApplyResult>("_CanApplyResult",
                                                                             "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("DriveAPI");

  cls.def(init<UsdPrim, TfToken>((arg("prim"), arg("name"))))
      .def(init<UsdSchemaBase const &, TfToken>((arg("schemaObj"), arg("name"))))
      .def(TfTypePythonClass())

      .def("Get",
           (UsdPhysicsDriveAPI(*)(const UsdStagePtr &stage, const SdfPath &path)) & This::Get,
           (arg("stage"), arg("path")))
      .def("Get",
           (UsdPhysicsDriveAPI(*)(const UsdPrim &prim, const TfToken &name)) & This::Get,
           (arg("prim"), arg("name")))
      .staticmethod("Get")

      .def("GetAll",
           (std::vector<UsdPhysicsDriveAPI>(*)(const UsdPrim &prim)) & This::GetAll,
           arg("prim"),
           return_value_policy<TfPySequenceToList>())
      .staticmethod("GetAll")

      .def("CanApply", &_WrapCanApply, (arg("prim"), arg("name")))
      .staticmethod("CanApply")

      .def("Apply", &This::Apply, (arg("prim"), arg("name")))
      .staticmethod("Apply")

      .def("GetSchemaAttributeNames",
           (const TfTokenVector &(*)(bool)) & This::GetSchemaAttributeNames,
           arg("includeInherited") = true,
           return_value_policy<TfPySequenceToList>())
      .def("GetSchemaAttributeNames",
           (TfTokenVector(*)(bool, const TfToken &)) & This::GetSchemaAttributeNames,
           arg("includeInherited"),
           arg("instanceName"),
           return_value_policy<TfPySequenceToList>())
      .staticmethod("GetSchemaAttributeNames")

      .def("_GetStaticTfType",
           (TfType const &(*)())TfType::Find<This>,
           return_value_policy<return_by_value>())
      .staticmethod("_GetStaticTfType")

      .def(!self)

      .def("GetTypeAttr", &This::GetTypeAttr)
      .def("CreateTypeAttr",
           &_CreateTypeAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetMaxForceAttr", &This::GetMaxForceAttr)
      .def("CreateMaxForceAttr",
           &_CreateMaxForceAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTargetPositionAttr", &This::GetTargetPositionAttr)
      .def("CreateTargetPositionAttr",
           &_CreateTargetPositionAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTargetVelocityAttr", &This::GetTargetVelocityAttr)
      .def("CreateTargetVelocityAttr",
           &_CreateTargetVelocityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetDampingAttr", &This::GetDampingAttr)
      .def("CreateDampingAttr",
           &_CreateDampingAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetStiffnessAttr", &This::GetStiffnessAttr)
      .def("CreateStiffnessAttr",
           &_CreateStiffnessAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("IsPhysicsDriveAPIPath", _WrapIsPhysicsDriveAPIPath)
      .staticmethod("IsPhysicsDriveAPIPath")
      .def("__repr__", ::_Repr);

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

WRAP_CUSTOM {}

}  // namespace
