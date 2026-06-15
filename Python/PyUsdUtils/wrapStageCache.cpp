//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdUtils/stageCache.h"

#include "Tf/pyResultConversions.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapStageCache()
{
    class_<UsdUtilsStageCache>("StageCache")

        .def("Get", &UsdUtilsStageCache::Get,
             return_value_policy<reference_existing_object>())
        .staticmethod("Get")

        .def<SdfLayerRefPtr (*)(
            const TfToken& name,
            const std::vector<std::pair<std::string, std::string>>&)>(
            "GetSessionLayerForVariantSelections",
            &UsdUtilsStageCache::GetSessionLayerForVariantSelections,
            (arg("modelName"), arg("variantSelections"))
            )
        .def<SdfLayerRefPtr (*)(
            const SdfPath& primPath,
            const std::vector<std::pair<std::string, std::string>>&)>(
            "GetSessionLayerForVariantSelections",
            &UsdUtilsStageCache::GetSessionLayerForVariantSelections,
            (arg("primPath"), arg("variantSelections")))
        .staticmethod("GetSessionLayerForVariantSelections")
        ;
}
