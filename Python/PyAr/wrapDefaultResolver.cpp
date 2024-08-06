//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include <boost/python/class.hpp>

#include "Ar/defaultResolver.h"
#include "pxr/pxrns.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapDefaultResolver()
{
  using This = ArDefaultResolver;

  class_<This, bases<ArResolver>, boost::noncopyable>("DefaultResolver", no_init)

      .def("SetDefaultSearchPath", &This::SetDefaultSearchPath, args("searchPath"))
      .staticmethod("SetDefaultSearchPath");
}
