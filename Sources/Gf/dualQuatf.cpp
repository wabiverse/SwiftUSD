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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// dualQuat.template.cpp file to make changes.

#include "Gf/dualQuatf.h"
#include "Gf/ostreamHelpers.h"
#include "Tf/type.h"
#include <pxr/pxrns.h>

#include "Gf/dualQuatd.h"
#include "Gf/dualQuath.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType) { TfType::Define<GfDualQuatf>(); }

GfDualQuatf::GfDualQuatf(const GfDualQuatd &other)
    : _real(other.GetReal()), _dual(other.GetDual()) {}
GfDualQuatf::GfDualQuatf(const GfDualQuath &other)
    : _real(other.GetReal()), _dual(other.GetDual()) {}

std::pair<float, float> GfDualQuatf::GetLength() const {
  const float realLength = _real.GetLength();

  if (realLength == 0)
    return std::pair<float, float>{0, 0};

  return std::pair<float, float>{realLength, GfDot(_real, _dual) / realLength};
}

GfDualQuatf GfDualQuatf::GetNormalized(float eps) const {
  GfDualQuatf dq(*this);
  dq.Normalize(eps);

  return dq;
}

std::pair<float, float> GfDualQuatf::Normalize(float eps) {
  const std::pair<float, float> length = GetLength();
  const float realLength = length.first;

  if (realLength < eps) {
    (*this) = GfDualQuatf::GetIdentity();
  } else {
    const float invRealLength = 1.0 / realLength;
    _real *= invRealLength;
    _dual *= invRealLength;

    _dual -= (GfDot(_real, _dual) * _real);
  }

  return length;
}

GfDualQuatf GfDualQuatf::GetConjugate() const {
  return GfDualQuatf(_real.GetConjugate(), _dual.GetConjugate());
}

GfDualQuatf GfDualQuatf::GetInverse() const {
  // DQ * DQ.GetInverse() == GetIdentity()
  const float realLengthSqr = GfDot(_real, _real);

  if (realLengthSqr <= 0.0)
    return GfDualQuatf::GetIdentity();

  const float invRealLengthSqr = 1.0 / realLengthSqr;
  const GfDualQuatf conjInvLenSqr = GetConjugate() * invRealLengthSqr;
  const GfQuatf realPart = conjInvLenSqr.GetReal();
  const GfQuatf dualPart =
      conjInvLenSqr.GetDual() -
      (2.0 * invRealLengthSqr * GfDot(_real, _dual) * conjInvLenSqr.GetReal());

  return GfDualQuatf(realPart, dualPart);
}

void GfDualQuatf::SetTranslation(const GfVec3f &translation) {
  // compute and set the dual part
  _dual = GfQuatf(0.0, 0.5 * translation) * _real;
}

GfVec3f GfDualQuatf::GetTranslation() const {
  // _dual = GfQuatf(0, 0.5*translation) * _real
  // => translation = 2 * (_dual * _real.GetConjugate()).GetImaginary()

  // Assume that this dual quaternion is normalized
  TF_DEV_AXIOM(GfIsClose(_real.GetLength(), 1.0, 0.001));
  const float r1 = _dual.GetReal();
  const float r2 = _real.GetReal();
  const GfVec3f &i1 = _dual.GetImaginary();
  const GfVec3f &i2 = _real.GetImaginary();

  // Translation of the dual quaternion: -2.0 * (r1*i2 - r2*i1 + i1^i2)
  return GfVec3f(
      -2.0 * (r1 * i2[0] - r2 * i1[0] + (i1[1] * i2[2] - i1[2] * i2[1])),
      -2.0 * (r1 * i2[1] - r2 * i1[1] + (i1[2] * i2[0] - i1[0] * i2[2])),
      -2.0 * (r1 * i2[2] - r2 * i1[2] + (i1[0] * i2[1] - i1[1] * i2[0])));
}

GfDualQuatf &GfDualQuatf::operator*=(const GfDualQuatf &dq) {
  const GfQuatf tempReal = GetReal() * dq.GetReal();
  const GfQuatf tempDual = GetReal() * dq.GetDual() + GetDual() * dq.GetReal();

  SetReal(tempReal);
  SetDual(tempDual);

  return *this;
}

GfVec3f GfDualQuatf::Transform(const GfVec3f &vec) const {
  // Apply rotation and translation
  return GetReal().Transform(vec) + GetTranslation();
}

std::ostream &operator<<(std::ostream &out, const GfDualQuatf &dq) {
  return (out << '(' << Gf_OstreamHelperP(dq.GetReal()) << ", "
              << Gf_OstreamHelperP(dq.GetDual()) << ')');
}

PXR_NAMESPACE_CLOSE_SCOPE