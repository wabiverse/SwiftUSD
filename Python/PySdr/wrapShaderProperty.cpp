//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdr/shaderProperty.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyStaticTokens.h"
#include "Tf/weakPtr.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

// Boost treats a const ptr differently than a non-const ptr, so a custom
// converter is needed to deal with the const-ness
struct SdrShaderPropertyConstPtrToPythonConverter {
  static PyObject *convert(SdrShaderPropertyConstPtr shaderProperty)
  {
    object shaderPropertyObject(ptr(shaderProperty));

    return incref(shaderPropertyObject.ptr());
  }
};

}  // anonymous namespace

void wrapShaderProperty()
{
  typedef SdrShaderProperty This;
  typedef SdrShaderPropertyPtr ThisPtr;

  TF_PY_WRAP_PUBLIC_TOKENS("PropertyTypes", SdrPropertyTypes, SDR_PROPERTY_TYPE_TOKENS);

  TF_PY_WRAP_PUBLIC_TOKENS("PropertyMetadata", SdrPropertyMetadata, SDR_PROPERTY_METADATA_TOKENS);

  TF_PY_WRAP_PUBLIC_TOKENS("PropertyRole", SdrPropertyRole, SDR_PROPERTY_ROLE_TOKENS);

  return_value_policy<copy_const_reference> copyRefPolicy;

  to_python_converter<SdrShaderPropertyConstPtr, SdrShaderPropertyConstPtrToPythonConverter>();

  class_<This, ThisPtr, bases<NdrProperty>, boost::noncopyable>("ShaderProperty", no_init)
      .def("GetDefaultValueAsSdfType", &This::GetDefaultValueAsSdfType, copyRefPolicy)
      .def("GetLabel", &This::GetLabel, copyRefPolicy)
      .def("GetHelp", &This::GetHelp)
      .def("GetPage", &This::GetPage, copyRefPolicy)
      .def("GetWidget", &This::GetWidget, copyRefPolicy)
      .def("GetHints", &This::GetHints, return_value_policy<TfPyMapToDictionary>())
      .def("GetOptions", &This::GetOptions, return_value_policy<TfPySequenceToList>())
      .def("GetImplementationName", &This::GetImplementationName)
      .def("GetVStructMemberOf", &This::GetVStructMemberOf, copyRefPolicy)
      .def("GetVStructMemberName", &This::GetVStructMemberName, copyRefPolicy)
      .def("GetVStructConditionalExpr", &This::GetVStructConditionalExpr, copyRefPolicy)
      .def("IsVStructMember", &This::IsVStructMember)
      .def("IsVStruct", &This::IsVStruct)
      .def("GetValidConnectionTypes", &This::GetValidConnectionTypes, copyRefPolicy)
      .def("IsAssetIdentifier", &This::IsAssetIdentifier)
      .def("IsDefaultInput", &This::IsDefaultInput);
}
