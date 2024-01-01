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
#ifndef PXR_BASE_TF_DECLARE_PTRS_H
#define PXR_BASE_TF_DECLARE_PTRS_H

/// \file Tf/declarePtrs.h
/// Standard pointer typedefs.
///
/// This file provides typedefs for standard pointer types.

#include <pxr/pxrns.h>

#include "Tf/weakPtr.h"
#include "Tf/refPtr.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

/// \struct TfDeclarePtrs
/// Templated struct used for type definition macros.
template <typename T> struct TfDeclarePtrs {
  using ClsType = T;
  
  using Ptr = TfWeakPtr<ClsType>;
  using ConstPtr = TfWeakPtr<const ClsType>;
  using PtrVector = std::vector<Ptr>;
  using ConstPtrVector = std::vector<ConstPtr>;

  using RefPtr = TfRefPtr<ClsType>;
  using ConstRefPtr = TfRefPtr<const ClsType>;
  using RefPtrVector = std::vector<RefPtr>;
  using ConstRefPtrVector = std::vector<ConstRefPtr>;
};

/// Define standard weak pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_WEAK_PTRS(Class) declares ClassPtr, ClassConstPtr,
/// ClassPtrVector and ClassConstPtrVector.
///
/// \hideinitializer
#define TF_DECLARE_WEAK_PTRS(type)                                          \
  using type##Ptr = TfDeclarePtrs<class type>::Ptr;                         \
  using type##ConstPtr = TfDeclarePtrs<class type>::ConstPtr;               \
  using type##PtrVector = TfDeclarePtrs<class type>::PtrVector;             \
  using type##ConstPtrVector = TfDeclarePtrs<class type>::ConstPtrVector

/// Define standard ref pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_REF_PTRS(Class) declares ClassRefPtr and ClassConstRefPtr.
///
/// \hideinitializer
#define TF_DECLARE_REF_PTRS(type)                                              \
  using type##RefPtr = TfDeclarePtrs<class type>::RefPtr;                      \
  using type##ConstRefPtr = TfDeclarePtrs<class type>::ConstRefPtr;            \
  using type##RefPtrVector = TfDeclarePtrs<class type>::RefPtrVector;          \
  using type##ConstRefPtrVector = TfDeclarePtrs<class type>::ConstRefPtrVector

/// Define standard weak, ref, and vector pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_WEAK_AND_REF_PTRS(Class) declares ClassPtr, ClassConstPtr,
/// ClassPtrVector, ClassConstPtrVector, ClassRefPtr and ClassConstRefPtr.
///
/// \hideinitializer
#define TF_DECLARE_WEAK_AND_REF_PTRS(type)                                     \
  TF_DECLARE_WEAK_PTRS(type);                                                  \
  TF_DECLARE_REF_PTRS(type)

PXR_NAMESPACE_CLOSE_SCOPE

#endif
