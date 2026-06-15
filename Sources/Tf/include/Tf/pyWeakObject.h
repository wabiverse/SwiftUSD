//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PY_WEAK_OBJECT_H
#define PXR_BASE_TF_PY_WEAK_OBJECT_H

#include "pxr/pxrns.h"

#include "Tf/api.h"
#include "Tf/pyIdentity.h"

#include "Tf/hash.h"
#include "Tf/singleton.h"
#include "Tf/weakBase.h"
#include "Tf/weakPtr.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/handle.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "Tf/hashmap.h"

#if PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_OPEN_SCOPE

typedef TfWeakPtr<struct Tf_PyWeakObject> Tf_PyWeakObjectPtr;

// A weak pointable weak reference to a python object.
struct Tf_PyWeakObject : public TfWeakBase
{
public:
    typedef Tf_PyWeakObject This;

    static Tf_PyWeakObjectPtr GetOrCreate(pxr_boost::python::object const &obj);
    pxr_boost::python::object GetObject() const;
    void Delete();
    
private:
    explicit Tf_PyWeakObject(pxr_boost::python::object const &obj);
    
    pxr_boost::python::handle<> _weakRef;
};

PXR_NAMESPACE_CLOSE_SCOPE
#endif // PXR_PYTHON_SUPPORT_ENABLED

#endif // PXR_BASE_TF_PY_WEAK_OBJECT_H