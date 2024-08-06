//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_PLUG_TEST_PLUG_BASE_H
#define PXR_BASE_PLUG_TEST_PLUG_BASE_H

#include "Plug/api.h"
#include "Tf/refBase.h"
#include "Tf/stringUtils.h"
#include "Tf/type.h"
#include "Tf/weakBase.h"
#include "pxr/pxrns.h"

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

template<int M> class _TestPlugBase : public TfRefBase, public TfWeakBase {
 public:
  typedef _TestPlugBase This;
  typedef TfRefPtr<This> RefPtr;
  typedef TfWeakPtr<This> Ptr;
  constexpr static int N = M;

  virtual ~_TestPlugBase() {}

  virtual std::string GetTypeName()
  {
    return TfType::Find(this).GetTypeName();
  }

  static RefPtr New()
  {
    return TfCreateRefPtr(new This());
  }

  PLUG_API
  static RefPtr Manufacture(const std::string &subclass);

 protected:
  _TestPlugBase() {}
};

template<int N> class _TestPlugFactoryBase : public TfType::FactoryBase {
 public:
  virtual TfRefPtr<_TestPlugBase<N>> New() const = 0;
};

template<typename T> class _TestPlugFactory : public _TestPlugFactoryBase<T::N> {
 public:
  virtual TfRefPtr<_TestPlugBase<T::N>> New() const
  {
    return T::New();
  }
};

typedef _TestPlugBase<1> _TestPlugBase1;
typedef _TestPlugBase<2> _TestPlugBase2;
typedef _TestPlugBase<3> _TestPlugBase3;
typedef _TestPlugBase<4> _TestPlugBase4;

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_PLUG_TEST_PLUG_BASE_H
