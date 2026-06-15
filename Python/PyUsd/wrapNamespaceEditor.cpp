//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/namespaceEditor.h"
#include "Usd/prim.h"
#include "Usd/property.h"

#include "Tf/pyResultConversions.h"
#include "Tf/pyContainerConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/enum.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static
UsdNamespaceEditor::CanApplyResult
_CanApplyEdits(const UsdNamespaceEditor &editor)
{
    return editor.CanApplyEdits();
}
static
std::string 
_FormatWhyNot(const UsdNamespaceEditor::CanApplyResult &result) {
    return TfStringJoin(result.errors, "; ");
}

void wrapUsdNamespaceEditor()
{
    using This = UsdNamespaceEditor;

    scope s = class_<This>("NamespaceEditor", no_init)
        .def(init<const UsdStagePtr &>())
        .def(init<const UsdStagePtr &, const This::EditOptions &>())

        .def("AddDependentStage", &This::AddDependentStage)
        .def("RemoveDependentStage", &This::RemoveDependentStage)
        .def("SetDependentStages", &This::SetDependentStages)

        .def("DeletePrimAtPath", &This::DeletePrimAtPath)
        .def("MovePrimAtPath", &This::MovePrimAtPath)

        .def("DeletePrim", &This::DeletePrim)
        .def("RenamePrim", &This::RenamePrim)
        .def("ReparentPrim", 
            (bool (This::*) (const UsdPrim &, const UsdPrim &))
               &This::ReparentPrim)
        .def("ReparentPrim", 
            (bool (This::*) (const UsdPrim &, const UsdPrim &, 
                const TfToken &)) &This::ReparentPrim)

        .def("DeletePropertyAtPath", &This::DeletePropertyAtPath)
        .def("MovePropertyAtPath", &This::MovePropertyAtPath)

        .def("DeleteProperty", &This::DeleteProperty)
        .def("RenameProperty", &This::RenameProperty)
        .def("ReparentProperty", 
            (bool (This::*) (const UsdProperty &, const UsdPrim &))
               &This::ReparentProperty)
        .def("ReparentProperty", 
            (bool (This::*) (const UsdProperty &, const UsdPrim &, 
                const TfToken &)) &This::ReparentProperty)

        .def("ApplyEdits", &This::ApplyEdits)
        .def("CanApplyEdits", &_CanApplyEdits)
        .def("GetLayersToEdit", &This::GetLayersToEdit,
            return_value_policy<TfPySequenceToList>())
    ;

    class_<This::EditOptions>("EditOptions")
        .def(init<>())
        .add_property("allowRelocatesAuthoring", 
            &This::EditOptions::allowRelocatesAuthoring, 
            &This::EditOptions::allowRelocatesAuthoring)
    ;

    class_<This::CanApplyResult>("CanApplyResult")
        .def(init<>())
        .def("__bool__", &This::CanApplyResult::operator bool)
        .add_property("whyNot", &_FormatWhyNot)
        .add_property("errors", make_getter(&This::CanApplyResult::errors, 
            return_value_policy<TfPySequenceToList>()))
        .add_property("warnings", make_getter(&This::CanApplyResult::warnings, 
            return_value_policy<TfPySequenceToList>()))
    ;
}
