//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Hd/basisCurves.h"
#include "Hd/tokens.h"
#include "Tf/envSetting.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdBasisCurvesReprDescTokens, HD_BASISCURVES_REPR_DESC_TOKENS);

TF_DEFINE_ENV_SETTING(HD_ENABLE_REFINED_CURVES, 0, "Force curves to always be refined.");

HdBasisCurves::HdBasisCurves(SdfPath const &id) : HdRprim(id)
{
  /*NOTHING*/
}

HdBasisCurves::~HdBasisCurves() = default;

/* virtual */
TfTokenVector const &HdBasisCurves::GetBuiltinPrimvarNames() const
{
  static const TfTokenVector primvarNames = {
      HdTokens->points, HdTokens->normals, HdTokens->widths};
  return primvarNames;
}

// static repr configuration
HdBasisCurves::_BasisCurvesReprConfig HdBasisCurves::_reprDescConfig;

/* static */
bool HdBasisCurves::IsEnabledForceRefinedCurves()
{
  return TfGetEnvSetting(HD_ENABLE_REFINED_CURVES) == 1;
}

/* static */
void HdBasisCurves::ConfigureRepr(TfToken const &reprName, HdBasisCurvesReprDesc desc)
{
  HD_TRACE_FUNCTION();

  if (IsEnabledForceRefinedCurves()) {
    desc.geomStyle = HdBasisCurvesGeomStylePatch;
  }

  _reprDescConfig.AddOrUpdate(reprName, _BasisCurvesReprConfig::DescArray{desc});
}

/* static */
HdBasisCurves::_BasisCurvesReprConfig::DescArray HdBasisCurves::_GetReprDesc(
    TfToken const &reprName)
{
  return _reprDescConfig.Find(reprName);
}

PXR_NAMESPACE_CLOSE_SCOPE
