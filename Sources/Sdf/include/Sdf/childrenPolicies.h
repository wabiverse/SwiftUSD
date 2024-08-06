//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_CHILDREN_POLICIES_H
#define PXR_USD_SDF_CHILDREN_POLICIES_H

// These policies are used as template arguments to SdfChildrenView to
// determine how the view maps between keys (the child's name or path) and
// values (the child's SpecHandle).

#include "Sdf/api.h"
#include "Sdf/declareHandles.h"
#include "Sdf/path.h"
#include "Sdf/proxyPolicies.h"
#include "Sdf/schema.h"
#include "Sdf/types.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

SDF_DECLARE_HANDLES(SdfAttributeSpec);
SDF_DECLARE_HANDLES(SdfPrimSpec);
SDF_DECLARE_HANDLES(SdfPropertySpec);
SDF_DECLARE_HANDLES(SdfRelationshipSpec);
SDF_DECLARE_HANDLES(SdfVariantSpec);
SDF_DECLARE_HANDLES(SdfVariantSetSpec);

//
// Token Child Policies
//

template<class SpecType> class Sdf_TokenChildPolicy {
 public:
  typedef SdfNameKeyPolicy KeyPolicy;
  typedef KeyPolicy::value_type KeyType;
  typedef TfToken FieldType;
  typedef SpecType ValueType;

  static KeyType GetKey(const ValueType &spec)
  {
    return spec->GetPath().GetName();
  }

  static SdfPath GetParentPath(const SdfPath &childPath)
  {
    return childPath.GetParentPath();
  }

  static FieldType GetFieldValue(const SdfPath &childPath)
  {
    return childPath.GetNameToken();
  }

  static bool IsValidIdentifier(const std::string &name)
  {
    return SdfSchema::IsValidIdentifier(name);
  }
};

class Sdf_PrimChildPolicy : public Sdf_TokenChildPolicy<SdfPrimSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendChild(key);
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->PrimChildren;
  }
};

class Sdf_PropertyChildPolicy : public Sdf_TokenChildPolicy<SdfPropertySpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    if (parentPath.IsTargetPath()) {
      return parentPath.AppendRelationalAttribute(key);
    }
    else {
      return parentPath.AppendProperty(key);
    }
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->PropertyChildren;
  }

  static bool IsValidIdentifier(const std::string &name)
  {
    return SdfSchema::IsValidNamespacedIdentifier(name);
  }
};

class Sdf_AttributeChildPolicy : public Sdf_TokenChildPolicy<SdfAttributeSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    if (parentPath.IsTargetPath()) {
      return parentPath.AppendRelationalAttribute(key);
    }
    else {
      return parentPath.AppendProperty(key);
    }
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->PropertyChildren;
  }

  static bool IsValidIdentifier(const std::string &name)
  {
    return SdfSchema::IsValidNamespacedIdentifier(name);
  }
};

class Sdf_RelationshipChildPolicy : public Sdf_TokenChildPolicy<SdfRelationshipSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendProperty(key);
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->PropertyChildren;
  }

  static bool IsValidIdentifier(const std::string &name)
  {
    return SdfSchema::IsValidNamespacedIdentifier(name);
  }
};

class Sdf_MapperArgChildPolicy : public Sdf_TokenChildPolicy<SdfSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendMapperArg(key);
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->MapperArgChildren;
  }
};

class Sdf_ExpressionChildPolicy : public Sdf_TokenChildPolicy<SdfSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendExpression();
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->ExpressionChildren;
  }
};

class Sdf_VariantChildPolicy : public Sdf_TokenChildPolicy<SdfVariantSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    std::string variantSet = parentPath.GetVariantSelection().first;
    return parentPath.GetParentPath().AppendVariantSelection(TfToken(variantSet), key);
  }

  static SdfPath GetParentPath(const SdfPath &childPath)
  {
    // Construct a path with the same variant set but an empty variant
    std::string variantSet = childPath.GetVariantSelection().first;
    return childPath.GetParentPath().AppendVariantSelection(variantSet, "");
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->VariantChildren;
  }
};

class Sdf_VariantSetChildPolicy : public Sdf_TokenChildPolicy<SdfVariantSetSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendVariantSelection(key, "");
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->VariantSetChildren;
  }
};

//
// Path Child Policies
//

template<class SpecType> class Sdf_PathChildPolicy {
 public:
  typedef SdfPathKeyPolicy KeyPolicy;
  typedef KeyPolicy::value_type KeyType;
  typedef SpecType ValueType;
  typedef SdfPath FieldType;

  static SdfPath GetParentPath(const SdfPath &childPath)
  {
    return childPath.GetParentPath();
  }

  static KeyType GetKey(const ValueType &value)
  {
    return value->GetPath().GetTargetPath();
  }

  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    return parentPath.AppendTarget(key);
  }

  static FieldType GetFieldValue(const SdfPath &childPath)
  {
    return childPath.GetTargetPath();
  }

  static bool IsValidIdentifier(const FieldType &path)
  {
    return true;
  }

  static bool IsValidIdentifier(const std::string &path)
  {
    return SdfPath::IsValidPathString(path);
  }
};

class Sdf_MapperChildPolicy : public Sdf_PathChildPolicy<SdfSpecHandle> {
 public:
  static SdfPath GetChildPath(const SdfPath &parentPath, const FieldType &key)
  {
    SdfPath targetPath = key.MakeAbsolutePath(parentPath.GetPrimPath());
    return parentPath.AppendMapper(targetPath);
  }

  static FieldType GetFieldValue(const SdfPath &childPath)
  {
    SdfPath targetPath = childPath.GetTargetPath();
    return targetPath.MakeAbsolutePath(childPath.GetPrimPath());
  }

  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->MapperChildren;
  }
};

class Sdf_AttributeConnectionChildPolicy : public Sdf_PathChildPolicy<SdfSpecHandle> {
 public:
  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->ConnectionChildren;
  }
};

class Sdf_RelationshipTargetChildPolicy : public Sdf_PathChildPolicy<SdfSpecHandle> {

 public:
  static TfToken GetChildrenToken(const SdfPath &parentPath)
  {
    return SdfChildrenKeys->RelationshipTargetChildren;
  }
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_SDF_CHILDREN_POLICIES_H
