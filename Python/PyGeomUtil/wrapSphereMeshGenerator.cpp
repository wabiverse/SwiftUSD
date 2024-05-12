//
// Copyright 2022 Pixar
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
#include "GeomUtil/sphereMeshGenerator.h"

#include "PxOsd/meshTopology.h"

#include "Vt/types.h"

#include <boost/python/class.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static VtVec3fArray
_WrapGeneratePoints(
    const size_t numRadial,
    const size_t numAxial,
    const float radius)
{
  const size_t numPoints =
      GeomUtilSphereMeshGenerator::ComputeNumPoints(numRadial, numAxial);
  if (numPoints == 0)
  {
    return VtVec3fArray();
  }

  VtVec3fArray points(numPoints);
  GeomUtilSphereMeshGenerator::GeneratePoints(
      points.begin(), numRadial, numAxial, radius);

  return points;
}

void wrapSphereMeshGenerator()
{
  using This = GeomUtilSphereMeshGenerator;

  // Pull the constexpr values into variables so boost can odr-use them.
  static constexpr size_t minNumRadial = This::minNumRadial;
  static constexpr size_t minNumAxial = This::minNumAxial;

  // Note: These are only "classes" for name scoping, and are uninstantiable;
  // hence no need to bother declaring bases.
  class_<This>("SphereMeshGenerator", no_init)
      .def_readonly("minNumRadial", minNumRadial)
      .def_readonly("minNumAxial", minNumAxial)

      .def("ComputeNumPoints", &This::ComputeNumPoints)
      .staticmethod("ComputeNumPoints")

      .def("GenerateTopology", &This::GenerateTopology)
      .staticmethod("GenerateTopology")

      .def("GeneratePoints", &_WrapGeneratePoints)
      .staticmethod("GeneratePoints");
}