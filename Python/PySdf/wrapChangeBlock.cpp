//
// Copyright 2016 Pixar
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
#include "Sdf/changeBlock.h"
#include "Sdf/changeManager.h"
#include "Tf/diagnostic.h"
#include "Tf/pyUtils.h"
#include <pxr/pxrns.h>

#include <boost/python.hpp>

#include <memory>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

class Sdf_PythonChangeBlock {
public:
  explicit Sdf_PythonChangeBlock(bool enabled) : _enabled(enabled) {}

  void Open() {
    if (!_enabled || !TF_VERIFY(!_block)) {
      return;
    }
    _block.reset(new SdfChangeBlock);
  }

  void Close(object, object, object) {
    if (!_enabled || !TF_VERIFY(_block)) {
      return;
    }
    _block.reset();
  }

private:
  std::unique_ptr<SdfChangeBlock> _block;
  const bool _enabled;
};

} // anonymous namespace

void wrapChangeBlock() {
  // This allows SdfChangeBlocks to be used in an RAII fashion in Python
  // with the 'with' statement.
  typedef Sdf_PythonChangeBlock This;
  class_<This, boost::noncopyable>("ChangeBlock",
                                   init<bool>(arg("enabled") = true))
      .def("__enter__", &This::Open)
      .def("__exit__", &This::Close);
}
