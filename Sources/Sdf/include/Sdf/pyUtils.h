//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_PY_UTILS_H
#define PXR_USD_SDF_PY_UTILS_H

#include "pxr/pxrns.h"
#include "Sdf/api.h"
#include "Sdf/layer.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/dict.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include <string>

#if PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_OPEN_SCOPE

/// Convert the Python dictionary \p dict to an SdfLayer::FileFormatArguments
/// object and return it via \p args. 
///
/// If a non-string key or value is encountered, \p errMsg will be filled in
/// (if given) and this function will return false. Otherwise, this function
/// will return true.
SDF_API bool
SdfFileFormatArgumentsFromPython(
    const pxr_boost::python::dict& dict,
    SdfLayer::FileFormatArguments* args,
    std::string* errMsg = NULL);

PXR_NAMESPACE_CLOSE_SCOPE
#endif // PXR_PYTHON_SUPPORT_ENABLED

#endif // PXR_USD_SDF_PY_UTILS_H