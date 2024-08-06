//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "CameraUtil/framing.h"

#include "Gf/matrix4d.h"

#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

std::string _Repr(const CameraUtilFraming &self)
{
  static const std::string prefix = TF_PY_REPR_PREFIX + "Framing(";
  static const std::string separator = ",\n" + std::string(prefix.size(), ' ');

  std::vector<std::string> kwargs;
  kwargs.push_back("displayWindow = " + TfPyRepr(self.displayWindow));
  kwargs.push_back("dataWindow = " + TfPyRepr(self.dataWindow));
  if (self.pixelAspectRatio != 1.0f) {
    kwargs.push_back("pixelAspectRatio = " + TfPyRepr(self.pixelAspectRatio));
  }

  return prefix + TfStringJoin(kwargs, separator.c_str()) + ")";
}

}  // namespace

void wrapFraming()
{
  using This = CameraUtilFraming;

  class_<This>("Framing")
      .def(init<>())
      .def(init<const This &>())
      .def(init<const GfRange2f &, const GfRect2i &, float>(
          (args("displayWindow"), args("dataWindow"), args("pixelAspectRatio") = 1.0)))
      .def(init<const GfRect2i>(((args("dataWindow")))))
      .def("ApplyToProjectionMatrix",
           &This::ApplyToProjectionMatrix,
           ((args("projectionMatrix"), args("windowPolicy"))))
      .def("ComputeFilmbackWindow",
           &This::ComputeFilmbackWindow,
           ((args("cameraAspectRatio"), args("windowPolicy"))))
      .def("IsValid", &This::IsValid)
      .def_readwrite("displayWindow", &This::displayWindow)
      .def_readwrite("dataWindow", &This::dataWindow)
      .def_readwrite("pixelAspectRatio", &This::pixelAspectRatio)

      .def(self == self)
      .def(self != self)

      .def("__repr__", _Repr);
}
