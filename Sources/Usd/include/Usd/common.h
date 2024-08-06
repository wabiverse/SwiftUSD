//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_COMMON_H
#define PXR_USD_USD_COMMON_H

/// \file usd/common.h

#include "Sdf/layerOffset.h"
#include "Tf/declarePtrs.h"
#include "Tf/stringUtils.h"
#include "Usd/api.h"
#include "pxr/pxrns.h"

#include "Usd/primDataHandle.h"
#include "Usd/timeCode.h"

#include <map>
#include <string>

PXR_NAMESPACE_OPEN_SCOPE

// Forward declare Usd classes.
class UsdStage;
class UsdObject;
class UsdPrim;
class UsdProperty;
class UsdAttribute;
class UsdRelationship;
class UsdStageCache;

class VtValue;

TF_DECLARE_WEAK_AND_REF_PTRS(UsdStage);
typedef UsdStagePtr UsdStageWeakPtr;

/// Return a human-readable description.
USD_API
std::string UsdDescribe(const UsdObject &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageRefPtr &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageWeakPtr &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStage *);
/// \overload
USD_API
std::string UsdDescribe(const UsdStage &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageCache &);

// XXX:
// Currently used for querying composed values from text layers, so VtValue is
// the optimal value-store, but this may not always be the case.
typedef std::map<class TfToken, VtValue, TfDictionaryLessThan> UsdMetadataValueMap;

/// \enum UsdListPosition
///
/// Specifies a position to add items to lists.  Used by some Add()
/// methods in the USD API that manipulate lists, such as AddReference().
///
enum UsdListPosition {
  /// The position at the front of the prepend list.
  /// An item added at this position will, after composition is applied,
  /// be stronger than other items prepended in this layer, and stronger
  /// than items added by weaker layers.
  UsdListPositionFrontOfPrependList,
  /// The position at the back of the prepend list.
  /// An item added at this position will, after composition is applied,
  /// be weaker than other items prepended in this layer, but stronger
  /// than items added by weaker layers.
  UsdListPositionBackOfPrependList,
  /// The position at the front of the append list.
  /// An item added at this position will, after composition is applied,
  /// be stronger than other items appended in this layer, and stronger
  /// than items added by weaker layers.
  UsdListPositionFrontOfAppendList,
  /// The position at the back of the append list.
  /// An item added at this position will, after composition is applied,
  /// be weaker than other items appended in this layer, but stronger
  /// than items added by weaker layers.
  UsdListPositionBackOfAppendList,
};

/// \enum UsdLoadPolicy
///
/// Controls UsdStage::Load() and UsdPrim::Load() behavior regarding whether or
/// not descendant prims are loaded.
///
enum UsdLoadPolicy {
  /// Load a prim plus all its descendants.
  UsdLoadWithDescendants,
  /// Load a prim by itself with no descendants.
  UsdLoadWithoutDescendants
};

/// \enum UsdSchemaKind
///
/// An enum representing which kind of schema a given schema class belongs to.
/// For more details on the different kinds of schemas, see
/// \ref Usd_Page_GeneratingSchemas.
///
enum class UsdSchemaKind {
  /// Invalid or unknown schema kind.
  Invalid,
  /// Represents abstract or base schema types that are interface-only
  /// and cannot be instantiated. These are reserved for core base classes
  /// known to the usdGenSchema system, so this should never be assigned to
  /// generated schema classes.
  AbstractBase,
  /// Represents a non-concrete typed schema
  AbstractTyped,
  /// Represents a concrete typed schema
  ConcreteTyped,
  /// Non-applied API schema
  NonAppliedAPI,
  /// Single Apply API schema
  SingleApplyAPI,
  /// Multiple Apply API Schema
  MultipleApplyAPI
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
