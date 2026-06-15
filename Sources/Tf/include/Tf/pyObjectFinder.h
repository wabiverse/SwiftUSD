//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PY_OBJECT_FINDER_H
#define PXR_BASE_TF_PY_OBJECT_FINDER_H

#include "pxr/pxrns.h"

#include "Tf/api.h"
#include "Tf/pyIdentity.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/handle.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <typeinfo>

#if PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_OPEN_SCOPE

struct Tf_PyObjectFinderBase {
    TF_API virtual ~Tf_PyObjectFinderBase();
    virtual pxr_boost::python::object Find(void const *objPtr) const = 0;
};

template <class T, class PtrType>
struct Tf_PyObjectFinder : public Tf_PyObjectFinderBase {
    virtual ~Tf_PyObjectFinder() {}
    virtual pxr_boost::python::object Find(void const *objPtr) const {
        using namespace pxr_boost::python;
        TfPyLock lock;
        void *p = const_cast<void *>(objPtr);
        PyObject *obj = Tf_PyGetPythonIdentity(PtrType(static_cast<T *>(p)));
        return obj ? object(handle<>(obj)) : object();
    }
};

TF_API
void Tf_RegisterPythonObjectFinderInternal(std::type_info const &type,
                                           Tf_PyObjectFinderBase const *finder);

template <class T, class PtrType>
void Tf_RegisterPythonObjectFinder() {
    Tf_RegisterPythonObjectFinderInternal(typeid(T),
                                          new Tf_PyObjectFinder<T, PtrType>());
}

TF_API pxr_boost::python::object
Tf_FindPythonObject(void const *objPtr, std::type_info const &type);

PXR_NAMESPACE_CLOSE_SCOPE
#endif // PXR_PYTHON_SUPPORT_ENABLED

#endif // PXR_BASE_TF_PY_OBJECT_FINDER_H