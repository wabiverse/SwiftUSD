//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file wrapPseudoRootSpec.cpp

#include "pxr/pxrns.h"
#include "Sdf/pseudoRootSpec.h"
#include "Sdf/pySpec.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void
wrapPseudoRootSpec()
{
    typedef SdfPseudoRootSpec This;

    class_<This, SdfHandle<This>, 
           bases<SdfPrimSpec>, noncopyable>
        ("PseudoRootSpec", no_init)
        .def(SdfPySpec())
        ;
}
