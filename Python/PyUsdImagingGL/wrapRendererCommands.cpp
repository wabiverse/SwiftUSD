//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include <boost/python/class.hpp>
#include <boost/python/converter/from_python.hpp>
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>

#include "UsdImagingGL/engine.h"

#include "Hd/command.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

using UsdImagingGLRendererCommandArgDescriptor = HdCommandArgDescriptor;

using UsdImagingGLRendererCommandDescriptor = HdCommandDescriptor;

void wrapRendererCommands()
{
  // Wrap the UsdImagingGLRendererCommandArgDescriptor struct.
  // Accessible as UsdImagingGL.RendererCommandArgDescriptor
  class_<UsdImagingGLRendererCommandArgDescriptor>(
      "RendererCommandArgDescriptor", "Renderer Command Argument Metadata", no_init)
      .add_property("argName",
                    make_getter(&UsdImagingGLRendererCommandArgDescriptor::argName,
                                return_value_policy<return_by_value>()))

      .def_readonly("defaultValue", &UsdImagingGLRendererCommandArgDescriptor::defaultValue);

  // Wrap the UsdImagingGLRendererCommandDescriptor struct.
  // Accessible as UsdImagingGL.RendererCommandDescriptor
  class_<UsdImagingGLRendererCommandDescriptor>(
      "RendererCommandDescriptor", "Renderer Command Metadata", no_init)
      .add_property("commandName",
                    make_getter(&UsdImagingGLRendererCommandDescriptor::commandName,
                                return_value_policy<return_by_value>()))

      .def_readonly("commandDescription",
                    &UsdImagingGLRendererCommandDescriptor::commandDescription)

      .def_readonly("commandArgs", &UsdImagingGLRendererCommandDescriptor::commandArgs);
}
