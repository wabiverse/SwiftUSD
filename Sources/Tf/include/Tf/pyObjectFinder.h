//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PY_OBJECT_FINDER_H
#define PXR_BASE_TF_PY_OBJECT_FINDER_H

#include "pxr/pxrns.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#include "Tf/api.h"
#include "Tf/pyIdentity.h"

#if __has_include(<boost/python/handle.hpp>)
#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>
#endif // __has_include(<boost/python/handle.hpp>)

#include <typeinfo>

PXR_NAMESPACE_OPEN_SCOPE

struct Tf_PyObjectFinderBase {
  TF_API virtual ~Tf_PyObjectFinderBase();
  virtual boost::python::object Find(void const *objPtr) const = 0;
};

template<class T, class PtrType> struct Tf_PyObjectFinder : public Tf_PyObjectFinderBase {
  virtual ~Tf_PyObjectFinder() {}
  virtual boost::python::object Find(void const *objPtr) const
  {
    using namespace boost::python;
    TfPyLock lock;
    void *p = const_cast<void *>(objPtr);
    PyObject *obj = Tf_PyGetPythonIdentity(PtrType(static_cast<T *>(p)));
    return obj ? object(handle<>(obj)) : object();
  }
};

TF_API
void Tf_RegisterPythonObjectFinderInternal(std::type_info const &type,
                                           Tf_PyObjectFinderBase const *finder);

template<class T, class PtrType> void Tf_RegisterPythonObjectFinder()
{
  Tf_RegisterPythonObjectFinderInternal(typeid(T), new Tf_PyObjectFinder<T, PtrType>());
}

TF_API boost::python::object Tf_FindPythonObject(void const *objPtr, std::type_info const &type);

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#endif  // PXR_BASE_TF_PY_OBJECT_FINDER_H
