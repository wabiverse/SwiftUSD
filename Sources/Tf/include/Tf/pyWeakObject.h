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

#if __has_include(<boost/python/handle.hpp>)
#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>
#endif // __has_include(<boost/python/handle.hpp>)

#include "Tf/hashmap.h"

PXR_NAMESPACE_OPEN_SCOPE

typedef TfWeakPtr<struct Tf_PyWeakObject> Tf_PyWeakObjectPtr;

// A weak pointable weak reference to a python object.
struct Tf_PyWeakObject : public TfWeakBase {
 public:
  typedef Tf_PyWeakObject This;

  static Tf_PyWeakObjectPtr GetOrCreate(boost::python::object const &obj);
  boost::python::object GetObject() const;
  void Delete();

 private:
  explicit Tf_PyWeakObject(boost::python::object const &obj);

  boost::python::handle<> _weakRef;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TF_PY_WEAK_OBJECT_H
