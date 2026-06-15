//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Sdf/changeBlock.h"
#include "Sdf/changeManager.h"
#include "Tf/diagnostic.h"
#include "Tf/pyUtils.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <memory>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

class Sdf_PythonChangeBlock {
public:
    explicit Sdf_PythonChangeBlock(bool enabled) : _enabled(enabled) {}
    
    void Open() {
        if (!_enabled || !TF_VERIFY(!_block)) {
            return;
        }
        _block.reset(new SdfChangeBlock);
    }

    void Close(object, object, object)
    {
        if (!_enabled || !TF_VERIFY(_block)) {
            return;
        }
        _block.reset();
    }

private:
    std::unique_ptr<SdfChangeBlock> _block;
    const bool _enabled;
};

} // anonymous namespace 

void
wrapChangeBlock()
{
    // This allows SdfChangeBlocks to be used in an RAII fashion in Python 
    // with the 'with' statement.
    typedef Sdf_PythonChangeBlock This;
    class_<This, noncopyable>("ChangeBlock",
                                     init<bool>(arg("enabled")=true))
        .def("__enter__", &This::Open)
        .def("__exit__", &This::Close)
        ;
}
