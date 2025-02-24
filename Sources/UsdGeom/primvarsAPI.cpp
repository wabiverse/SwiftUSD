//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/primvarsAPI.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomPrimvarsAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdGeomPrimvarsAPI::~UsdGeomPrimvarsAPI() {}

/* static */
UsdGeomPrimvarsAPI UsdGeomPrimvarsAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomPrimvarsAPI();
  }
  return UsdGeomPrimvarsAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdGeomPrimvarsAPI::_GetSchemaKind() const
{
  return UsdGeomPrimvarsAPI::schemaKind;
}

/* static */
const TfType &UsdGeomPrimvarsAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomPrimvarsAPI>();
  return tfType;
}

/* static */
bool UsdGeomPrimvarsAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomPrimvarsAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

/*static*/
const TfTokenVector &UsdGeomPrimvarsAPI::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames;
  static TfTokenVector allNames = UsdAPISchemaBase::GetSchemaAttributeNames(true);

  if (includeInherited)
    return allNames;
  else
    return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

PXR_NAMESPACE_OPEN_SCOPE

UsdGeomPrimvar UsdGeomPrimvarsAPI::CreatePrimvar(const TfToken &name,
                                                 const SdfValueTypeName &typeName,
                                                 const TfToken &interpolation,
                                                 int elementSize) const
{
  const UsdPrim &prim = GetPrim();

  UsdGeomPrimvar primvar(prim, name, typeName);

  if (primvar) {
    if (!interpolation.IsEmpty())
      primvar.SetInterpolation(interpolation);
    if (elementSize > 0)
      primvar.SetElementSize(elementSize);
  }
  // otherwise, errors have already been issued
  return primvar;
}

bool UsdGeomPrimvarsAPI::RemovePrimvar(const TfToken &name)
{
  const TfToken &attrName = UsdGeomPrimvar::_MakeNamespaced(name);
  if (attrName.IsEmpty()) {
    return false;
  }

  UsdPrim prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("RemovePrimvar called on invalid prim: %s", UsdDescribe(prim).c_str());
    return false;
  }

  const UsdGeomPrimvar &primvar = UsdGeomPrimvar(prim.GetAttribute(attrName));
  if (!primvar) {
    return false;
  }

  const UsdAttribute &indexAttr = primvar.GetIndicesAttr();
  bool success = true;
  // If the Primvar is an indexed primvar, also remove the indexAttr
  if (indexAttr) {
    success = prim.RemoveProperty(indexAttr.GetName());
  }
  return prim.RemoveProperty(attrName) && success;
}

void UsdGeomPrimvarsAPI::BlockPrimvar(const TfToken &name)
{
  const TfToken &attrName = UsdGeomPrimvar::_MakeNamespaced(name);
  if (attrName.IsEmpty()) {
    return;
  }

  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("RemovePrimvar called on invalid prim: %s", UsdDescribe(prim).c_str());
    return;
  }

  const UsdGeomPrimvar &primvar = UsdGeomPrimvar(prim.GetAttribute(name));
  if (!primvar) {
    return;
  }

  // Always block indices attr irrespective of primvar is indexed or not
  // This prevents leak of indices attr in a composed stage when a stronger
  // layer has blocked the primvar and at a later time weaker layer adds
  // indices to the primvar
  primvar.BlockIndices();

  primvar.GetAttr().Block();
}

UsdGeomPrimvar UsdGeomPrimvarsAPI::GetPrimvar(const TfToken &name) const
{
  // The getter SHOULD issue an error if 'name' is malformed, which
  // _MakeNamespaced() will do for us.
  return UsdGeomPrimvar(GetPrim().GetAttribute(UsdGeomPrimvar::_MakeNamespaced(name)));
}

static std::vector<UsdGeomPrimvar> _MakePrimvars(std::vector<UsdProperty> const &props,
                                                 bool(filterPass)(UsdGeomPrimvar const &))
{
  std::vector<UsdGeomPrimvar> primvars;
  primvars.reserve(props.size());
  for (UsdProperty const &prop : props) {
    // All prefixed properties except the ones that contain extra
    // namespaces (eg. the ":indices" attributes belonging to indexed
    // primvars) will be valid primvars.
    UsdGeomPrimvar primvar = UsdGeomPrimvar(prop.As<UsdAttribute>());
    if (primvar && filterPass(primvar)) {
      primvars.push_back(std::move(primvar));
    }
  }
  return primvars;
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::GetPrimvars() const
{
  TRACE_FUNCTION();
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("Called GetPrimvars on invalid prim: %s", UsdDescribe(prim).c_str());
    return std::vector<UsdGeomPrimvar>();
  }
  return _MakePrimvars(prim.GetPropertiesInNamespace(UsdGeomPrimvar::_GetNamespacePrefix()),
                       [](UsdGeomPrimvar const &) { return true; });
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::GetAuthoredPrimvars() const
{
  TRACE_FUNCTION();
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("Called GetAuthoredPrimvars on invalid prim: %s", UsdDescribe(prim).c_str());
    return std::vector<UsdGeomPrimvar>();
  }
  return _MakePrimvars(
      prim.GetAuthoredPropertiesInNamespace(UsdGeomPrimvar::_GetNamespacePrefix()),
      [](UsdGeomPrimvar const &) { return true; });
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::GetPrimvarsWithValues() const
{
  TRACE_FUNCTION();
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("Called GetPrimvarsWithValues on invalid prim: %s", UsdDescribe(prim).c_str());
    return std::vector<UsdGeomPrimvar>();
  }
  return _MakePrimvars(
      prim.GetAuthoredPropertiesInNamespace(UsdGeomPrimvar::_GetNamespacePrefix()),
      [](UsdGeomPrimvar const &pv) { return pv.HasValue(); });
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::GetPrimvarsWithAuthoredValues() const
{
  TRACE_FUNCTION();
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("Called GetPrimvarsWithAuthoredValues on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return std::vector<UsdGeomPrimvar>();
  }
  return _MakePrimvars(
      prim.GetAuthoredPropertiesInNamespace(UsdGeomPrimvar::_GetNamespacePrefix()),
      [](UsdGeomPrimvar const &pv) { return pv.HasAuthoredValue(); });
}

static void _AddPrimToInheritedPrimvars(const UsdPrim &prim,
                                        const TfToken &pvPrefix,
                                        const std::vector<UsdGeomPrimvar> *inputPrimvars,
                                        std::vector<UsdGeomPrimvar> *outputPrimvars,
                                        bool acceptAll)
{
  auto copyPrimvars = [&inputPrimvars, &outputPrimvars]() {
    if (inputPrimvars != outputPrimvars) {
      *outputPrimvars = *inputPrimvars;
      inputPrimvars = outputPrimvars;
    }
  };

  for (UsdProperty const &prop : prim.GetAuthoredPropertiesInNamespace(pvPrefix)) {
    if (UsdGeomPrimvar pv = UsdGeomPrimvar(prop.As<UsdAttribute>())) {
      // If the primvar does not provide a value, then it is as if it
      // does not exist on prim
      if (!pv.HasAuthoredValue()) {
        continue;
      }

      // If pv is constant it will replace an instance already on the list;
      // if non-constant we'll just remove it.
      const TfToken &name = pv.GetName();
      size_t i;
      bool pvIsConstant = pv.GetInterpolation() == UsdGeomTokens->constant;
      bool foundMatch = false;
      for (i = 0; i < inputPrimvars->size(); ++i) {
        if (name == (*inputPrimvars)[i].GetName()) {
          copyPrimvars();
          foundMatch = true;
          if (pvIsConstant || acceptAll) {
            (*outputPrimvars)[i] = std::move(pv);
            break;
          }
          else {
            // Swap to the end and truncate the vector.
            // Don't bother to preserve order.
            std::swap((*outputPrimvars)[i], outputPrimvars->back());
            outputPrimvars->pop_back();
            break;
          }
        }
      }
      if (!foundMatch && (pvIsConstant || acceptAll)) {
        copyPrimvars();
        outputPrimvars->push_back(std::move(pv));
      }
    }
  }
}

static void _RecurseForInheritablePrimvars(const UsdPrim &prim,
                                           const TfToken &pvPrefix,
                                           std::vector<UsdGeomPrimvar> *primvars,
                                           bool acceptAll = false)
{
  if (prim.IsPseudoRoot())
    return;

  // The `acceptAll` override is only useful for the prim we are actually
  // querying, i.e. the *first* prim on which this function is called
  _RecurseForInheritablePrimvars(prim.GetParent(), pvPrefix, primvars);
  _AddPrimToInheritedPrimvars(prim, pvPrefix, primvars, primvars, acceptAll);
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::FindInheritablePrimvars() const
{
  TRACE_FUNCTION();
  // Assume the number of primvars is relatively bounded and
  // just use a vector to accumulate primvars up to the root prim.
  std::vector<UsdGeomPrimvar> primvars;
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindInheritablePrimvars called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return primvars;
  }

  TfToken const &prefix = UsdGeomPrimvar::_GetNamespacePrefix();
  _RecurseForInheritablePrimvars(prim, prefix, &primvars);

  return primvars;
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::FindIncrementallyInheritablePrimvars(
    const std::vector<UsdGeomPrimvar> &inheritedFromAncestors) const
{
  TRACE_FUNCTION();

  std::vector<UsdGeomPrimvar> primvars;
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindIncrementallyInheritablePrimvars called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return primvars;
  }

  TfToken const &prefix = UsdGeomPrimvar::_GetNamespacePrefix();
  _AddPrimToInheritedPrimvars(
      prim, prefix, &inheritedFromAncestors, &primvars, /* acceptAll = */ false);
  return primvars;
}

UsdGeomPrimvar UsdGeomPrimvarsAPI::FindPrimvarWithInheritance(const TfToken &name) const
{
  TRACE_FUNCTION();

  const TfToken attrName = UsdGeomPrimvar::_MakeNamespaced(name);
  UsdPrim prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindPrimvarWithInheritance called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return UsdGeomPrimvar();
  }
  UsdGeomPrimvar localPv = GetPrimvar(name);
  if (localPv.HasAuthoredValue()) {
    return localPv;
  }

  for (prim = prim.GetParent(); prim && !prim.IsPseudoRoot(); prim = prim.GetParent()) {
    UsdAttribute attr = prim.GetAttribute(attrName);
    if (attr.HasAuthoredValue()) {
      if (UsdGeomPrimvar pv = UsdGeomPrimvar(attr)) {
        // Only constant primvars can be inherited.
        if (pv.GetInterpolation() == UsdGeomTokens->constant) {
          return pv;
        }
        else {
          // Non-constant interpolation blocks inheritance.
          return UsdGeomPrimvar();
        }
      }
    }
  }
  return localPv;
}

UsdGeomPrimvar UsdGeomPrimvarsAPI::FindPrimvarWithInheritance(
    const TfToken &name, const std::vector<UsdGeomPrimvar> &inheritedFromAncestors) const
{
  TRACE_FUNCTION();

  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindPrimvarWithInheritance called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return UsdGeomPrimvar();
  }
  const TfToken attrName = UsdGeomPrimvar::_MakeNamespaced(name);
  UsdGeomPrimvar pv = GetPrimvar(attrName);
  if (pv.HasAuthoredValue()) {
    return pv;
  }

  for (UsdGeomPrimvar const &inherited : inheritedFromAncestors) {
    if (inherited.GetName() == attrName) {
      return inherited;
    }
  }

  return pv;
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::FindPrimvarsWithInheritance() const
{
  TRACE_FUNCTION();
  // Assume the number of primvars is relatively bounded and
  // just use a vector to accumulate primvars up to the root prim.
  std::vector<UsdGeomPrimvar> primvars;
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindPrimvarsWithINheritance called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return primvars;
  }

  TfToken const &prefix = UsdGeomPrimvar::_GetNamespacePrefix();
  _RecurseForInheritablePrimvars(prim,
                                 prefix,
                                 &primvars,
                                 /* acceptAll = */ true);

  return primvars;
}

std::vector<UsdGeomPrimvar> UsdGeomPrimvarsAPI::FindPrimvarsWithInheritance(
    const std::vector<UsdGeomPrimvar> &inheritedFromAncestors) const
{
  TRACE_FUNCTION();

  std::vector<UsdGeomPrimvar> primvars;
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("FindPrimvarsWithInheritance called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return primvars;
  }

  TfToken const &prefix = UsdGeomPrimvar::_GetNamespacePrefix();
  _AddPrimToInheritedPrimvars(prim,
                              prefix,
                              &inheritedFromAncestors,
                              &primvars,
                              /* acceptAll = */ true);

  // If this prim contributed no primvars, then `primvars` won't have
  // gotten a copy of `inheritedFromAncestors`, so ensure we compensate
  return primvars.empty() ? inheritedFromAncestors : primvars;
}

bool UsdGeomPrimvarsAPI::HasPrimvar(const TfToken &name) const
{
  TfToken primvarName = UsdGeomPrimvar::_MakeNamespaced(name, /* quiet */ true);
  const UsdPrim &prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("HasPrimvar called on invalid prim: %s", UsdDescribe(prim).c_str());
    return false;
  }
  return primvarName.IsEmpty() ? false : UsdGeomPrimvar::IsPrimvar(prim.GetAttribute(primvarName));
}

bool UsdGeomPrimvarsAPI::HasPossiblyInheritedPrimvar(const TfToken &name) const
{
  TRACE_FUNCTION();

  UsdPrim prim = GetPrim();
  if (!prim) {
    TF_CODING_ERROR("HasPossiblyInheritedPrimvar called on invalid prim: %s",
                    UsdDescribe(prim).c_str());
    return false;
  }
  UsdGeomPrimvar pv = GetPrimvar(name);
  if (pv.HasAuthoredValue()) {
    return true;
  }

  const TfToken attrName = UsdGeomPrimvar::_MakeNamespaced(name);
  if (attrName.IsEmpty()) {
    return false;
  }
  for (prim = prim.GetParent(); prim && !prim.IsPseudoRoot(); prim = prim.GetParent()) {
    UsdAttribute attr = prim.GetAttribute(attrName);
    if (attr.HasAuthoredValue() && UsdGeomPrimvar::IsPrimvar(attr)) {
      // Only constant primvars can be inherited.
      // Non-constant interpolation blocks inheritance.
      return UsdGeomPrimvar(attr).GetInterpolation() == UsdGeomTokens->constant;
    }
  }
  return false;
}

/* static */
bool UsdGeomPrimvarsAPI::CanContainPropertyName(const TfToken &name)
{
  TfToken const &prefix = UsdGeomPrimvar::_GetNamespacePrefix();
  return TfStringStartsWith(name, prefix);
}

PXR_NAMESPACE_CLOSE_SCOPE
