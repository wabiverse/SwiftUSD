//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdUtils/introspection.h"

#include "Tf/pyResultConversions.h"
#include "Tf/pyStaticTokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

VtDictionary 
_WrapUsdUtilsComputeUsdStageStats_1(const std::string &rootLayerPath) {
    VtDictionary stats;
    UsdUtilsComputeUsdStageStats(rootLayerPath, &stats);
    return stats;    
}

VtDictionary 
_WrapUsdUtilsComputeUsdStageStats_2(const UsdStageWeakPtr &stage) {
    VtDictionary stats;
    UsdUtilsComputeUsdStageStats(stage, &stats);
    return stats;
}

} // anonymous namespace 

void wrapIntrospection()
{
    TF_PY_WRAP_PUBLIC_TOKENS("UsdStageStatsKeys", UsdUtilsUsdStageStatsKeys, 
                             USDUTILS_USDSTAGE_STATS);

    def("ComputeUsdStageStats", _WrapUsdUtilsComputeUsdStageStats_1);
    def("ComputeUsdStageStats", _WrapUsdUtilsComputeUsdStageStats_2);
}
