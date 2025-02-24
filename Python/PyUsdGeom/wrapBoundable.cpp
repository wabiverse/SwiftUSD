//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/boundable.h"

#include "Sdf/primSpec.h"

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

static UsdAttribute _CreateExtentAttr(UsdGeomBoundable &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateExtentAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float3Array),
                               writeSparsely);
}

static std::string _Repr(const UsdGeomBoundable &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.Boundable(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomBoundable()
{
  typedef UsdGeomBoundable This;

  class_<This, bases<UsdGeomXformable>> cls("Boundable");

  cls.def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

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

      .def("GetExtentAttr", &This::GetExtentAttr)
      .def("CreateExtentAttr",
           &_CreateExtentAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

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

static object _ComputeExtent(UsdGeomBoundable &boundable, const UsdTimeCode &time)
{
  VtVec3fArray extent;
  if (!boundable.ComputeExtent(time, &extent)) {
    return object();
  }
  return object(extent);
}

static object _ComputeExtentFromPlugins(const UsdGeomBoundable &boundable, const UsdTimeCode &time)
{
  VtVec3fArray extent;
  if (!UsdGeomBoundable::ComputeExtentFromPlugins(boundable, time, &extent)) {
    return object();
  }
  return object(extent);
}

static object _ComputeExtentFromPluginsWithTransform(const UsdGeomBoundable &boundable,
                                                     const UsdTimeCode &time,
                                                     const GfMatrix4d &transform)
{
  VtVec3fArray extent;
  if (!UsdGeomBoundable::ComputeExtentFromPlugins(boundable, time, transform, &extent)) {
    return object();
  }
  return object(extent);
}

WRAP_CUSTOM
{
  _class.def("ComputeExtent", &_ComputeExtent, (arg("time")))
      .def("ComputeExtentFromPlugins", &_ComputeExtentFromPlugins, (arg("boundable"), arg("time")))
      .def("ComputeExtentFromPlugins",
           &_ComputeExtentFromPluginsWithTransform,
           (arg("boundable"), arg("time"), arg("transform")))
      .staticmethod("ComputeExtentFromPlugins");
}

}  // anonymous namespace
