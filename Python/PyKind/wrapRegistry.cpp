//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Kind/registry.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pySingleton.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapRegistry()
{
  typedef KindRegistry This;
  typedef TfWeakPtr<KindRegistry> ThisPtr;

  class_<This, ThisPtr, boost::noncopyable>("Registry", no_init)
      .def(TfPySingleton())
      .def("HasKind", &This::HasKind)
      .staticmethod("HasKind")
      .def("GetAllKinds", &This::GetAllKinds, return_value_policy<TfPySequenceToList>())
      .staticmethod("GetAllKinds")
      .def("GetBaseKind", &This::GetBaseKind)
      .staticmethod("GetBaseKind")
      .def("IsA", &This::IsA)
      .def("IsModel", &This::IsModel)
      .def("IsGroup", &This::IsGroup)
      .def("IsAssembly", &This::IsAssembly)
      .def("IsComponent", &This::IsComponent)
      .def("IsSubComponent", &This::IsSubComponent)
      .staticmethod("IsA");
}
