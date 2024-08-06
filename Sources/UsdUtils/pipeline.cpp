//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdUtils/pipeline.h"
#include "pxr/pxrns.h"

#include "Plug/plugin.h"
#include "Plug/registry.h"
#include "Sdf/layer.h"
#include "Sdf/path.h"
#include "Sdf/primSpec.h"
#include "Tf/diagnostic.h"
#include "Tf/envSetting.h"
#include "Tf/hashmap.h"
#include "Tf/staticTokens.h"
#include "Tf/stl.h"
#include "Tf/stringUtils.h"
#include "Tf/token.h"
#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdGeom/metrics.h"
#include "UsdGeom/tokens.h"

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(USD_FORCE_DEFAULT_MATERIALS_SCOPE_NAME,
                      false,
                      "Disables the ability to configure the materials scope name with a "
                      "plugInfo.json value and forces the use of the built-in default instead. "
                      "This is primarily used for unit testing purposes as a way to ignore any "
                      "site-based configuration.");

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,

    (UsdUtilsPipeline)(MaterialsScopeName)(PrimaryCameraName)(ProvidesRegisteredVariantSetsFromPlugin)(RegisteredVariantSets)(selectionExportPolicy)

        ((DefaultMaterialsScopeName, "Looks"))((DefaultPrimaryCameraName, "main_cam"))

            (pref)(st));

TfToken UsdUtilsGetAlphaAttributeNameForColor(TfToken const &colorAttrName)
{
  return TfToken(colorAttrName.GetString() + std::string("_A"));
}

TfToken UsdUtilsGetModelNameFromRootLayer(const SdfLayerHandle &rootLayer)
{
  // First check if if we have the metadata.
  TfToken modelName = rootLayer->GetDefaultPrim();
  if (!modelName.IsEmpty()) {
    return modelName;
  }

  // If no default prim, see if there is a prim w/ the same "name" as the
  // file.  "name" here means the string before the first ".".
  const std::string &filePath = rootLayer->GetRealPath();
  std::string baseName = TfGetBaseName(filePath);
  modelName = TfToken(baseName.substr(0, baseName.find('.')));

  if (!modelName.IsEmpty() && SdfPath::IsValidIdentifier(modelName) &&
      rootLayer->GetPrimAtPath(SdfPath::AbsoluteRootPath().AppendChild(modelName)))
  {
    return modelName;
  }

  // Otherwise, fallback to getting the first non-class child in the layer.
  TF_FOR_ALL(rootChildrenIter, rootLayer->GetRootPrims())
  {
    const SdfPrimSpecHandle &rootPrim = *rootChildrenIter;
    if (rootPrim->GetSpecifier() != SdfSpecifierClass) {
      return rootPrim->GetNameToken();
    }
  }

  return modelName;
}

TF_MAKE_STATIC_DATA(std::set<UsdUtilsRegisteredVariantSet>, _regVarSets) {}

static void _RegisterVariantSetsFromPlugInfos()
{
  for (PlugPluginPtr plug : PlugRegistry::GetInstance().GetAllPlugins()) {
    JsObject metadata = plug->GetMetadata();
    JsValue pipelineUtilsDictValue;
    if (TfMapLookup(metadata, _tokens->UsdUtilsPipeline, &pipelineUtilsDictValue)) {
      if (!pipelineUtilsDictValue.Is<JsObject>()) {
        TF_CODING_ERROR("%s[UsdUtilsPipeline] was not a dictionary.", plug->GetName().c_str());
        continue;
      }

      JsObject pipelineUtilsDict = pipelineUtilsDictValue.Get<JsObject>();

      JsValue registeredVariantSetsValue;
      if (TfMapLookup(
              pipelineUtilsDict, _tokens->RegisteredVariantSets, &registeredVariantSetsValue))
      {
        if (!registeredVariantSetsValue.IsObject()) {
          TF_CODING_ERROR("%s[UsdUtilsPipeline][RegisteredVariantSets] was not a dictionary.",
                          plug->GetName().c_str());
          continue;
        }

        const JsObject &registeredVariantSets = registeredVariantSetsValue.GetJsObject();
        for (const auto &i : registeredVariantSets) {
          const std::string &variantSetName = i.first;
          const JsValue &v = i.second;
          if (!v.IsObject()) {
            TF_CODING_ERROR(
                "%s[UsdUtilsPipeline][RegisteredVariantSets][%s] was not a dictionary.",
                plug->GetName().c_str(),
                variantSetName.c_str());
            continue;
          }

          JsObject info = v.GetJsObject();
          std::string variantSetType = info[_tokens->selectionExportPolicy].GetString();

          UsdUtilsRegisteredVariantSet::SelectionExportPolicy selectionExportPolicy;
          if (!UsdUtilsRegisteredVariantSet::GetSelectionExportPolicyFromString(
                  variantSetType, &selectionExportPolicy))
          {
            TF_CODING_ERROR("%s[UsdUtilsPipeline][RegisteredVariantSets][%s] was not valid.",
                            plug->GetName().c_str(),
                            variantSetName.c_str());
            continue;
          }
          UsdUtilsRegisterVariantSet(variantSetName, selectionExportPolicy);
        }
      }
    }
  }
}

static void _LoadPluginsThatRegisterVariantSets()
{
  for (PlugPluginPtr plug : PlugRegistry::GetInstance().GetAllPlugins()) {
    JsObject metadata = plug->GetMetadata();
    JsValue pipelineUtilsDictValue;
    if (TfMapLookup(metadata, _tokens->UsdUtilsPipeline, &pipelineUtilsDictValue)) {
      if (!pipelineUtilsDictValue.Is<JsObject>()) {
        TF_CODING_ERROR("%s[UsdUtilsPipeline] was not a dictionary.", plug->GetName().c_str());
        continue;
      }

      JsObject pipelineUtilsDict = pipelineUtilsDictValue.Get<JsObject>();
      JsValue registersVariantSets;
      if (TfMapLookup(pipelineUtilsDict,
                      _tokens->ProvidesRegisteredVariantSetsFromPlugin,
                      &registersVariantSets))
      {
        if (!registersVariantSets.IsBool()) {
          TF_CODING_ERROR(
              "%s[UsdUtilsPipeline][ProvidesRegisteredVariantSetsFromPlugin] was not a bool.",
              plug->GetName().c_str());
        }

        if (registersVariantSets.GetBool()) {
          plug->Load();
        }
      }
    }
  }
}

const std::set<UsdUtilsRegisteredVariantSet> &UsdUtilsGetRegisteredVariantSets()
{
  // Lazy population on first use.
  static std::once_flag _flag;
  std::call_once(_flag, []() {
    // First, we'll populate from any plugInfos that provide this information.
    _RegisterVariantSetsFromPlugInfos();

    // Now, we load any plugins that may want register variantSets as well.
    _LoadPluginsThatRegisterVariantSets();

    // Invoke any code for UsdUtilsRegisteredVariantSet.
    TfRegistryManager::GetInstance().SubscribeTo<UsdUtilsRegisteredVariantSet>();
  });

  return *_regVarSets;
}

void UsdUtilsRegisterVariantSet(
    const std::string &variantSetName,
    const UsdUtilsRegisteredVariantSet::SelectionExportPolicy &selectionExportPolicy)
{
  _regVarSets->emplace(variantSetName, selectionExportPolicy);
}

UsdPrim UsdUtilsGetPrimAtPathWithForwarding(const UsdStagePtr &stage, const SdfPath &path)
{
  // If the given path refers to a prim beneath an instance,
  // UsdStage::GetPrimAtPath will return an instance proxy
  // from which we can retrieve the corresponding prim in
  // the prototype.
  UsdPrim p = stage->GetPrimAtPath(path);
  return (p && p.IsInstanceProxy()) ? p.GetPrimInPrototype() : p;
}

UsdPrim UsdUtilsUninstancePrimAtPath(const UsdStagePtr &stage, const SdfPath &path)
{
  // If a valid prim exists at the requested path, simply return it.
  // If the prim is an instance proxy, it means this path indicates
  // a prim beneath an instance. In order to uninstance it, we need
  // to uninstance all ancestral instances.
  UsdPrim p = stage->GetPrimAtPath(path);
  if (!p || !p.IsInstanceProxy()) {
    return p;
  }

  // Skip the last element in prefixes, since that's our own
  // path and we only want to uninstance ancestors.
  SdfPathVector prefixes = path.GetPrefixes();
  if (!prefixes.empty()) {
    prefixes.pop_back();
  }

  for (const SdfPath &prefixPath : prefixes) {
    UsdPrim prim = stage->GetPrimAtPath(prefixPath);
    if (!prim) {
      break;
    }

    if (prim.IsInstance()) {
      prim.SetInstanceable(false);
    }
  }

  // Uninstancing should ensure that the prim at the given
  // path, if it exists, is no longer inside an instance.
  p = stage->GetPrimAtPath(path);
  TF_VERIFY(!p || !p.IsInstanceProxy());
  return p;
}

const TfToken &UsdUtilsGetPrimaryUVSetName()
{
  return _tokens->st;
}

const TfToken &UsdUtilsGetPrefName()
{
  return _tokens->pref;
}

using _TokenToTokenMap = TfHashMap<TfToken, TfToken, TfToken::HashFunctor>;

/// Looks through the metadata dictionaries of all registered plugins for
/// string values that match the key path:
///     [UsdUtilsPipeline][<identifierKey>]
///
/// A string value will be looked up for each of the tokens in identifierKeys.
///
/// The first valid string value identifier found for each identifierKey, if
/// any, is inserted into the returned map.
static _TokenToTokenMap _GetPipelineIdentifierTokens(const TfTokenVector &identifierKeys)
{
  const TfToken metadataDictKey = _tokens->UsdUtilsPipeline;

  _TokenToTokenMap identifierMap;

  const PlugPluginPtrVector plugs = PlugRegistry::GetInstance().GetAllPlugins();
  for (const PlugPluginPtr &plug : plugs) {
    JsObject metadata = plug->GetMetadata();
    JsValue metadataDictValue;
    if (!TfMapLookup(metadata, metadataDictKey, &metadataDictValue)) {
      continue;
    }

    if (!metadataDictValue.Is<JsObject>()) {
      TF_CODING_ERROR(
          "%s[%s] was not a dictionary.", plug->GetName().c_str(), metadataDictKey.GetText());
      continue;
    }

    JsObject metadataDict = metadataDictValue.Get<JsObject>();

    for (const TfToken &identifierKey : identifierKeys) {
      JsValue stringJsValue;
      if (!TfMapLookup(metadataDict, identifierKey, &stringJsValue)) {
        continue;
      }

      if (!stringJsValue.IsString()) {
        TF_CODING_ERROR("%s[%s][%s] was not a string.",
                        plug->GetName().c_str(),
                        metadataDictKey.GetText(),
                        identifierKey.GetText());
        continue;
      }

      const std::string valueString = stringJsValue.GetString();
      if (!SdfPath::IsValidIdentifier(valueString)) {
        TF_CODING_ERROR("%s[%s][%s] was not a valid identifier: \"%s\".",
                        plug->GetName().c_str(),
                        metadataDictKey.GetText(),
                        identifierKey.GetText(),
                        valueString.c_str());
        continue;
      }

      identifierMap.insert({identifierKey, TfToken(valueString)});
    }

    if (identifierMap.size() == identifierKeys.size()) {
      // We got an identifier for all of the given keys, so stop looking
      // through plugin metadata.
      break;
    }
  }

  return identifierMap;
}

TF_MAKE_STATIC_DATA(_TokenToTokenMap, _pipelineIdentifiersMap)
{
  const TfTokenVector identifierKeys({_tokens->MaterialsScopeName, _tokens->PrimaryCameraName});

  *_pipelineIdentifiersMap = _GetPipelineIdentifierTokens(identifierKeys);
}

TfToken UsdUtilsGetMaterialsScopeName(const bool forceDefault)
{
  if (TfGetEnvSetting(USD_FORCE_DEFAULT_MATERIALS_SCOPE_NAME) || forceDefault) {
    return _tokens->DefaultMaterialsScopeName;
  }

  return TfMapLookupByValue(
      *_pipelineIdentifiersMap, _tokens->MaterialsScopeName, _tokens->DefaultMaterialsScopeName);
}

TfToken UsdUtilsGetPrimaryCameraName(const bool forceDefault)
{
  if (forceDefault) {
    return _tokens->DefaultPrimaryCameraName;
  }

  return TfMapLookupByValue(
      *_pipelineIdentifiersMap, _tokens->PrimaryCameraName, _tokens->DefaultPrimaryCameraName);
}

PXR_NAMESPACE_CLOSE_SCOPE
