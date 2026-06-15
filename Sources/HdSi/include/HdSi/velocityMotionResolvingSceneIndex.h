//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDSI_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_H
#define PXR_IMAGING_HDSI_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_H

#include "Hd/dataSource.h"
#include "Hd/filteringSceneIndex.h"
#include "Hd/sceneIndex.h"
#include "Hd/sceneIndexObserver.h"
#include "Hdsi/api.h"

#include "Sdf/path.h"

#include "Tf/debug.h"
#include "Tf/declarePtrs.h"
#include "Tf/staticTokens.h"
#include "Tf/token.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEBUG_CODES(
    HDSI_VELOCITY_MOTION);

#define HDSI_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_TOKENS \
    (disable) \
    (enable) \
    (ignore) \
    (noAcceleration) \
    (timeCodesPerSecond) \
    ((velocityMotionMode, "__velocityMotionMode"))

TF_DECLARE_PUBLIC_TOKENS(HdsiVelocityMotionResolvingSceneIndexTokens,
    HDSI_API, HDSI_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_TOKENS);

TF_DECLARE_REF_PTRS(HdsiVelocityMotionResolvingSceneIndex);

/// Scene index that resolves velocity-based motion for all prims that support
/// it. For a complete discussion of how velocity-based motion works, when it
/// is valid, and how it is resolved, see the UsdGeom documentation here:
/// https://openusd.org/dev/api/usd_geom_page_front.html#UsdGeom_VelocityInterpolation
///
/// This scene index performs all the necessary calculations so that downstream
/// consumers do not need to worry about velocity-based motion. Downstream
/// consumers need only make the usual call to GetContributingSampleTimesForInterval()
/// for an affected primvar, then sample the primvar's value at the given times.
///
/// Affected primvars are:
///   For points-based geometry:
///     - points
///   For point instancers:
///     - instancePositions
///     - instanceRotations
///     - instanceScales
///
/// There is no need for downstream consumers to query velocities, accelerations,
/// or angularVelocities; their effects have already been applied to the sampled
/// values when appropriate. Downstream consumers will only see motion (or none),
/// again, as appropriate for the sampled primvar. Any distinction between
/// motion due to velocities and motion due to USD value interpolation is
/// intentionally lost.
///
/// Note that, where non-linear motion has been applied (i.e., points or
/// instancePositions with accelerations, or instance rotations with
/// angularVelocities), GetContributingSampleTimesForInterval() will provide
/// the correct number of sample times for non-linear motion, taking
/// UsdGeomMotionAPI's nonlinearSampleCount into consideration.
/// (Downstream consumers should still check nonlinearSampleCount in the
/// case of instanceRotations.)
///
/// Additionally, to support certain established workflows, the behavior of the
/// scene index may be controlled by the prim-level Hydra parameter
/// "__velocityMotionMode". This is never read from usd and must instead be
/// authored in a preceding filtering scene index. It is a token with one of the
/// following recognized values:
///
/// - enable: velocity-based motion is resolved according to the normal rules.
/// - disable: velocity-based motion is frozen to the most recent authored
///            positions/rotations for the current frame.
/// - ignore: velocity-based motion is ignored as if velocities are not present.
/// - noAcceleration: the effect of authored accelerations is ignored.
///
/// In all cases (except 'ignore'), __velocityMotionMode has no effect unless
/// the authored velocity data is valid (see link above for what counts as
/// valid). (In the case of 'ignore', validity is not evaluated.) Where the
/// velocity data is not valid, the scene index makes no changes to the incoming
/// scene data, which may indicate motion due to USD value interpolation where
/// appropriate.
///
class HdsiVelocityMotionResolvingSceneIndex
  : public HdSingleInputFilteringSceneIndexBase
{
public:
    HDSI_API
    static HdsiVelocityMotionResolvingSceneIndexRefPtr
    New(
        const HdSceneIndexBaseRefPtr& inputSceneIndex,
        const HdContainerDataSourceHandle& inputArgs = nullptr);

    HDSI_API
    HdSceneIndexPrim
    GetPrim(const SdfPath& primPath) const override;

    HDSI_API
    SdfPathVector
    GetChildPrimPaths(const SdfPath& primPath) const override;

    HDSI_API
    static bool
    PrimTypeSupportsVelocityMotion(const TfToken& primType);

protected:
    HdsiVelocityMotionResolvingSceneIndex(
        const HdSceneIndexBaseRefPtr& inputSceneIndex,
        const HdContainerDataSourceHandle& inputArgs = nullptr);

    void
    _PrimsAdded(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::AddedPrimEntries& entries) override;

    void
    _PrimsRemoved(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::RemovedPrimEntries& entries) override;

    void
    _PrimsDirtied(
        const HdSceneIndexBase& sender,
        const HdSceneIndexObserver::DirtiedPrimEntries& entries) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HDSI_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_H
