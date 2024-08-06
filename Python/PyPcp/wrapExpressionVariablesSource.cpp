//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "Pcp/cache.h"
#include "Pcp/expressionVariablesSource.h"
#include "Pcp/layerStackIdentifier.h"

#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_value_policy.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapExpressionVariablesSource()
{
  using This = PcpExpressionVariablesSource;

  class_<This>("ExpressionVariablesSource")
      .def(init<>())
      .def(init<const PcpLayerStackIdentifier &, const PcpLayerStackIdentifier &>(
          (args("layerStackId"), args("rootLayerStackId"))))

      .def(self == self)
      .def(self != self)

      .def("IsRootLayerStack", &This::IsRootLayerStack)
      .def(
          "GetLayerStackIdentifier",
          +[](const This &s) {
            const PcpLayerStackIdentifier *id = s.GetLayerStackIdentifier();
            return id ? object(*id) : object();
          })
      .def("ResolveLayerStackIdentifier",
           (const PcpLayerStackIdentifier &(This::*)(const PcpLayerStackIdentifier &) const) &
               This::ResolveLayerStackIdentifier,
           return_value_policy<return_by_value>())

      .def("ResolveLayerStackIdentifier",
           (const PcpLayerStackIdentifier &(This::*)(const PcpCache &) const) &
               This::ResolveLayerStackIdentifier,
           return_value_policy<return_by_value>())

      .def(
          "__repr__", +[](const PcpExpressionVariablesSource &s) {
            return TfStringPrintf(
                "%sExpressionVariablesSource(%s)",
                TF_PY_REPR_PREFIX.c_str(),
                s.IsRootLayerStack() ? "" : TfPyRepr(*s.GetLayerStackIdentifier()).c_str());
          });
}
