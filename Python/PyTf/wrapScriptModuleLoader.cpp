//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/scriptModuleLoader.h"
#include "Tf/weakPtr.h"

#include "Tf/pyResultConversions.h"
#include "Tf/pySingleton.h"

#include <boost/python/class.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapScriptModuleLoader()
{
  typedef TfScriptModuleLoader This;
  class_<This, TfWeakPtr<This>, boost::noncopyable>("ScriptModuleLoader", no_init)
      .def(TfPySingleton())
      .def("GetModuleNames", &This::GetModuleNames, return_value_policy<TfPySequenceToList>())
      .def("GetModulesDict", &This::GetModulesDict)
      .def("WriteDotFile", &This::WriteDotFile)

      // For testing purposes only.
      .def("_RegisterLibrary", &This::RegisterLibrary)
      .def("_LoadModulesForLibrary", &This::LoadModulesForLibrary);
}
