//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_GF_SIZE3_H
#define PXR_BASE_GF_SIZE3_H

/// \file gf/size3.h
/// \ingroup group_gf_LinearAlgebra

#include "Arch/inttypes.h"
#include "Gf/api.h"
#include "Gf/vec3i.h"
#include "pxr/pxrns.h"

#include <iosfwd>

PXR_NAMESPACE_OPEN_SCOPE

/// \class GfSize3
/// \ingroup group_gf_LinearAlgebra
///
/// Three-dimensional array of sizes
///
/// GfSize3 is used to represent triples of counts.  It is based on the
/// datatype size_t, and thus can only represent non-negative values in each
/// dimension.  If you need to represent negative numbers as well, use GfVeci.
///
/// Usage of GfSize3 is similar to that of GfVec3i, except that all
/// mathematical operations are componentwise (including multiplication).
///
class GfSize3 {
 public:
  /// Default constructor initializes components to zero
  GfSize3()
  {
    Set(0, 0, 0);
  }

  /// Copy constructor.
  GfSize3(const GfSize3 &o)
  {
    *this = o;
  }

  /// Conversion from GfVec3i
  explicit GfSize3(const GfVec3i &o)
  {
    Set(o[0], o[1], o[2]);
  }

  /// Construct from an array
  GfSize3(const size_t v[3])
  {
    Set(v);
  }

  /// Construct from three values
  GfSize3(size_t v0, size_t v1, size_t v2)
  {
    Set(v0, v1, v2);
  }

  /// Set to the values in \p v.
  GfSize3 &Set(const size_t v[3])
  {
    _vec[0] = v[0];
    _vec[1] = v[1];
    _vec[2] = v[2];
    return *this;
  }

  /// Set to values passed directly
  GfSize3 &Set(size_t v0, size_t v1, size_t v2)
  {
    _vec[0] = v0;
    _vec[1] = v1;
    _vec[2] = v2;
    return *this;
  }

  /// Array operator
  size_t &operator[](size_t i)
  {
    return _vec[i];
  }

  /// Const array operator
  const size_t &operator[](size_t i) const
  {
    return _vec[i];
  }

  /// Component-wise equality
  bool operator==(const GfSize3 &v) const
  {
    return _vec[0] == v._vec[0] && _vec[1] == v._vec[1] && _vec[2] == v._vec[2];
  }

  /// Component-wise inequality
  bool operator!=(const GfSize3 &v) const
  {
    return !(*this == v);
  }

  /// Component-wise in-place addition
  GfSize3 &operator+=(const GfSize3 &v)
  {
    _vec[0] += v._vec[0];
    _vec[1] += v._vec[1];
    _vec[2] += v._vec[2];
    return *this;
  }

  /// Component-wise in-place subtraction
  GfSize3 &operator-=(const GfSize3 &v)
  {
    _vec[0] -= v._vec[0];
    _vec[1] -= v._vec[1];
    _vec[2] -= v._vec[2];
    return *this;
  }

  /// Component-wise in-place multiplication.
  GfSize3 &operator*=(GfSize3 const &v)
  {
    _vec[0] *= v._vec[0];
    _vec[1] *= v._vec[1];
    _vec[2] *= v._vec[2];
    return *this;
  }

  /// Component-wise in-place multiplication by a scalar
  GfSize3 &operator*=(size_t d)
  {
    _vec[0] = _vec[0] * d;
    _vec[1] = _vec[1] * d;
    _vec[2] = _vec[2] * d;
    return *this;
  }

  /// Component-wise in-place division by a scalar
  GfSize3 &operator/=(size_t d)
  {
    _vec[0] = _vec[0] / d;
    _vec[1] = _vec[1] / d;
    _vec[2] = _vec[2] / d;
    return *this;
  }

  /// Component-wise addition
  friend GfSize3 operator+(const GfSize3 &v1, const GfSize3 &v3)
  {
    return GfSize3(v1._vec[0] + v3._vec[0], v1._vec[1] + v3._vec[1], v1._vec[2] + v3._vec[2]);
  }

  /// Component-wise subtraction
  friend GfSize3 operator-(const GfSize3 &v1, const GfSize3 &v3)
  {
    return GfSize3(v1._vec[0] - v3._vec[0], v1._vec[1] - v3._vec[1], v1._vec[2] - v3._vec[2]);
  }

  /// Component-wise multiplication
  friend GfSize3 operator*(const GfSize3 &v1, const GfSize3 &v3)
  {
    return GfSize3(v1._vec[0] * v3._vec[0], v1._vec[1] * v3._vec[1], v1._vec[2] * v3._vec[2]);
  }

  /// Component-wise multiplication by a scalar
  friend GfSize3 operator*(const GfSize3 &v1, size_t s)
  {
    return GfSize3(v1._vec[0] * s, v1._vec[1] * s, v1._vec[2] * s);
  }

  /// Component-wise multiplication by a scalar
  friend GfSize3 operator*(size_t s, const GfSize3 &v1)
  {
    return GfSize3(v1._vec[0] * s, v1._vec[1] * s, v1._vec[2] * s);
  }

  /// Component-wise division by a scalar
  friend GfSize3 operator/(const GfSize3 &v1, size_t s)
  {
    return GfSize3(v1._vec[0] / s, v1._vec[1] / s, v1._vec[2] / s);
  }

  /// Output operator
  friend GF_API std::ostream &operator<<(std::ostream &o, GfSize3 const &v);

  /// Conversion to GfVec3i
  operator GfVec3i() const
  {
    return GfVec3i(_vec[0], _vec[1], _vec[2]);
  }

 private:
  size_t _vec[3];
};

// Friend functions must be declared
GF_API std::ostream &operator<<(std::ostream &o, GfSize3 const &v);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_GF_SIZE3_H
