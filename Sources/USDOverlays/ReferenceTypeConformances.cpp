// This source file is taken from github.com/apple/SwiftUsd
//
// Copyright © 2025 Apple Inc. and the SwiftUsd project authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
//===----------------------------------------------------------------------===//

#include "USDOverlays/ReferenceTypeConformances.h"

void* _Nonnull _address(Pixar::TfRefBase* _Nonnull x)
{
  return reinterpret_cast<void*>(x);
}
Pixar::TfRefBase * _Nullable _fromRawPointer__ZN3Pixar9TfRefBaseE(void* _Nullable p) {
  return __Overlay::dynamic_cast_raw_to_frt<Pixar::TfRefBase>(p);
}

bool __Overlay::operatorEqualsEquals(const Pixar::TfRefBase& l,
                                     const Pixar::TfRefBase& r)
{
  return &l == &r;
}

bool __Overlay::operatorEqualsEquals(const Pixar::TfSimpleRefBase& l,
                                     const Pixar::TfSimpleRefBase& r)
{
  return &l == &r;
}

bool __Overlay::operatorEqualsEquals(const Pixar::UsdStage& l,
                                     const Pixar::UsdStage& r) {
  return &l == &r;
}


void* _Nonnull _address(Pixar::TfSimpleRefBase* _Nonnull x) {
    return reinterpret_cast<void*>(x);
}
Pixar::TfRefPtr<Pixar::TfSimpleRefBase> _asRefPtrType(Pixar::TfSimpleRefBase* _Nonnull x) {
    return Pixar::TfRefPtr<Pixar::TfSimpleRefBase>(x);
}
Pixar::TfSimpleRefBase * _Nullable _fromRefPtrType(const Pixar::TfRefPtr<Pixar::TfSimpleRefBase>& x) {
    if (!x) { return nullptr; }
    Pixar::Tf_RetainReleaseHelper::retain(x.operator->());
    return x.operator->();
}
Pixar::TfSimpleRefBase * _Nullable _fromConstRefPtrType(const Pixar::TfRefPtr<const Pixar::TfSimpleRefBase>& x) {
    if (!x) { return nullptr; }
    Pixar::TfSimpleRefBase* result = const_cast<Pixar::TfSimpleRefBase *>(x.operator->());
    Pixar::Tf_RetainReleaseHelper::retain(result);
    return result;
}
Pixar::TfSimpleRefBase * _Nullable _fromRawPointer__ZN3Pixar15TfSimpleRefBaseE(void* _Nullable p) {
    return __Overlay::dynamic_cast_raw_to_frt<Pixar::TfSimpleRefBase>(p);
}
Pixar::TfRefPtr<Pixar::TfSimpleRefBase>_nullRefPtr__ZN3Pixar15TfSimpleRefBaseE() {
    return Pixar::TfRefPtr<Pixar::TfSimpleRefBase>(nullptr);
}
bool _isNonnull(const Pixar::TfRefPtr<Pixar::TfSimpleRefBase> & p) {
    return (bool)p;
}
bool _isNonnull(const Pixar::TfRefPtr<const Pixar::TfSimpleRefBase> & p) {
    return (bool)p;
}


void* _Nonnull _address(Pixar::UsdStage* _Nonnull x) {
  return reinterpret_cast<void*>(x);
}
Pixar::TfRefPtr<Pixar::UsdStage> _asRefPtrType(Pixar::UsdStage* _Nonnull x) {
  return Pixar::TfRefPtr<Pixar::UsdStage>(x);
}
Pixar::UsdStage * _Nullable _fromRefPtrType(const Pixar::TfRefPtr<Pixar::UsdStage>& x)
{
  if (!x) { return nullptr; }
  Pixar::Tf_RetainReleaseHelper::retain(x.operator->());
  return x.operator->();
}
Pixar::UsdStage * _Nullable _fromConstRefPtrType(const Pixar::TfRefPtr<const Pixar::UsdStage>& x)
{
  if (!x) { return nullptr; }
  Pixar::UsdStage* result = const_cast<Pixar::UsdStage *>(x.operator->());
  Pixar::Tf_RetainReleaseHelper::retain(result);
  return result;
}
Pixar::UsdStage * _Nullable _fromRawPointer__ZN3Pixar8UsdStageE(void* _Nullable p) {
  return __Overlay::dynamic_cast_raw_to_frt<Pixar::UsdStage>(p);
}
Pixar::TfRefPtr<Pixar::UsdStage>_nullRefPtr__ZN3Pixar8UsdStageE()
{
  return Pixar::TfRefPtr<Pixar::UsdStage>(nullptr);
}
bool _isNonnull(const Pixar::TfRefPtr<Pixar::UsdStage> & p)
{
  return (bool)p;
}
bool _isNonnull(const Pixar::TfRefPtr<const Pixar::UsdStage> & p)
{
  return (bool)p;
}
Pixar::TfWeakPtr<Pixar::UsdStage> _asWeakPtrType(Pixar::UsdStage* _Nonnull x) {
  return Pixar::TfWeakPtr<Pixar::UsdStage>(x);
}
Pixar::UsdStage * _Nullable _fromWeakPtrType(const Pixar::TfWeakPtr<Pixar::UsdStage>& x) {
  return _fromRefPtrType(Pixar::TfRefPtr<Pixar::UsdStage>(x));
}
Pixar::UsdStage * _Nullable _fromConstWeakPtrType(const Pixar::TfWeakPtr<const Pixar::UsdStage> & x) {
  if (!x) { return nullptr; }
  Pixar::UsdStage * result = const_cast<Pixar::UsdStage *>(x.operator->());
  Pixar::Tf_RetainReleaseHelper::retain(result);
  return result;
}
Pixar::TfAnyWeakPtr _asAnyWeakPtr(const Pixar::TfWeakPtr<Pixar::UsdStage>& x) {
  return Pixar::TfAnyWeakPtr(x);
}
Pixar::TfWeakPtr<Pixar::UsdStage>_fromAnyWeakPtr__ZN3Pixar8UsdStageE(const Pixar::TfAnyWeakPtr& x) {
  if (!x) { return Pixar::TfWeakPtr<Pixar::UsdStage>(nullptr); }
  Pixar::UsdStage* rawPtr = static_cast<Pixar::UsdStage*>(const_cast<Pixar::TfWeakBase*>(x.GetWeakBase()));
  return Pixar::TfWeakPtr<Pixar::UsdStage>(rawPtr);
}
Pixar::TfWeakPtr<Pixar::UsdStage>_nullWeakPtr__ZN3Pixar8UsdStageE()
{
  return Pixar::TfWeakPtr<Pixar::UsdStage>(nullptr);
}
bool _isNonnull(const Pixar::TfWeakPtr<Pixar::UsdStage> & p) {
  return (bool)p;
}
bool _isNonnull(const Pixar::TfWeakPtr<const Pixar::UsdStage> & p) {
  return (bool)p;
}
