//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/attribute.h"
#include "Usd/primRange.h"
#include "Usd/property.h"
#include "Usd/relationship.h"
#include "Usd/stage.h"
#include "pxr/pxrns.h"

#include "Ar/resolverContext.h"

#include "Pcp/pyUtils.h"
#include "Sdf/pyUtils.h"
#include "Usd/pyConversions.h"

#include "Tf/makePyConstructor.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyEnum.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"
#include "Tf/weakPtr.h"

#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_OPEN_SCOPE

class Usd_PcpCacheAccess {
 public:
  static const PcpCache *GetPcpCache(const UsdStage &stage)
  {
    return stage._GetPcpCache();
  }
};

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static bool _Export(const UsdStagePtr &self,
                    const std::string &filename,
                    bool addSourceFileComment,
                    const boost::python::dict &dict)
{
  SdfLayer::FileFormatArguments args;
  std::string errMsg;
  if (!SdfFileFormatArgumentsFromPython(dict, &args, &errMsg)) {
    TF_CODING_ERROR("%s", errMsg.c_str());
    return false;
  }

  return self->Export(filename, addSourceFileComment, args);
}

static string _ExportToString(const UsdStagePtr &self, bool addSourceFileComment = true)
{
  string result;
  self->ExportToString(&result, addSourceFileComment);
  return result;
}

static string __repr__(const UsdStagePtr &self)
{
  if (self.IsExpired()) {
    return "invalid " + UsdDescribe(self);
  }

  string result = TF_PY_REPR_PREFIX + TfStringPrintf("Stage.Open(rootLayer=%s, sessionLayer=%s",
                                                     TfPyRepr(self->GetRootLayer()).c_str(),
                                                     TfPyRepr(self->GetSessionLayer()).c_str());

  if (!self->GetPathResolverContext().IsEmpty()) {
    result += TfStringPrintf(", pathResolverContext=%s",
                             TfPyRepr(self->GetPathResolverContext()).c_str());
  }

  return result + ")";
}

static TfPyObjWrapper _GetMetadata(const UsdStagePtr &self, const TfToken &key)
{
  VtValue result;
  self->GetMetadata(key, &result);
  // If the above failed, result will still be empty, which is
  // the appropriate return value
  return UsdVtValueToPython(result);
}

static bool _SetMetadata(const UsdStagePtr &self, const TfToken &key, object obj)
{
  VtValue value;
  return UsdPythonToMetadataValue(key, /*keyPath*/ TfToken(), obj, &value) &&
         self->SetMetadata(key, value);
}

static TfPyObjWrapper _GetMetadataByDictKey(const UsdStagePtr &self,
                                            const TfToken &key,
                                            const TfToken &keyPath)
{
  VtValue result;
  self->GetMetadataByDictKey(key, keyPath, &result);
  // If the above failed, result will still be empty, which is
  // the appropriate return value
  return UsdVtValueToPython(result);
}

static bool _SetMetadataByDictKey(const UsdStagePtr &self,
                                  const TfToken &key,
                                  const TfToken &keyPath,
                                  object obj)
{
  VtValue value;
  return UsdPythonToMetadataValue(key, keyPath, obj, &value) &&
         self->SetMetadataByDictKey(key, keyPath, value);
}

static void _SetGlobalVariantFallbacks(const dict &d)
{
  PcpVariantFallbackMap fallbacks;
  if (PcpVariantFallbackMapFromPython(d, &fallbacks)) {
    UsdStage::SetGlobalVariantFallbacks(fallbacks);
  }
}

static UsdEditTarget _GetEditTargetForLocalLayerIndex(const UsdStagePtr &self, size_t index)
{
  return self->GetEditTargetForLocalLayer(index);
}

static UsdEditTarget _GetEditTargetForLocalLayer(const UsdStagePtr &self,
                                                 const SdfLayerHandle &layer)
{
  return self->GetEditTargetForLocalLayer(layer);
}

static void _ExpandPopulationMask(UsdStage &self,
                                  Usd_PrimFlagsPredicate const &traversal,
                                  boost::python::object pyRelPred,
                                  boost::python::object pyAttrPred)
{
  using RelPredicate = std::function<bool(UsdRelationship const &)>;
  using AttrPredicate = std::function<bool(UsdAttribute const &)>;
  RelPredicate relPred;
  AttrPredicate attrPred;
  if (!pyRelPred.is_none()) {
    relPred = boost::python::extract<RelPredicate>(pyRelPred);
  }
  if (!pyAttrPred.is_none()) {
    attrPred = boost::python::extract<AttrPredicate>(pyAttrPred);
  }
  return self.ExpandPopulationMask(traversal, relPred, attrPred);
}

static void _ExpandPopulationMaskDefault(UsdStage &self,
                                         boost::python::object pyRelPred,
                                         boost::python::object pyAttrPred)
{
  return _ExpandPopulationMask(self, UsdPrimDefaultPredicate, pyRelPred, pyAttrPred);
}

static object _GetColorConfigFallbacks()
{
  SdfAssetPath colorConfiguration;
  TfToken colorManagementSystem;
  UsdStage::GetColorConfigFallbacks(&colorConfiguration, &colorManagementSystem);
  return boost::python::make_tuple(colorConfiguration, colorManagementSystem);
}

}  // anonymous namespace

void wrapUsdStage()
{
  typedef TfWeakPtr<UsdStage> StagePtr;

  class_<UsdStage, StagePtr, boost::noncopyable> cls("Stage", no_init);

  // Expose the UsdStage::InitialLoadSet enum under the Usd.Stage scope.
  // We need to do this here because we use enum values as default
  // parameters to other wrapped functions.
  scope s = cls;
  TfPyWrapEnum<UsdStage::InitialLoadSet>();

  cls.def(TfPyRefAndWeakPtr())
      .def("__repr__", __repr__)

      .def("CreateNew",
           (UsdStageRefPtr(*)(const string &, UsdStage::InitialLoadSet))&UsdStage::CreateNew,
           (arg("identifier"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateNew",
           (UsdStageRefPtr(*)(const string &,
                              const SdfLayerHandle &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateNew,
           (arg("identifier"),
            arg("sessionLayer"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateNew",
           (UsdStageRefPtr(*)(const string &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateNew,
           (arg("identifier"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateNew",
           (UsdStageRefPtr(*)(const string &,
                              const SdfLayerHandle &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateNew,
           (arg("identifier"),
            arg("sessionLayer"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .staticmethod("CreateNew")

      .def("CreateInMemory",
           (UsdStageRefPtr(*)(UsdStage::InitialLoadSet))&UsdStage::CreateInMemory,
           (arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateInMemory",
           (UsdStageRefPtr(*)(const string &, UsdStage::InitialLoadSet))&UsdStage::CreateInMemory,
           (arg("identifier"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateInMemory",
           (UsdStageRefPtr(*)(const string &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateInMemory,
           (arg("identifier"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateInMemory",
           (UsdStageRefPtr(*)(const string &,
                              const SdfLayerHandle &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateInMemory,
           (arg("identifier"),
            arg("sessionLayer"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("CreateInMemory",
           (UsdStageRefPtr(*)(const string &,
                              const SdfLayerHandle &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::CreateInMemory,
           (arg("identifier"),
            arg("sessionLayer"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .staticmethod("CreateInMemory")

      .def("Open",
           (UsdStageRefPtr(*)(const string &, UsdStage::InitialLoadSet))&UsdStage::Open,
           (arg("filePath"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("Open",
           (UsdStageRefPtr(*)(const string &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::Open,
           (arg("filePath"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())

      .def("Open",
           (UsdStageRefPtr(*)(const SdfLayerHandle &, UsdStage::InitialLoadSet))&UsdStage::Open,
           (arg("rootLayer"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def(
          "Open",
          (UsdStageRefPtr(*)(const SdfLayerHandle &,
                             const SdfLayerHandle &,
                             UsdStage::InitialLoadSet))&UsdStage::Open,
          (arg("rootLayer"), arg("sessionLayer"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
          return_value_policy<TfPyRefPtrFactory<>>())
      .def("Open",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::Open,
           (arg("rootLayer"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("Open",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const SdfLayerHandle &,
                              const ArResolverContext &,
                              UsdStage::InitialLoadSet))&UsdStage::Open,
           (arg("rootLayer"),
            arg("sessionLayer"),
            arg("pathResolverContext"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .staticmethod("Open")

      .def("OpenMasked",
           (UsdStageRefPtr(*)(const string &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("filePath"), arg("mask"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("OpenMasked",
           (UsdStageRefPtr(*)(const string &,
                              const ArResolverContext &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("filePath"),
            arg("pathResolverContext"),
            arg("mask"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("OpenMasked",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("rootLayer"), arg("mask"), arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("OpenMasked",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const SdfLayerHandle &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("rootLayer"),
            arg("sessionLayer"),
            arg("mask"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("OpenMasked",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const ArResolverContext &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("rootLayer"),
            arg("pathResolverContext"),
            arg("mask"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .def("OpenMasked",
           (UsdStageRefPtr(*)(const SdfLayerHandle &,
                              const SdfLayerHandle &,
                              const ArResolverContext &,
                              const UsdStagePopulationMask &,
                              UsdStage::InitialLoadSet))&UsdStage::OpenMasked,
           (arg("rootLayer"),
            arg("sessionLayer"),
            arg("pathResolverContext"),
            arg("mask"),
            arg("load") = UsdStage::InitialLoadSet::LoadAll),
           return_value_policy<TfPyRefPtrFactory<>>())
      .staticmethod("OpenMasked")

      .def("Reload", &UsdStage::Reload)

      .def("Save", &UsdStage::Save)
      .def("SaveSessionLayers", &UsdStage::SaveSessionLayers)
      .def("WriteFallbackPrimTypes", &UsdStage::WriteFallbackPrimTypes)

      .def("GetGlobalVariantFallbacks",
           &UsdStage::GetGlobalVariantFallbacks,
           return_value_policy<TfPyMapToDictionary>())
      .staticmethod("GetGlobalVariantFallbacks")
      .def("SetGlobalVariantFallbacks", &_SetGlobalVariantFallbacks)
      .staticmethod("SetGlobalVariantFallbacks")

      .def("Load",
           &UsdStage::Load,
           (arg("path") = SdfPath::AbsoluteRootPath(),
            arg("policy") = UsdLoadPolicy::UsdLoadPolicyWithDescendants))

      .def("Unload", &UsdStage::Unload, arg("path") = SdfPath::AbsoluteRootPath())

      .def("LoadAndUnload",
           &UsdStage::LoadAndUnload,
           (arg("loadSet"),
            arg("unloadSet"),
            arg("policy") = UsdLoadPolicy::UsdLoadPolicyWithDescendants))

      .def("GetLoadSet", &UsdStage::GetLoadSet, return_value_policy<TfPySequenceToList>())

      .def("FindLoadable",
           &UsdStage::FindLoadable,
           arg("rootPath") = SdfPath::AbsoluteRootPath(),
           return_value_policy<TfPySequenceToList>())

      .def("GetLoadRules", &UsdStage::GetLoadRules, return_value_policy<return_by_value>())
      .def("SetLoadRules", &UsdStage::SetLoadRules, arg("rules"))

      .def("GetPopulationMask", &UsdStage::GetPopulationMask)
      .def("SetPopulationMask", &UsdStage::SetPopulationMask, arg("mask"))
      .def("ExpandPopulationMask",
           &_ExpandPopulationMaskDefault,
           (arg("relationshipPredicate") = object(), arg("attributePredicate") = object()))
      .def("ExpandPopulationMask",
           &_ExpandPopulationMask,
           (arg("traversalPredicate"),
            arg("relationshipPredicate") = object(),
            arg("attributePredicate") = object()))

      .def("GetPseudoRoot", &UsdStage::GetPseudoRoot)

      .def("GetDefaultPrim", &UsdStage::GetDefaultPrim)
      .def("SetDefaultPrim", &UsdStage::SetDefaultPrim, arg("prim"))
      .def("ClearDefaultPrim", &UsdStage::ClearDefaultPrim)
      .def("HasDefaultPrim", &UsdStage::HasDefaultPrim)

      .def("GetPrimAtPath", &UsdStage::GetPrimAtPath, arg("path"))
      .def("GetObjectAtPath", &UsdStage::GetObjectAtPath, arg("path"))
      .def("GetPropertyAtPath", &UsdStage::GetPropertyAtPath, arg("path"))
      .def("GetAttributeAtPath", &UsdStage::GetAttributeAtPath, arg("path"))
      .def("GetRelationshipAtPath", &UsdStage::GetRelationshipAtPath, arg("path"))
      .def("Traverse", (UsdPrimRange(UsdStage::*)())&UsdStage::Traverse)
      .def("Traverse",
           (UsdPrimRange(UsdStage::*)(const Usd_PrimFlagsPredicate &))&UsdStage::Traverse,
           arg("predicate"))
      .def("TraverseAll", &UsdStage::TraverseAll)

      .def("OverridePrim", &UsdStage::OverridePrim, arg("path"))
      .def("DefinePrim", &UsdStage::DefinePrim, (arg("path"), arg("typeName") = TfToken()))
      .def("CreateClassPrim", &UsdStage::CreateClassPrim, arg("rootPrimPath"))

      .def("RemovePrim", &UsdStage::RemovePrim, arg("path"))

      .def("GetSessionLayer", &UsdStage::GetSessionLayer)
      .def("GetRootLayer", &UsdStage::GetRootLayer)
      .def("GetPathResolverContext", &UsdStage::GetPathResolverContext)
      .def("ResolveIdentifierToEditTarget",
           &UsdStage::ResolveIdentifierToEditTarget,
           arg("identifier"))
      .def("GetCompositionErrors",
           &UsdStage::GetCompositionErrors,
           return_value_policy<TfPySequenceToList>())
      .def("GetLayerStack",
           &UsdStage::GetLayerStack,
           arg("includeSessionLayers") = true,
           return_value_policy<TfPySequenceToList>())
      .def("GetUsedLayers",
           &UsdStage::GetUsedLayers,
           arg("includeClipLayers") = true,
           return_value_policy<TfPySequenceToList>())

      .def("HasLocalLayer", &UsdStage::HasLocalLayer, arg("layer"))

      .def("GetEditTarget", &UsdStage::GetEditTarget, return_value_policy<return_by_value>())
      .def("GetEditTargetForLocalLayer",
           &_GetEditTargetForLocalLayerIndex,
           return_value_policy<return_by_value>())
      .def("GetEditTargetForLocalLayer",
           &_GetEditTargetForLocalLayer,
           return_value_policy<return_by_value>())
      .def("SetEditTarget", &UsdStage::SetEditTarget, arg("editTarget"))

      .def("MuteLayer", &UsdStage::MuteLayer, (arg("layerIdentifier")))
      .def("UnmuteLayer", &UsdStage::UnmuteLayer, (arg("layerIdentifier")))
      .def("MuteAndUnmuteLayers",
           &UsdStage::MuteAndUnmuteLayers,
           (arg("muteLayers"), arg("unmuteLayers")))
      .def("GetMutedLayers", &UsdStage::GetMutedLayers, return_value_policy<TfPySequenceToList>())
      .def("IsLayerMuted", &UsdStage::IsLayerMuted, (arg("layerIdentifier")))

      .def("Export",
           &_Export,
           (arg("filename"),
            arg("addSourceFileComment") = true,
            arg("args") = boost::python::dict()))

      .def("ExportToString", _ExportToString, arg("addSourceFileComment") = true)

      .def("Flatten",
           &UsdStage::Flatten,
           (arg("addSourceFileComment") = true),
           return_value_policy<TfPyRefPtrFactory<SdfLayerHandle>>())

      .def("GetMetadata", &_GetMetadata)
      .def("HasMetadata", &UsdStage::HasMetadata)
      .def("HasAuthoredMetadata", &UsdStage::HasAuthoredMetadata)
      .def("ClearMetadata", &UsdStage::ClearMetadata)
      .def("SetMetadata", &_SetMetadata)

      .def("GetMetadataByDictKey", &_GetMetadataByDictKey)
      .def("HasMetadataDictKey", &UsdStage::HasMetadataDictKey)
      .def("HasAuthoredMetadataDictKey", &UsdStage::HasAuthoredMetadataDictKey)
      .def("ClearMetadataByDictKey", &UsdStage::ClearMetadataByDictKey)
      .def("SetMetadataByDictKey", &_SetMetadataByDictKey)

      .def("GetStartTimeCode", &UsdStage::GetStartTimeCode)
      .def("SetStartTimeCode", &UsdStage::SetStartTimeCode)

      .def("GetEndTimeCode", &UsdStage::GetEndTimeCode)
      .def("SetEndTimeCode", &UsdStage::SetEndTimeCode)

      .def("HasAuthoredTimeCodeRange", &UsdStage::HasAuthoredTimeCodeRange)

      .def("GetTimeCodesPerSecond", &UsdStage::GetTimeCodesPerSecond)
      .def("SetTimeCodesPerSecond", &UsdStage::SetTimeCodesPerSecond)

      .def("GetFramesPerSecond", &UsdStage::GetFramesPerSecond)
      .def("SetFramesPerSecond", &UsdStage::SetFramesPerSecond)

      .def("GetColorConfiguration", &UsdStage::GetColorConfiguration)
      .def("SetColorConfiguration", &UsdStage::SetColorConfiguration)

      .def("GetColorManagementSystem", &UsdStage::GetColorManagementSystem)
      .def("SetColorManagementSystem", &UsdStage::SetColorManagementSystem)

      .def("GetColorConfigFallbacks", &_GetColorConfigFallbacks)
      .staticmethod("GetColorConfigFallbacks")

      .def("SetColorConfigFallbacks",
           &UsdStage::SetColorConfigFallbacks,
           (arg("colorConfiguration") = SdfAssetPath(), arg("colorManagementSystem") = TfToken()))
      .staticmethod("SetColorConfigFallbacks")

      .def("GetInterpolationType", &UsdStage::GetInterpolationType)
      .def("SetInterpolationType", &UsdStage::SetInterpolationType)
      .def("IsSupportedFile", &UsdStage::IsSupportedFile, arg("filePath"))
      .staticmethod("IsSupportedFile")

      .def("GetPrototypes", &UsdStage::GetPrototypes, return_value_policy<TfPySequenceToList>())

      .def("_GetPcpCache", &Usd_PcpCacheAccess::GetPcpCache, return_internal_reference<>());
}
