//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/namespaceEditor.h"
#include "Usd/prim.h"
#include "Usd/property.h"
#include "pxr/pxrns.h"

#include "Tf/pyAnnotatedBoolResult.h"
#include "Tf/pyResultConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/scope.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

struct Usd_UsdNamespaceEditorCanEditResult : public TfPyAnnotatedBoolResult<std::string> {
  Usd_UsdNamespaceEditorCanEditResult(bool val, const std::string &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, std::move(msg))
  {
  }
};

template<typename Fn> Usd_UsdNamespaceEditorCanEditResult _CallWithAnnotatedResult(const Fn &func)
{
  std::string whyNot;
  bool result = func(&whyNot);
  return Usd_UsdNamespaceEditorCanEditResult(result, whyNot);
}

static Usd_UsdNamespaceEditorCanEditResult _CanApplyEdits(const UsdNamespaceEditor &editor)
{
  return _CallWithAnnotatedResult(
      [&](std::string *whyNot) { return editor.CanApplyEdits(whyNot); });
}

void wrapUsdNamespaceEditor()
{
  using This = UsdNamespaceEditor;

  Usd_UsdNamespaceEditorCanEditResult::Wrap<Usd_UsdNamespaceEditorCanEditResult>(
      "_UsdNamespaceEditorCanEditResult", "whyNot");

  scope s = class_<This>("NamespaceEditor", no_init)
                .def(init<const UsdStagePtr &>())
                .def(init<const UsdStagePtr &, const This::EditOptions &>())

                .def("DeletePrimAtPath", &This::DeletePrimAtPath)
                .def("MovePrimAtPath", &This::MovePrimAtPath)

                .def("DeletePrim", &This::DeletePrim)
                .def("RenamePrim", &This::RenamePrim)
                .def("ReparentPrim",
                     (bool(This::*)(const UsdPrim &, const UsdPrim &)) & This::ReparentPrim)
                .def("ReparentPrim",
                     (bool(This::*)(const UsdPrim &, const UsdPrim &, const TfToken &)) &
                         This::ReparentPrim)

                .def("DeletePropertyAtPath", &This::DeletePropertyAtPath)
                .def("MovePropertyAtPath", &This::MovePropertyAtPath)

                .def("DeleteProperty", &This::DeleteProperty)
                .def("RenameProperty", &This::RenameProperty)
                .def("ReparentProperty",
                     (bool(This::*)(const UsdProperty &, const UsdPrim &)) &
                         This::ReparentProperty)
                .def("ReparentProperty",
                     (bool(This::*)(const UsdProperty &, const UsdPrim &, const TfToken &)) &
                         This::ReparentProperty)

                .def("ApplyEdits", &This::ApplyEdits)
                .def("CanApplyEdits", &_CanApplyEdits);

  class_<This::EditOptions>("EditOptions")
      .def(init<>())
      .add_property("allowRelocatesAuthoring",
                    &This::EditOptions::allowRelocatesAuthoring,
                    &This::EditOptions::allowRelocatesAuthoring);
}
