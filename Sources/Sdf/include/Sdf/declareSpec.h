//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_DECLARE_SPEC_H
#define PXR_USD_SDF_DECLARE_SPEC_H

#include "Sdf/api.h"
#include "Sdf/declareHandles.h"
#include "Sdf/specType.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfSpec;

/// Helper macros for implementing C++ spec classes corresponding to
/// the various scene description spec types defined by Sdf. There are
/// two macros that each C++ spec class must invoke, one in the class
/// definition and one in the implementation .cpp file. For example:
///
/// <in MySpecType.h>
/// class MySpecType : public MyBaseSpecType {
///     SDF_DECLARE_SPEC(MySpecType, MyBaseSpecType);
///     ...
/// };
///
/// <in MySpecType.cpp>
/// SDF_DEFINE_SPEC(MySchemaType, <SdfSpecType enum value>, MySpecType,
///                 MyBaseSpecType);
///
/// There are two sets of these macros, one for concrete spec types
/// and one for 'abstract' spec types that only serve as a base class
/// for concrete specs.
///
#define SDF_DECLARE_ABSTRACT_SPEC(SpecType, BaseSpecType) \
 public: \
  SpecType() {} \
  SpecType(const SpecType &spec) : BaseSpecType(spec) {} \
  explicit SpecType(const Sdf_IdentityRefPtr &identity) : BaseSpecType(identity) {} \
\
 protected: \
  friend struct Sdf_CastAccess; \
  explicit SpecType(const SdfSpec &spec) : BaseSpecType(spec) {}

#define SDF_DEFINE_ABSTRACT_SPEC(SchemaType, SpecType, BaseSpecType) \
  TF_REGISTRY_FUNCTION_WITH_TAG(TfType, Type) \
  { \
    TfType::Define<SpecType, TfType::Bases<BaseSpecType>>(); \
  } \
  TF_REGISTRY_FUNCTION_WITH_TAG(SdfSpecTypeRegistration, Registration) \
  { \
    SdfSpecTypeRegistration::RegisterAbstractSpecType<SchemaType, SpecType>(); \
  }

// ------------------------------------------------------------

#define SDF_DECLARE_SPEC(SpecType, BaseSpecType) SDF_DECLARE_ABSTRACT_SPEC(SpecType, BaseSpecType)

#define SDF_DEFINE_SPEC(SchemaType, SpecTypeEnum, SpecType, BaseSpecType) \
  TF_REGISTRY_FUNCTION_WITH_TAG(TfType, Type) \
  { \
    TfType::Define<SpecType, TfType::Bases<BaseSpecType>>(); \
  } \
  TF_REGISTRY_FUNCTION_WITH_TAG(SdfSpecTypeRegistration, Registration) \
  { \
    SdfSpecTypeRegistration::RegisterSpecType<SchemaType, SpecType>(SpecTypeEnum); \
  }

// ------------------------------------------------------------
// Special set of macros for SdfSpec only.

#define SDF_DECLARE_BASE_SPEC(SpecType) \
 public: \
  SpecType() {} \
  SpecType(const SpecType &spec) : _id(spec._id) {} \
  explicit SpecType(const Sdf_IdentityRefPtr &id) : _id(id) {}

#define SDF_DEFINE_BASE_SPEC(SchemaType, SpecType) \
  TF_REGISTRY_FUNCTION_WITH_TAG(TfType, Type) \
  { \
    TfType::Define<SpecType>(); \
  } \
  TF_REGISTRY_FUNCTION_WITH_TAG(SdfSpecTypeRegistration, Registration) \
  { \
    SdfSpecTypeRegistration::RegisterAbstractSpecType<SchemaType, SpecType>(); \
  }

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_SDF_DECLARE_SPEC_H
