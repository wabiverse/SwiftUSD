//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/dataSourceCamera.h"
#include "UsdImaging/dataSourceAttribute.h"

#include "Hd/cameraSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

template<typename T> class _ScalingTypedSampledDataSource : public HdTypedSampledDataSource<T> {
 public:
  HD_DECLARE_DATASOURCE(_ScalingTypedSampledDataSource<T>);

  _ScalingTypedSampledDataSource(const typename HdTypedSampledDataSource<T>::Handle &dataSource,
                                 T scale)
      : _dataSource(dataSource), _scale(scale)
  {
  }

  VtValue GetValue(HdSampledDataSource::Time shutterOffset) override
  {
    return VtValue(GetTypedValue(shutterOffset));
  }

  T GetTypedValue(HdSampledDataSource::Time shutterOffset) override
  {
    if (!_dataSource) {
      return 0.0f;
    }
    return _dataSource->GetTypedValue(shutterOffset) * _scale;
  }

  bool GetContributingSampleTimesForInterval(
      HdSampledDataSource::Time startTime,
      HdSampledDataSource::Time endTime,
      std::vector<HdSampledDataSource::Time> *outSampleTimes) override
  {
    if (!_dataSource) {
      return false;
    }
    return _dataSource->GetContributingSampleTimesForInterval(startTime, endTime, outSampleTimes);
  }

 private:
  typename HdTypedSampledDataSource<T>::Handle _dataSource;
  T _scale;
};

class _Vec4fArrayToVec4dArrayDataSource : public HdTypedSampledDataSource<VtArray<GfVec4d>> {
 public:
  HD_DECLARE_DATASOURCE(_Vec4fArrayToVec4dArrayDataSource);

  _Vec4fArrayToVec4dArrayDataSource(
      const HdTypedSampledDataSource<VtArray<GfVec4f>>::Handle &dataSource)
      : _dataSource(dataSource)
  {
  }

  VtValue GetValue(HdSampledDataSource::Time shutterOffset) override
  {
    return VtValue(GetTypedValue(shutterOffset));
  }

  VtArray<GfVec4d> GetTypedValue(HdSampledDataSource::Time shutterOffset) override
  {
    VtArray<GfVec4d> result;
    if (!_dataSource) {
      return result;
    }

    const VtArray<GfVec4f> data = _dataSource->GetTypedValue(shutterOffset);
    result.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
      result[i] = GfVec4d(data[i]);
    }
    return result;
  }

  bool GetContributingSampleTimesForInterval(
      HdSampledDataSource::Time startTime,
      HdSampledDataSource::Time endTime,
      std::vector<HdSampledDataSource::Time> *outSampleTimes) override
  {
    if (!_dataSource) {
      return false;
    }

    return _dataSource->GetContributingSampleTimesForInterval(startTime, endTime, outSampleTimes);
  }

 private:
  typename HdTypedSampledDataSource<VtArray<GfVec4f>>::Handle _dataSource;
};

}  // namespace

UsdImagingDataSourceCamera::UsdImagingDataSourceCamera(
    const SdfPath &sceneIndexPath,
    UsdGeomCamera usdCamera,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
    : _sceneIndexPath(sceneIndexPath), _usdCamera(usdCamera), _stageGlobals(stageGlobals)
{
}

TfTokenVector UsdImagingDataSourceCamera::GetNames()
{
  return UsdGeomCamera::GetSchemaAttributeNames(/* includeInherited = */ false);
}

HdDataSourceBaseHandle UsdImagingDataSourceCamera::Get(const TfToken &name)
{
  TfToken usdName = name;
  // UsdGeomTokens->shutterOpen is "shutter:open" and thus different
  // from the camera schema.
  if (name == HdCameraSchemaTokens->shutterOpen) {
    usdName = UsdGeomTokens->shutterOpen;
  }
  // Similar to shutterOpen.
  if (name == HdCameraSchemaTokens->shutterClose) {
    usdName = UsdGeomTokens->shutterClose;
  }

  UsdAttribute attr = _usdCamera.GetPrim().GetAttribute(usdName);

  if (!attr) {
    return nullptr;
  }

  HdSampledDataSourceHandle const dataSource = UsdImagingDataSourceAttributeNew(
      attr, _stageGlobals, _sceneIndexPath, HdCameraSchema::GetDefaultLocator().Append(name));
  if (name == UsdGeomTokens->horizontalAperture || name == UsdGeomTokens->verticalAperture ||
      name == UsdGeomTokens->horizontalApertureOffset ||
      name == UsdGeomTokens->verticalApertureOffset)
  {
    return _ScalingTypedSampledDataSource<float>::New(
        HdTypedSampledDataSource<float>::Cast(dataSource), float(GfCamera::APERTURE_UNIT));
  }
  else if (name == UsdGeomTokens->focalLength) {
    return _ScalingTypedSampledDataSource<float>::New(
        HdTypedSampledDataSource<float>::Cast(dataSource), float(GfCamera::FOCAL_LENGTH_UNIT));
  }
  else if (name == UsdGeomTokens->clippingPlanes) {
    return _Vec4fArrayToVec4dArrayDataSource::New(
        HdTypedSampledDataSource<VtArray<GfVec4f>>::Cast(dataSource));
  }

  return dataSource;
}

// ----------------------------------------------------------------------------

UsdImagingDataSourceCameraPrim::UsdImagingDataSourceCameraPrim(
    const SdfPath &sceneIndexPath,
    UsdPrim usdPrim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
    : UsdImagingDataSourcePrim(sceneIndexPath, usdPrim, stageGlobals)
{
}

TfTokenVector UsdImagingDataSourceCameraPrim::GetNames()
{
  TfTokenVector result = UsdImagingDataSourcePrim::GetNames();
  result.push_back(HdCameraSchema::GetSchemaToken());
  return result;
}

HdDataSourceBaseHandle UsdImagingDataSourceCameraPrim::Get(const TfToken &name)
{
  if (name == HdCameraSchema::GetSchemaToken()) {
    return UsdImagingDataSourceCamera::New(
        _GetSceneIndexPath(), UsdGeomCamera(_GetUsdPrim()), _GetStageGlobals());
  }

  return UsdImagingDataSourcePrim::Get(name);
}

HdDataSourceLocatorSet UsdImagingDataSourceCameraPrim::Invalidate(
    UsdPrim const &prim,
    const TfToken &subprim,
    const TfTokenVector &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  TRACE_FUNCTION();

  HdDataSourceLocatorSet locators = UsdImagingDataSourcePrim::Invalidate(
      prim, subprim, properties, invalidationType);

  static TfTokenVector usdNames = UsdGeomCamera::GetSchemaAttributeNames(
      /* includeInherited = */ false);

  for (const TfToken &propertyName : properties) {
    for (const TfToken &usdName : usdNames) {
      if (propertyName == usdName) {
        if (usdName == UsdGeomTokens->shutterOpen) {
          // UsdGeomTokens->shutterOpen is "shutter:open" and thus
          // different from camera schema.
          locators.insert(HdCameraSchema::GetShutterOpenLocator());
        }
        else if (usdName == UsdGeomTokens->shutterClose) {
          // Similar to shutterOpen.
          locators.insert(HdCameraSchema::GetShutterCloseLocator());
        }
        else {
          locators.insert(HdCameraSchema::GetDefaultLocator().Append(propertyName));
        }
      }
    }
  }

  return locators;
}

PXR_NAMESPACE_CLOSE_SCOPE
