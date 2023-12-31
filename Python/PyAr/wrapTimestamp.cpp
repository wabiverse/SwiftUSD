//
// Copyright 2021 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include <pxr/pxrns.h>

#include "Ar/timestamp.h"

#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static size_t __hash__(const ArTimestamp &self) { return TfHash()(self); }

static std::string __repr__(const ArTimestamp &self) {
  return TF_PY_REPR_PREFIX + "Timestamp" +
         (self.IsValid()
              ? TfStringPrintf("(%s)", TfPyRepr(self.GetTime()).c_str())
              : "()");
}

void wrapTimestamp() {
  class_<ArTimestamp>("Timestamp")
      .def(init<double>())
      .def(init<ArTimestamp>())

      .def("IsValid", &ArTimestamp::IsValid)
      .def("GetTime", &ArTimestamp::GetTime)

      .def(self == self)
      .def(self != self)
      .def(self < self)
      .def(self <= self)
      .def(self > self)
      .def(self >= self)

      .def("__hash__", __hash__)
      .def("__repr__", __repr__);
}
