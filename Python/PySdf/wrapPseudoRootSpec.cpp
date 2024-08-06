//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file wrapPseudoRootSpec.cpp

#include "Sdf/pseudoRootSpec.h"
#include "Sdf/pySpec.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapPseudoRootSpec()
{
  typedef SdfPseudoRootSpec This;

  class_<This, SdfHandle<This>, bases<SdfPrimSpec>, boost::noncopyable>("PseudoRootSpec", no_init)
      .def(SdfPySpec());
}
