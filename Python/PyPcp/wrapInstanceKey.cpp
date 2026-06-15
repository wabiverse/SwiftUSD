//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Pcp/instanceKey.h"
#include "Pcp/primIndex.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
 
PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static size_t
__hash__(const PcpInstanceKey& key)
{
    return TfHash{}(key);
}

} // anonymous namespace 

void
wrapInstanceKey()
{
    class_<PcpInstanceKey>("InstanceKey")
        .def(init<const PcpPrimIndex&>(args("primIndex")))

        .def(self == self)
        .def(self != self)

        .def("__str__", &PcpInstanceKey::GetString)
        .def("__hash__", __hash__)
        ;
}
