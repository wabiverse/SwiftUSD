//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/pyModule.h"
#include "UsdLux/blackbody.h"
#include "pxr/pxrns.h"
#include <boost/python/def.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
  TF_WRAP(UsdLuxTokens);

  boost::python::def("BlackbodyTemperatureAsRgb", UsdLuxBlackbodyTemperatureAsRgb);

  // Generated schema.  Base classes must precede derived classes.
  // Indentation shows class hierarchy.
  TF_WRAP(UsdLuxBoundableLightBase);
  TF_WRAP(UsdLuxNonboundableLightBase);
  {
    TF_WRAP(UsdLuxCylinderLight);
    TF_WRAP(UsdLuxDiskLight);
    TF_WRAP(UsdLuxDistantLight);
    TF_WRAP(UsdLuxRectLight);
    TF_WRAP(UsdLuxSphereLight);
    TF_WRAP(UsdLuxDomeLight);
    TF_WRAP(UsdLuxDomeLight_1);
    TF_WRAP(UsdLuxGeometryLight);
    TF_WRAP(UsdLuxPluginLight);
    TF_WRAP(UsdLuxPortalLight);
  }
  TF_WRAP(UsdLuxLightAPI);
  {
    TF_WRAP(UsdLuxMeshLightAPI);
    TF_WRAP(UsdLuxVolumeLightAPI);
  }
  TF_WRAP(UsdLuxLightListAPI);
  TF_WRAP(UsdLuxListAPI);
  TF_WRAP(UsdLuxShapingAPI);
  TF_WRAP(UsdLuxShadowAPI);
  TF_WRAP(UsdLuxLightFilter);
  TF_WRAP(UsdLuxPluginLightFilter);
}
