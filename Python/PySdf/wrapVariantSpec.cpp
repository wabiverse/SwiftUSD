//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file wrapVariantSpec.cpp

#include "pxr/pxrns.h"
#include "Sdf/variantSpec.h"
#include "Sdf/primSpec.h"
#include "Sdf/pySpec.h"
#include "Sdf/variantSetSpec.h"
#include "Sdf/pyChildrenProxy.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

typedef SdfPyChildrenProxy<SdfVariantSetView> VariantSetProxy;

static
VariantSetProxy
_WrapGetVariantSetsProxy(const SdfVariantSpec& owner)
{
    return VariantSetProxy(owner.GetVariantSets());
}

} // anonymous namespace 

void wrapVariantSpec()
{
    def("CreateVariantInLayer", SdfCreateVariantInLayer);

    typedef SdfVariantSpec This;

    class_<This, SdfHandle<This>, bases<SdfSpec>, noncopyable>
        ("VariantSpec", no_init)
        .def(SdfPySpec())
        .def(SdfMakePySpecConstructor(&This::New))

        .add_property("primSpec", &This::GetPrimSpec,
            "The root prim of this variant.")
        .add_property("owner", &This::GetOwner,
            "The variant set that this variant belongs to.")
        .add_property("name",
            make_function(&This::GetName,
                          return_value_policy<return_by_value>()),
            "The variant's name.")
        .add_property("variantSets",
            &_WrapGetVariantSetsProxy)
        .def("GetVariantNames", &This::GetVariantNames)
        ;
}
