//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_SITE_UTILS_H
#define PXR_USD_SDF_SITE_UTILS_H

/// \file sdf/siteUtils.h
///
/// Convenience API for working with SdfSite.
///
/// These functions simply forward to the indicated functions on SdfLayer.

#include "Sdf/layer.h"
#include "Sdf/primSpec.h"
#include "Sdf/propertySpec.h"
#include "Sdf/site.h"
#include "Sdf/spec.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

inline SdfSpecHandle SdfGetObjectAtPath(const SdfSite &site)
{
  return site.layer->GetObjectAtPath(site.path);
}

inline SdfPrimSpecHandle SdfGetPrimAtPath(const SdfSite &site)
{
  return site.layer->GetPrimAtPath(site.path);
}

inline SdfPropertySpecHandle SdfGetPropertyAtPath(const SdfSite &site)
{
  return site.layer->GetPropertyAtPath(site.path);
}

inline bool SdfHasField(const SdfSite &site, const TfToken &field)
{
  return site.layer->HasField(site.path, field);
}

template<class T> inline bool SdfHasField(const SdfSite &site, const TfToken &field, T *value)
{
  return site.layer->HasField(site.path, field, value);
}

inline const VtValue SdfGetField(const SdfSite &site, const TfToken &field)
{
  return site.layer->GetField(site.path, field);
}

template<class T>
inline T SdfGetFieldAs(const SdfSite &site, const TfToken &field, const T &defaultValue = T())
{
  return site.layer->GetFieldAs<T>(site.path, field, defaultValue);
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_SDF_SITE_UTILS_H
