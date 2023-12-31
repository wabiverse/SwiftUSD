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

#include "Vt/streamOut.h"
#include "Arch/demangle.h"
#include "Tf/stringUtils.h"
#include "Vt/types.h"
#include <pxr/pxrns.h>

#ifdef PXR_PYTHON_SUPPORT_ENABLED
#include "Tf/pyObjWrapper.h"
#include "Tf/pyUtils.h"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <numeric>
#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

std::ostream &Vt_StreamOutGeneric(std::type_info const &type, void const *addr,
                                  std::ostream &stream) {
  return stream << TfStringPrintf("<'%s' @ %p>", ArchGetDemangled(type).c_str(),
                                  addr);
}

std::ostream &VtStreamOut(bool const &val, std::ostream &stream) {
  return stream << static_cast<int>(val);
}

std::ostream &VtStreamOut(char const &val, std::ostream &stream) {
  return stream << static_cast<int>(val);
}

std::ostream &VtStreamOut(unsigned char const &val, std::ostream &stream) {
  return stream << static_cast<unsigned int>(val);
}

std::ostream &VtStreamOut(signed char const &val, std::ostream &stream) {
  return stream << static_cast<int>(val);
}

std::ostream &VtStreamOut(float const &val, std::ostream &stream) {
  return stream << TfStreamFloat(val);
}

std::ostream &VtStreamOut(double const &val, std::ostream &stream) {
  return stream << TfStreamDouble(val);
}

namespace {

void _StreamArrayRecursive(std::ostream &out, const Vt_ShapeData &shape,
                           TfFunctionRef<void(std::ostream &)> streamNextElem,
                           size_t lastDimSize, size_t dimension) {
  out << '[';
  if (dimension == shape.GetRank() - 1) {
    for (size_t j = 0; j < lastDimSize; ++j) {
      if (j) {
        out << ", ";
      }
      streamNextElem(out);
    }
  } else {
    for (size_t j = 0; j < shape.otherDims[dimension]; ++j) {
      if (j) {
        out << ", ";
      }
      _StreamArrayRecursive(out, shape, streamNextElem, lastDimSize,
                            dimension + 1);
    }
  }
  out << ']';
}

} // namespace

void VtStreamOutArray(std::ostream &out, const Vt_ShapeData *shapeData,
                      TfFunctionRef<void(std::ostream &)> streamNextElem) {
  // Compute last dim size, and if size is not evenly divisible, output as
  // rank-1.
  size_t divisor = std::accumulate(
      shapeData->otherDims, shapeData->otherDims + shapeData->GetRank() - 1, 1,
      [](size_t x, size_t y) { return x * y; });

  size_t lastDimSize = divisor ? shapeData->totalSize / divisor : 0;
  size_t remainder = divisor ? shapeData->totalSize % divisor : 0;

  // If there's a remainder, make a rank-1 shapeData.
  Vt_ShapeData rank1;
  if (remainder) {
    rank1.totalSize = shapeData->totalSize;
    shapeData = &rank1;
  }

  _StreamArrayRecursive(out, *shapeData, streamNextElem, lastDimSize, 0);
}

#ifdef PXR_PYTHON_SUPPORT_ENABLED
std::ostream &VtStreamOut(TfPyObjWrapper const &obj, std::ostream &stream) {
  return stream << TfPyObjectRepr(obj.Get());
}
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_CLOSE_SCOPE
