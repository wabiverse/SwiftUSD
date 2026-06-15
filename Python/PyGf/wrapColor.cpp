///
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Gf/color.h"
#include "Gf/vec3f.h"
#include "Gf/colorSpace.h"
#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include <string>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

std::string __repr__(GfColor const &self)
{
    return TF_PY_REPR_PREFIX + 
        TfStringPrintf("Color(%s, %s)", 
                             TfPyRepr(self.GetRGB()).c_str(),
			     TfPyRepr(self.GetColorSpace()).c_str());
}

}

void wrapColor()
{
    class_<GfColor>("Color", 
                    "A class representing a color, supporting different "
                    "color spaces.")
        .def(init<>()) 
        .def(init<const GfColor&>()) 
        .def(init<const GfColorSpace&>()) 
        .def(init<const GfVec3f&, const GfColorSpace&>()) 
        .def(init<const GfColor&, const GfColorSpace&>()) 
        .def("__repr__", &__repr__) 
        .def("SetFromPlanckianLocus", &GfColor::SetFromPlanckianLocus, 
             (arg("kelvin"), arg("luminance")))
        .def("GetRGB", &GfColor::GetRGB) 
        .def("GetColorSpace", &GfColor::GetColorSpace) 
        .def(self == self) 
        .def(self != self) 
        ;

    def("IsClose", 
        (bool (*)(const GfColor &v1, const GfColor &v2, double)) GfIsClose,
        (arg("v1"), arg("v2"), arg("tolerance")));
}

