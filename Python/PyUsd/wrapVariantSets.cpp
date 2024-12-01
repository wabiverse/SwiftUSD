//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/editContext.h"
#include "Usd/pyEditContext.h"
#include "Usd/variantSets.h"
#include "pxr/pxrns.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/object.hpp>
#include <boost/python/operators.hpp>

#include <string>
#include <vector>

using std::string;
using std::vector;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static object _HasAuthoredVariantSelection(const UsdVariantSet &self)
{
  string value;
  if (self.HasAuthoredVariantSelection(&value))
    return object(value);
  return object();
}

static vector<string> _GetNames(const UsdVariantSets &self)
{
  vector<string> result;
  self.GetNames(&result);
  return result;
}

static UsdPyEditContext _GetVariantEditContext(const UsdVariantSet &self,
                                               const SdfLayerHandle &layer)
{
  return UsdPyEditContext(self.GetVariantEditContext(layer));
}

}  // anonymous namespace

void wrapUsdVariantSets()
{
  class_<UsdVariantSet>("VariantSet", no_init)
      .def("AddVariant",
           &UsdVariantSet::AddVariant,
           (arg("variantName"), arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("GetVariantNames",
           &UsdVariantSet::GetVariantNames,
           return_value_policy<TfPySequenceToList>())
      .def("HasAuthoredVariant", &UsdVariantSet::HasAuthoredVariant)
      .def("GetVariantSelection", &UsdVariantSet::GetVariantSelection)
      .def("HasAuthoredVariantSelection", _HasAuthoredVariantSelection)
      .def("SetVariantSelection", &UsdVariantSet::SetVariantSelection, arg("variantName"))
      .def("ClearVariantSelection", &UsdVariantSet::ClearVariantSelection)
      .def("BlockVariantSelection", &UsdVariantSet::BlockVariantSelection)
      .def("GetVariantEditTarget",
           &UsdVariantSet::GetVariantEditTarget,
           arg("layer") = SdfLayerHandle())
      .def("GetVariantEditContext", _GetVariantEditContext, arg("layer") = SdfLayerHandle())
      .def("GetPrim", &UsdVariantSet::GetPrim, return_value_policy<return_by_value>())
      .def("GetName", &UsdVariantSet::GetName, return_value_policy<return_by_value>())
      .def("IsValid", &UsdVariantSet::IsValid)
      .def(!self);

  class_<UsdVariantSets>("VariantSets", no_init)
      .def("AddVariantSet",
           &UsdVariantSets::AddVariantSet,
           (arg("variantSetName"), arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("GetNames", _GetNames, return_value_policy<TfPySequenceToList>())
      .def("GetVariantSet", &UsdVariantSets::GetVariantSet, arg("variantSetName"))
      .def("HasVariantSet", &UsdVariantSets::HasVariantSet, arg("variantSetName"))
      .def("GetVariantSelection", &UsdVariantSets::GetVariantSelection, arg("variantSetName"))
      .def("SetSelection",
           &UsdVariantSets::SetSelection,
           (arg("variantSetName"), arg("variantName")))
      .def("GetAllVariantSelections",
           &UsdVariantSets::GetAllVariantSelections,
           return_value_policy<TfPyMapToDictionary>());
}
