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
#ifndef PXR_BASE_ARCH_MATH_H
#define PXR_BASE_ARCH_MATH_H

/// \file arch/pxrmath.h
/// \ingroup group_arch_Math
/// Architecture-specific math function calls.

#include "PXRBaseArch/defines.h"
#include "PXRBaseArch/pxrinttypes.h"
#include <pxr/pxrns.h>

#if defined(ARCH_COMPILER_MSVC)
#include <intrin.h>
#endif

#include <cmath>
#if !defined(M_PI)
#define M_PI 3.14159265358979323846
#endif

PXR_NAMESPACE_OPEN_SCOPE

/// \addtogroup group_arch_Math
///@{

#if defined(ARCH_CPU_INTEL) || defined(ARCH_CPU_ARM) || defined(doxygen)

/// This is the smallest value e such that 1+e^2 == 1, using floats.
/// True for all IEEE754 chipsets.
#define ARCH_MIN_FLOAT_EPS_SQR 0.000244141F

/// Three-valued sign.  Return 1 if val > 0, 0 if val == 0, or -1 if val < 0.
inline long ArchSign(long val) { return (val > 0) - (val < 0); }

/// Returns The IEEE-754 bit pattern of the specified single precision value
/// as a 32-bit unsigned integer.
inline uint32_t ArchFloatToBitPattern(float v) {
  union {
    float _float;
    uint32_t _uint;
  } value;
  value._float = v;
  return value._uint;
}

/// Returns The single precision floating point value corresponding to the
/// given IEEE-754 bit pattern.
inline float ArchBitPatternToFloat(uint32_t v) {
  union {
    uint32_t _uint;
    float _float;
  } value;
  value._uint = v;
  return value._float;
}

/// Returns The IEEE-754 bit pattern of the specified double precision value
/// as a 64-bit unsigned integer.
inline uint64_t ArchDoubleToBitPattern(double v) {
  union {
    double _double;
    uint64_t _uint;
  } value;
  value._double = v;
  return value._uint;
}

/// Returns The double precision floating point value corresponding to the
/// given IEEE-754 bit pattern.
inline double ArchBitPatternToDouble(uint64_t v) {
  union {
    uint64_t _uint;
    double _double;
  } value;
  value._uint = v;
  return value._double;
}

#else
#error Unknown system architecture.
#endif

#if defined(ARCH_OS_LINUX) || defined(doxygen)

/// Computes the sine and cosine of the specified value as a float.
inline void ArchSinCosf(float v, float *s, float *c) { sincosf(v, s, c); }

/// Computes the sine and cosine of the specified value as a double.
inline void ArchSinCos(double v, double *s, double *c) { sincos(v, s, c); }

#elif defined(ARCH_OS_DARWIN) || defined(ARCH_OS_WINDOWS)

inline void ArchSinCosf(float v, float *s, float *c) {
  *s = std::sin(v);
  *c = std::cos(v);
}
inline void ArchSinCos(double v, double *s, double *c) {
  *s = std::sin(v);
  *c = std::cos(v);
}

#else
#error Unknown architecture.
#endif

/// Return the number of consecutive 0-bits in \p x starting from the least
/// significant bit position.  If \p x is 0, the result is undefined.
inline int ArchCountTrailingZeros(uint64_t x) {
#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_CLANG)
  return __builtin_ctzl(x);
#elif defined(ARCH_COMPILER_MSVC)
  unsigned long index;
  _BitScanForward64(&index, x);
  return index;
#else
  // Flip trailing zeros to 1s, and clear all other bits, then count.
  x = (x ^ (x - 1)) >> 1;
  int c = 0;
  for (; x; ++c) {
    x >>= 1;
  }
  return c;
#endif
}

///@}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_BASE_ARCH_MATH_H