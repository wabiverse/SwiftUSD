//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdPhysics/rigidBodyAPI.h"

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

static UsdAttribute _CreateRigidBodyEnabledAttr(UsdPhysicsRigidBodyAPI &self,
                                                object defaultVal,
                                                bool writeSparsely)
{
  return self.CreateRigidBodyEnabledAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool),
                                         writeSparsely);
}

static UsdAttribute _CreateKinematicEnabledAttr(UsdPhysicsRigidBodyAPI &self,
                                                object defaultVal,
                                                bool writeSparsely)
{
  return self.CreateKinematicEnabledAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool),
                                         writeSparsely);
}

static UsdAttribute _CreateStartsAsleepAttr(UsdPhysicsRigidBodyAPI &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateStartsAsleepAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool),
                                     writeSparsely);
}

static UsdAttribute _CreateVelocityAttr(UsdPhysicsRigidBodyAPI &self,
                                        object defaultVal,
                                        bool writeSparsely)
{
  return self.CreateVelocityAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Vector3f),
                                 writeSparsely);
}

static UsdAttribute _CreateAngularVelocityAttr(UsdPhysicsRigidBodyAPI &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateAngularVelocityAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Vector3f), writeSparsely);
}

static std::string _Repr(const UsdPhysicsRigidBodyAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdPhysics.RigidBodyAPI(%s)", primRepr.c_str());
}

struct UsdPhysicsRigidBodyAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdPhysicsRigidBodyAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdPhysicsRigidBodyAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim)
{
  std::string whyNot;
  bool result = UsdPhysicsRigidBodyAPI::CanApply(prim, &whyNot);
  return UsdPhysicsRigidBodyAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdPhysicsRigidBodyAPI()
{
  typedef UsdPhysicsRigidBodyAPI This;

  UsdPhysicsRigidBodyAPI_CanApplyResult::Wrap<UsdPhysicsRigidBodyAPI_CanApplyResult>(
      "_CanApplyResult", "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("RigidBodyAPI");

  cls.def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

      .def("CanApply", &_WrapCanApply, (arg("prim")))
      .staticmethod("CanApply")

      .def("Apply", &This::Apply, (arg("prim")))
      .staticmethod("Apply")

      .def("GetSchemaAttributeNames",
           &This::GetSchemaAttributeNames,
           arg("includeInherited") = true,
           return_value_policy<TfPySequenceToList>())
      .staticmethod("GetSchemaAttributeNames")

      .def("_GetStaticTfType",
           (TfType const &(*)())TfType::Find<This>,
           return_value_policy<return_by_value>())
      .staticmethod("_GetStaticTfType")

      .def(!self)

      .def("GetRigidBodyEnabledAttr", &This::GetRigidBodyEnabledAttr)
      .def("CreateRigidBodyEnabledAttr",
           &_CreateRigidBodyEnabledAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetKinematicEnabledAttr", &This::GetKinematicEnabledAttr)
      .def("CreateKinematicEnabledAttr",
           &_CreateKinematicEnabledAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetStartsAsleepAttr", &This::GetStartsAsleepAttr)
      .def("CreateStartsAsleepAttr",
           &_CreateStartsAsleepAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVelocityAttr", &This::GetVelocityAttr)
      .def("CreateVelocityAttr",
           &_CreateVelocityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetAngularVelocityAttr", &This::GetAngularVelocityAttr)
      .def("CreateAngularVelocityAttr",
           &_CreateAngularVelocityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetSimulationOwnerRel", &This::GetSimulationOwnerRel)
      .def("CreateSimulationOwnerRel", &This::CreateSimulationOwnerRel)
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

#include "Tf/pyFunction.h"

namespace {

static tuple ComputeMassPropertiesHelper(
    const UsdPhysicsRigidBodyAPI &self,
    const UsdPhysicsRigidBodyAPI::MassInformationFn &massInfoFn)
{
  GfVec3f diagonalInertia;
  GfVec3f com;
  GfQuatf principalAxes;
  float mass = self.ComputeMassProperties(&diagonalInertia, &com, &principalAxes, massInfoFn);
  return boost::python::make_tuple(mass, diagonalInertia, com, principalAxes);
}

WRAP_CUSTOM
{

  typedef UsdPhysicsRigidBodyAPI This;

  TfPyFunctionFromPython<UsdPhysicsRigidBodyAPI::MassInformationFnSig>();

  scope s = _class.def("ComputeMassProperties", ComputeMassPropertiesHelper)

      ;

  class_<UsdPhysicsRigidBodyAPI::MassInformation>("MassInformation")
      .def_readwrite("volume", &UsdPhysicsRigidBodyAPI::MassInformation::volume)
      .def_readwrite("inertia", &UsdPhysicsRigidBodyAPI::MassInformation::inertia)
      .def_readwrite("centerOfMass", &UsdPhysicsRigidBodyAPI::MassInformation::centerOfMass)
      .def_readwrite("localPos", &UsdPhysicsRigidBodyAPI::MassInformation::localPos)
      .def_readwrite("localRot", &UsdPhysicsRigidBodyAPI::MassInformation::localRot);
}

}  // anonymous namespace
