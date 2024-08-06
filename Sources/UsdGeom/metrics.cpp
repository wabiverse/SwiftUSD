//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/metrics.h"
#include "UsdGeom/tokens.h"
#include "pxr/pxrns.h"

#include "Sdf/schema.h"
#include "Usd/stage.h"

#include "Plug/plugin.h"
#include "Plug/registry.h"

#include "Tf/diagnostic.h"
#include "Tf/envSetting.h"
#include "Tf/staticData.h"
#include "Tf/staticTokens.h"
#include "Tf/token.h"

#include <cfloat>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens, (UsdGeomMetrics));

TfToken UsdGeomGetStageUpAxis(const UsdStageWeakPtr &stage)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid UsdStage");
    return TfToken();
  }

  // Even after we remove backwards compatibility support, we will still
  // need to know if upAxis has been authored, since we want to provide
  // a potentially different fallback than that of the SdfSchema.
  if (stage->HasAuthoredMetadata(UsdGeomTokens->upAxis)) {
    TfToken axis;
    stage->GetMetadata(UsdGeomTokens->upAxis, &axis);
    return axis;
  }

  return UsdGeomGetFallbackUpAxis();
}

bool UsdGeomSetStageUpAxis(const UsdStageWeakPtr &stage, const TfToken &axis)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid UsdStage");
    return false;
  }

  if (axis != UsdGeomTokens->y && axis != UsdGeomTokens->z) {
    TF_CODING_ERROR(
        "UsdStage upAxis can only be set to \"Y\" or \"Z\", "
        "not attempted \"%s\" on stage %s.",
        axis.GetText(),
        stage->GetRootLayer()->GetIdentifier().c_str());
    return false;
  }

  return stage->SetMetadata(UsdGeomTokens->upAxis, VtValue(axis));
}

TF_MAKE_STATIC_DATA(TfToken, _fallbackUpAxis)
{
  TfToken upAxis;
  std::string definingPluginName;
  TfToken schemaFallback =
      SdfSchema::GetInstance().GetFallback(UsdGeomTokens->upAxis).Get<TfToken>();

  PlugPluginPtrVector plugs = PlugRegistry::GetInstance().GetAllPlugins();
  TF_FOR_ALL(plugIter, plugs)
  {
    PlugPluginPtr plug = *plugIter;
    JsObject metadata = plug->GetMetadata();
    JsValue metricsDictValue;
    if (TfMapLookup(metadata, _tokens->UsdGeomMetrics, &metricsDictValue)) {
      if (!metricsDictValue.Is<JsObject>()) {
        TF_CODING_ERROR("%s[%s] was not a dictionary in plugInfo.json file.",
                        plug->GetName().c_str(),
                        _tokens->UsdGeomMetrics.GetText());
        continue;
      }

      JsObject metricsDict = metricsDictValue.Get<JsObject>();
      JsValue upAxisValue;
      if (TfMapLookup(metricsDict, UsdGeomTokens->upAxis, &upAxisValue)) {
        if (!upAxisValue.Is<std::string>()) {
          TF_CODING_ERROR("%s[%s][%s] was not a string.",
                          plug->GetName().c_str(),
                          _tokens->UsdGeomMetrics.GetText(),
                          UsdGeomTokens->upAxis.GetText());
          continue;
        }

        std::string axisStr = upAxisValue.Get<std::string>();
        TfToken axisToken;
        if (axisStr == "Y") {
          axisToken = UsdGeomTokens->y;
        }
        else if (axisStr == "Z") {
          axisToken = UsdGeomTokens->z;
        }
        else {
          TF_CODING_ERROR(
              "%s[%s][%s] had value \"%s\", but only \"Y\" and"
              " \"Z\" are allowed.",
              plug->GetName().c_str(),
              _tokens->UsdGeomMetrics.GetText(),
              UsdGeomTokens->upAxis.GetText(),
              axisStr.c_str());
          continue;
        }

        if (!upAxis.IsEmpty() && upAxis != axisToken) {
          TF_CODING_ERROR(
              "Plugins %s and %s provided different"
              " fallback values for %s.  Ignoring all"
              " plugins and using schema fallback of"
              " \"%s\"",
              definingPluginName.c_str(),
              plug->GetName().c_str(),
              UsdGeomTokens->upAxis.GetText(),
              schemaFallback.GetText());
          *_fallbackUpAxis = schemaFallback;
          return;
        }
        else if (upAxis.IsEmpty()) {
          definingPluginName = plug->GetName();
          upAxis = axisToken;
        }
      }
    }
  }

  *_fallbackUpAxis = upAxis.IsEmpty() ? schemaFallback : upAxis;
}

TfToken UsdGeomGetFallbackUpAxis()
{
  return *_fallbackUpAxis;
}

constexpr double UsdGeomLinearUnits::nanometers;
constexpr double UsdGeomLinearUnits::micrometers;
constexpr double UsdGeomLinearUnits::millimeters;
constexpr double UsdGeomLinearUnits::centimeters;
constexpr double UsdGeomLinearUnits::meters;
constexpr double UsdGeomLinearUnits::kilometers;
constexpr double UsdGeomLinearUnits::lightYears;
constexpr double UsdGeomLinearUnits::inches;
constexpr double UsdGeomLinearUnits::feet;
constexpr double UsdGeomLinearUnits::yards;
constexpr double UsdGeomLinearUnits::miles;

double UsdGeomGetStageMetersPerUnit(const UsdStageWeakPtr &stage)
{
  double units = UsdGeomLinearUnits::centimeters;
  if (!stage) {
    TF_CODING_ERROR("Invalid UsdStage");
    return units;
  }

  stage->GetMetadata(UsdGeomTokens->metersPerUnit, &units);
  return units;
}

bool UsdGeomStageHasAuthoredMetersPerUnit(const UsdStageWeakPtr &stage)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid UsdStage");
    return false;
  }
  return stage->HasAuthoredMetadata(UsdGeomTokens->metersPerUnit);
}

bool UsdGeomSetStageMetersPerUnit(const UsdStageWeakPtr &stage, double metersPerUnit)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid UsdStage");
    return false;
  }

  return stage->SetMetadata(UsdGeomTokens->metersPerUnit, metersPerUnit);
}

bool UsdGeomLinearUnitsAre(double authoredUnits, double standardUnits, double epsilon)
{
  if (authoredUnits <= 0 || standardUnits <= 0) {
    return false;
  }

  const double diff = GfAbs(authoredUnits - standardUnits);
  return (diff / authoredUnits < epsilon) && (diff / standardUnits < epsilon);
}

PXR_NAMESPACE_CLOSE_SCOPE
