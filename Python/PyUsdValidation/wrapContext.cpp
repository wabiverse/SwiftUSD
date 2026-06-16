//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https:/</openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Sdf/layer.h"
#include "Tf/token.h"
#include "Plug/plugin.h"
#include "Usd/prim.h"
#include "Usd/primRange.h"
#include "Usd/stage.h"
#include "UsdValidation/validator.h"
#include "UsdValidation/context.h"
#include "UsdValidation/error.h"
#include "UsdValidation/timeRange.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/make_constructor.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdValidationContext()
{
    TfPyRegisterStlSequencesFromPython<UsdValidationError>();
    class_<UsdValidationContext>("ValidationContext", no_init)
        .def(init<const TfTokenVector &, bool>(
            (arg("keywords"), arg("includeAllAncestors") = true)))
        .def(init<const PlugPluginPtrVector &, bool>(
            (arg("plugins"), arg("includeAllAncestors") = true)))
        .def(init<const UsdValidationValidatorMetadataVector &, bool>(
            (arg("metadata"), arg("includeAllAncestors") = true)))
        .def(init<const std::vector<TfType> &>(arg("schemaTypes")))
        .def(init<const std::vector<const UsdValidationValidator*> &>(
            arg("validators")))
        .def(init<const std::vector<const UsdValidationValidatorSuite*> &>(
            arg("suites")))
        .def("Validate", 
             +[](const UsdValidationContext &ctx, const SdfLayerHandle &layer) 
                -> UsdValidationErrorVector {
                return ctx.Validate(layer);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("layer")))
        .def("Validate", 
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage) 
                -> UsdValidationErrorVector {
                return ctx.Validate(stage);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("stage")))
        .def("Validate",
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage, 
                const Usd_PrimFlagsPredicate &predicate) 
                -> UsdValidationErrorVector {
                return ctx.Validate(stage, predicate);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("stage"), arg("predicate")))
        .def("Validate",
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage, 
                 const Usd_PrimFlagsPredicate &predicate,
                 const UsdValidationTimeRange &timeRange)
                -> UsdValidationErrorVector {
                return ctx.Validate(stage, predicate, timeRange);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("stage"), arg("predicate"), arg("timeRange")))
        .def("Validate", 
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage,
                 const UsdValidationTimeRange &timeRange) 
                -> UsdValidationErrorVector {
                return ctx.Validate(stage, timeRange);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("stage"), arg("timeRange")))
        .def("Validate",
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage,
                 const Usd_PrimFlagsPredicate &predicate,
                 const std::vector<UsdTimeCode> &timeCodes)
                -> UsdValidationErrorVector {
                return ctx.Validate(stage, predicate, timeCodes);
            },
            return_value_policy<TfPySequenceToList>(),
            (arg("stage"), arg("predicate"), arg("timeCodes")))
        .def("Validate",
             +[](const UsdValidationContext &ctx, const UsdStagePtr &stage,
                 const std::vector<UsdTimeCode> &timeCodes)
                -> UsdValidationErrorVector {
                return ctx.Validate(stage, timeCodes);
            },
            return_value_policy<TfPySequenceToList>(),
            (arg("stage"), arg("timeCodes")))
        .def("Validate", 
             +[](const UsdValidationContext &ctx, 
                 const std::vector<UsdPrim> &prims,
                 const UsdValidationTimeRange &timeRange)
                -> UsdValidationErrorVector {
                return ctx.Validate(prims, timeRange);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("prims"), 
              arg("timeRange") = UsdValidationTimeRange()))
        .def("Validate", 
             +[](const UsdValidationContext &ctx, const UsdPrimRange &prims,
                 const UsdValidationTimeRange &timeRange)
                -> UsdValidationErrorVector {
                return ctx.Validate(prims, timeRange);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("prims"), 
              arg("timeCode") = UsdValidationTimeRange()))
        .def("Validate",
             +[](const UsdValidationContext &ctx,
                 const std::vector<UsdPrim> &prims,
                 const std::vector<UsdTimeCode> &timeCodes)
                -> UsdValidationErrorVector {
                return ctx.Validate(prims, timeCodes);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("prims"), arg("timeCodes")))
        .def("Validate",
             +[](const UsdValidationContext &ctx, const UsdPrimRange &prims,
                 const std::vector<UsdTimeCode> &timeCodes)
                -> UsdValidationErrorVector {
                return ctx.Validate(prims, timeCodes);
             },
             return_value_policy<TfPySequenceToList>(),
             (arg("prims"), arg("timeCodes")));
}
