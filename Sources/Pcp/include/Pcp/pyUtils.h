//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_PCP_PY_UTILS_H
#define PXR_USD_PCP_PY_UTILS_H

#include "Pcp/api.h"
#include "Pcp/types.h"
#include "pxr/pxrns.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#include <boost/python/dict.hpp>

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

/// Convert the Python dictionary \p dict to a PcpVariantFallbackMap
/// object and return it via \p result, returning true if successful.
PCP_API
bool PcpVariantFallbackMapFromPython(const boost::python::dict &dict,
                                     PcpVariantFallbackMap *result);

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#endif  // PXR_USD_PCP_PY_UTILS_H
