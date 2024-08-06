//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdLux/lightFilter.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdLuxLightFilter, TfType::Bases<UsdGeomXformable>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("LightFilter")
  // to find TfType<UsdLuxLightFilter>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdLuxLightFilter>("LightFilter");
}

/* virtual */
UsdLuxLightFilter::~UsdLuxLightFilter() {}

/* static */
UsdLuxLightFilter UsdLuxLightFilter::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxLightFilter();
  }
  return UsdLuxLightFilter(stage->GetPrimAtPath(path));
}

/* static */
UsdLuxLightFilter UsdLuxLightFilter::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("LightFilter");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxLightFilter();
  }
  return UsdLuxLightFilter(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdLuxLightFilter::_GetSchemaKind() const
{
  return UsdLuxLightFilter::schemaKind;
}

/* static */
const TfType &UsdLuxLightFilter::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdLuxLightFilter>();
  return tfType;
}

/* static */
bool UsdLuxLightFilter::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdLuxLightFilter::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdLuxLightFilter::GetShaderIdAttr() const
{
  return GetPrim().GetAttribute(UsdLuxTokens->lightFilterShaderId);
}

UsdAttribute UsdLuxLightFilter::CreateShaderIdAttr(VtValue const &defaultValue,
                                                   bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdLuxTokens->lightFilterShaderId,
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

namespace {
static inline TfTokenVector _ConcatenateAttributeNames(const TfTokenVector &left,
                                                       const TfTokenVector &right)
{
  TfTokenVector result;
  result.reserve(left.size() + right.size());
  result.insert(result.end(), left.begin(), left.end());
  result.insert(result.end(), right.begin(), right.end());
  return result;
}
}  // namespace

/*static*/
const TfTokenVector &UsdLuxLightFilter::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdLuxTokens->lightFilterShaderId,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdGeomXformable::GetSchemaAttributeNames(true), localNames);

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

#include "UsdShade/connectableAPI.h"
#include "UsdShade/connectableAPIBehavior.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdLuxLightFilter_ConnectableAPIBehavior : public UsdShadeConnectableAPIBehavior {
 public:
  // By default all UsdLuxLightFilter connectable behavior should be container
  // and we expect to make light filters be connected across multiple light
  // scopes, hence ignoring encapsulation rules.
  UsdLuxLightFilter_ConnectableAPIBehavior()
      : UsdShadeConnectableAPIBehavior(true /*isContainer*/, false /*requiresEncapsulation*/)
  {
  }

  bool CanConnectInputToSource(const UsdShadeInput &input,
                               const UsdAttribute &source,
                               std::string *reason) const override
  {
    return _CanConnectInputToSource(
        input, source, reason, ConnectableNodeTypes::DerivedContainerNodes);
  }

  // Note that LightFilter's outputs are not connectable (different from
  // UsdShadeNodeGraph default behavior) as there are no known use-case for
  // these right now.
  bool CanConnectOutputToSource(const UsdShadeOutput &output,
                                const UsdAttribute &source,
                                std::string *reason) const override
  {
    return false;
  }
};

TF_REGISTRY_FUNCTION(UsdShadeConnectableAPI)
{
  // UsdLuxLightFilter prims are connectable, with special behavior requiring
  // connection source to be encapsulated under the light.
  UsdShadeRegisterConnectableAPIBehavior<UsdLuxLightFilter,
                                         UsdLuxLightFilter_ConnectableAPIBehavior>();
}

UsdLuxLightFilter::UsdLuxLightFilter(const UsdShadeConnectableAPI &connectable)
    : UsdLuxLightFilter(connectable.GetPrim())
{
}

UsdShadeConnectableAPI UsdLuxLightFilter::ConnectableAPI() const
{
  return UsdShadeConnectableAPI(GetPrim());
}

UsdShadeOutput UsdLuxLightFilter::CreateOutput(const TfToken &name,
                                               const SdfValueTypeName &typeName)
{
  return UsdShadeConnectableAPI(GetPrim()).CreateOutput(name, typeName);
}

UsdShadeOutput UsdLuxLightFilter::GetOutput(const TfToken &name) const
{
  return UsdShadeConnectableAPI(GetPrim()).GetOutput(name);
}

std::vector<UsdShadeOutput> UsdLuxLightFilter::GetOutputs(bool onlyAuthored) const
{
  return UsdShadeConnectableAPI(GetPrim()).GetOutputs(onlyAuthored);
}

UsdShadeInput UsdLuxLightFilter::CreateInput(const TfToken &name, const SdfValueTypeName &typeName)
{
  return UsdShadeConnectableAPI(GetPrim()).CreateInput(name, typeName);
}

UsdShadeInput UsdLuxLightFilter::GetInput(const TfToken &name) const
{
  return UsdShadeConnectableAPI(GetPrim()).GetInput(name);
}

std::vector<UsdShadeInput> UsdLuxLightFilter::GetInputs(bool onlyAuthored) const
{
  return UsdShadeConnectableAPI(GetPrim()).GetInputs(onlyAuthored);
}

UsdCollectionAPI UsdLuxLightFilter::GetFilterLinkCollectionAPI() const
{
  return UsdCollectionAPI(GetPrim(), UsdLuxTokens->filterLink);
}

static TfToken _GetShaderIdAttrName(const TfToken &renderContext)
{
  if (renderContext.IsEmpty()) {
    return UsdLuxTokens->lightFilterShaderId;
  }
  return TfToken(SdfPath::JoinIdentifier(renderContext, UsdLuxTokens->lightFilterShaderId));
}

UsdAttribute UsdLuxLightFilter::GetShaderIdAttrForRenderContext(const TfToken &renderContext) const
{
  return GetPrim().GetAttribute(_GetShaderIdAttrName(renderContext));
}

UsdAttribute UsdLuxLightFilter::CreateShaderIdAttrForRenderContext(const TfToken &renderContext,
                                                                   VtValue const &defaultValue,
                                                                   bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(_GetShaderIdAttrName(renderContext),
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

TfToken UsdLuxLightFilter::GetShaderId(const TfTokenVector &renderContexts) const
{
  TfToken shaderId;
  // The passed in render contexts are in priority order so return the shader
  // ID from the first render context specific shaderId attribute that has a
  // a non-empty value.
  for (const TfToken &renderContext : renderContexts) {
    if (UsdAttribute shaderIdAttr = GetShaderIdAttrForRenderContext(renderContext)) {
      shaderIdAttr.Get(&shaderId);
      if (!shaderId.IsEmpty()) {
        return shaderId;
      }
    }
  }
  // Return the default shaderId attributes values if we couldn't get a value
  // for any of the render contexts.
  GetShaderIdAttr().Get(&shaderId);
  return shaderId;
}

PXR_NAMESPACE_CLOSE_SCOPE
