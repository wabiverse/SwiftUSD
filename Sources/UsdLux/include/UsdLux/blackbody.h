//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_LUX_BLACKBODY_H
#define PXR_USD_USD_LUX_BLACKBODY_H

/// \file usdLux/blackbody.h

#include "Gf/vec3f.h"
#include "UsdLux/api.h"

PXR_NAMESPACE_OPEN_SCOPE

/// Compute the RGB equivalent of the spectrum emitted by a blackbody
/// with the given temperature in degrees Kelvin, with normalized
/// luminance.
USDLUX_API
GfVec3f UsdLuxBlackbodyTemperatureAsRgb(float colorTemp);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
