//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include <boost/python/def.hpp>
#include <boost/python/tuple.hpp>

#include "Tf/pyFunction.h"
#include "Tf/pyUtils.h"

#include "Sdf/copyUtils.h"
#include "pxr/pxrns.h"

#include "Sdf/layer.h"
#include "Sdf/path.h"

#include "Vt/value.h"

#include <functional>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

VtValue _GetValueForField(const SdfLayerHandle &layer,
                          const TfToken &field,
                          const boost::python::object &obj)
{
  // Need to disambiguate certain types from Python.
  //
  // XXX: See also wrapSpec.cpp. Perhaps this logic should live in
  // pyUtils.h?
  const VtValue &fallback = layer->GetSchema().GetFallback(field);
  if (fallback.IsHolding<TfTokenVector>()) {
    return VtValue(extract<TfTokenVector>(obj)());
  }

  VtValue v = extract<VtValue>(obj)();
  if (!fallback.IsEmpty()) {
    v.CastToTypeOf(fallback);
  }
  return v;
}

using Py_SdfShouldCopyValueSig = boost::python::object(SdfSpecType,
                                                       const TfToken &,
                                                       const SdfLayerHandle &,
                                                       const SdfPath &,
                                                       bool,
                                                       const SdfLayerHandle &,
                                                       const SdfPath &,
                                                       bool);

using Py_SdfShouldCopyValueFn = std::function<Py_SdfShouldCopyValueSig>;

using Py_SdfShouldCopyChildrenSig = boost::python::object(const TfToken &,
                                                          const SdfLayerHandle &,
                                                          const SdfPath &,
                                                          bool,
                                                          const SdfLayerHandle &,
                                                          const SdfPath &,
                                                          bool);

using Py_SdfShouldCopyChildrenFn = std::function<Py_SdfShouldCopyChildrenSig>;

bool _ShouldCopyValue(const Py_SdfShouldCopyValueFn &pyFunc,
                      SdfSpecType specType,
                      const TfToken &field,
                      const SdfLayerHandle &srcLayer,
                      const SdfPath &srcPath,
                      bool fieldInSrc,
                      const SdfLayerHandle &dstLayer,
                      const SdfPath &dstPath,
                      bool fieldInDst,
                      std::optional<VtValue> *value)
{
  object result = pyFunc(
      specType, field, srcLayer, srcPath, fieldInSrc, dstLayer, dstPath, fieldInDst);

  if (PyBool_Check(result.ptr())) {
    return extract<bool>(result)();
  }

  extract<tuple> getTuple(result);
  if (getTuple.check()) {
    if (PyBool_Check(object(result[0]).ptr())) {
      const bool status = extract<bool>(result[0])();
      *value = _GetValueForField(srcLayer, field, result[1]);
      return status;
    }
  }

  TfPyThrowTypeError("Expected shouldCopyValueFn to return bool or (bool, value)");
  return true;
}

bool _ShouldCopyChildren(const Py_SdfShouldCopyChildrenFn &pyFunc,
                         const TfToken &field,
                         const SdfLayerHandle &srcLayer,
                         const SdfPath &srcPath,
                         bool fieldInSrc,
                         const SdfLayerHandle &dstLayer,
                         const SdfPath &dstPath,
                         bool fieldInDst,
                         std::optional<VtValue> *srcChildren,
                         std::optional<VtValue> *dstChildren)
{
  object result = pyFunc(field, srcLayer, srcPath, fieldInSrc, dstLayer, dstPath, fieldInDst);

  if (PyBool_Check(result.ptr())) {
    return extract<bool>(result)();
  }

  extract<tuple> getTuple(result);
  if (getTuple.check()) {
    if (PyBool_Check(object(result[0]).ptr())) {
      const bool status = extract<bool>(result[0])();
      *srcChildren = _GetValueForField(srcLayer, field, result[1]);
      *dstChildren = _GetValueForField(srcLayer, field, result[2]);
      return status;
    }
  }

  TfPyThrowTypeError("Expected shouldCopyChildrenFn to return bool or (bool, value, value)");
  return true;
}

bool Py_SdfCopySpec(const SdfLayerHandle &srcLayer,
                    const SdfPath &srcPath,
                    const SdfLayerHandle &dstLayer,
                    const SdfPath &dstPath,
                    const Py_SdfShouldCopyValueFn &shouldCopyValueFn,
                    const Py_SdfShouldCopyChildrenFn &shouldCopyChildrenFn)
{
  namespace ph = std::placeholders;

  return SdfCopySpec(srcLayer,
                     srcPath,
                     dstLayer,
                     dstPath,
                     /* shouldCopyValueFn = */
                     std::bind(_ShouldCopyValue,
                               std::cref(shouldCopyValueFn),
                               ph::_1,
                               ph::_2,
                               ph::_3,
                               ph::_4,
                               ph::_5,
                               ph::_6,
                               ph::_7,
                               ph::_8,
                               ph::_9),
                     /* shouldCopyChildrenFn = */
                     std::bind(_ShouldCopyChildren,
                               std::cref(shouldCopyChildrenFn),
                               ph::_1,
                               ph::_2,
                               ph::_3,
                               ph::_4,
                               ph::_5,
                               ph::_6,
                               ph::_7,
                               ph::_8,
                               ph::_9));
}

}  // namespace

void wrapCopyUtils()
{
  def("CopySpec",
      (bool (*)(
          const SdfLayerHandle &, const SdfPath &, const SdfLayerHandle &, const SdfPath &)) &
          SdfCopySpec,
      (arg("srcLayer"), arg("srcPath"), arg("dstLayer"), arg("dstPath")));

  TfPyFunctionFromPython<Py_SdfShouldCopyChildrenSig>();
  TfPyFunctionFromPython<Py_SdfShouldCopyValueSig>();
  def("CopySpec",
      &Py_SdfCopySpec,
      (arg("srcLayer"),
       arg("srcPath"),
       arg("dstLayer"),
       arg("dstPath"),
       arg("shouldCopyValueFn"),
       arg("shouldCopyChildrenFn")));
}
