//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ndr/declare.h"
#include "Tf/pyEnum.h"
#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static std::string _Repr(const NdrVersion &x)
{
  auto result = TF_PY_REPR_PREFIX;
  if (!x) {
    result += "Version()";
  }
  else {
    result += TfStringPrintf(
        "Version(%s, %s)", TfPyRepr(x.GetMajor()).c_str(), TfPyRepr(x.GetMinor()).c_str());
  }
  if (x.IsDefault()) {
    result += ".GetAsDefault()";
  }
  return result;
}

static void wrapVersion()
{
  typedef NdrVersion This;

  class_<This>("Version", no_init)
      .def(init<>())
      .def(init<int>())
      .def(init<int, int>())
      .def(init<std::string>())
      .def("GetMajor", &This::GetMajor)
      .def("GetMinor", &This::GetMinor)
      .def("IsDefault", &This::IsDefault)
      .def("GetAsDefault", &This::GetAsDefault)
      .def("GetStringSuffix", &This::GetStringSuffix)
      .def("__repr__", _Repr)
      .def("__str__", &This::GetString)
      .def("__hash__", &This::GetHash)
      .def(!self)
      .def(self == self)
      .def(self != self)
      .def(self < self)
      .def(self <= self)
      .def(self > self)
      .def(self >= self);
}

}  // namespace

void wrapDeclare()
{
  wrapVersion();

  TfPyWrapEnum<NdrVersionFilter>();
}
