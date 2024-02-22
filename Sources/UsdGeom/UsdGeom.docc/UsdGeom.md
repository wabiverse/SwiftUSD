# `UsdGeom`

## Overview

**UsdGeom** defines the 3D graphics-related prim and property schemas that
together form a basis for interchanging geometry between DCC tools in a
graphics pipeline.

### Geometric Primitive Schemas

#### UsdGeomImageable

Currently, all classes in UsdGeom inherit from UsdGeomImageable, whose intent is
to capture any prim type that might want to be rendered or visualized. This
distinction is made for two reasons:

- so that there _could_ be types that would never want to be renderered,
  and can thus be optimized around, for traversals, and also to enable
  validation: for example, in a compatible shading schema, only
  UsdGeomImageable-derived prims should be able to express a look/material
  binding.
- for the common properties described in UsdGeomImageable, including visibility,
  [purpose](Pixar/UsdGeom/ImageablePurpose), and the attribute schema for
  [primvars](Pixar/UsdGeom/PrimvarsOverview).

Admittedly, not all of the classes inheriting from UsdGeomImageable really need
to be imageable - they are grouped as they are to avoid the need for
multiple-inheritance, which would arise because some classes that may not
necessarily be imageable are definitely transformable.

#### UsdGeomXformable

In UsdGeom, all geometry prims are directly transformable. This is
primarily a scalability and complexity management decision, since prim-count
has a strong correlation to total scene composition time and memory
footprint, and eliminating the need for a "shape" node for every piece of
geometry generally reduces overall prim count by anywhere from 30% to 50%,
depending on depth and branching factor of a scene's namespace hierarchy.

UsdGeomXformable encapsulates the schema for a prim that is transformable.
Readers familiar with AbcGeom's Xform schema will find Xformable familiar,
but more easily introspectable. Xformable decomposes a transformation into
an ordered sequence of \ref UsdGeomXformOp "ops"; unlike AbcGeom::Xform,
which packs the op data into static and varying arrays, UsdGeomXformable
expresses each op as an independent UsdAttribute. This data layout, while
somewhat more expensive to extract, is much more conducive to "composed scene
description" because it allows individual ops to be overridden in stronger
layers independently of all other ops. We provide facilities leveraging
core Usd features that help mitigate the extra cost of reading more
attributes per-prim for performance-sensitive clients.

Of course, UsdGeom still requires a prim schema that simply represents a
transformable prim that scopes other child prims, which is fulfilled by
UsdGeomXform .

> [!NOTE]
> You may find it useful to digest the
> [basic assumptions of UsdGeom linear algebra](Pixar/UsdGeom/linAlgBasics)

#### UsdGeomGprim

UsdGeomGprim is the base class for all "geometric primitives", which encodes
several per-primitive graphics-related properties. Defined Gprims currently
include:

- UsdGeomMesh
- UsdGeomNurbsPatch
- UsdGeomBasisCurves
- UsdGeomNurbsCurves
- UsdGeomPoints
- UsdGeomCapsule
- UsdGeomCone
- UsdGeomCube
- UsdGeomCylinder
- UsdGeomSphere

We expect there to be some debate around the last five "intrinsic" Gprims:
Capsule, Cone, Cube, Cylinder, and Sphere, as not all DCC's support them as
primitives. In Pixar's pipeline, we in fact rarely render these primitives,
but find them highly useful for their fast inside/outside tests in defining
volumes for lighting effects, procedural modifiers (such as "kill spheres"
for instancers), and colliders. The last, in particular, is quite useful for
interchanging data with rigid-body simulators. It is necessary to be able to
transmit these volumes from dressing/animation tools to
simulation/lighting/rendering tools, thus their presence in our schema. We
expect to support these and other "non-native" schema types as some form of
proxy or "pass through" prim in DCC's that do not understand them.

#### UsdGeomPointInstancer

UsdGeomPointInstancer provides a powerful, scalable encoding for scattering
many instances of multiple prototype objects (which can be arbitrary subtrees
of the UsdStage that contains the PointInstancer), animating both the
instances and prototypes, and pruning/masking instances based on integer ID.

#### UsdGeomCamera

UsdGeomCamera encodes a transformable camera.

#### UsdGeomModelAPI

UsdGeomModelAPI is an API schema that extends the basic UsdModelAPI API with concepts
unique to models that contain 3D geometry. This includes:

- \ref UsdGeomModelAPI::GetExtentsHint "cached extent hints encompassing an entire model"
- API for collecting and extracting all \ref UsdGeomConstraintTarget "constraint targets" for a model from the model's root prim.

### Primvars (Primitive Variables)

"Primvars" are an important concept in UsdGeom. Primvars are attributes with
a number of extra features that address the following problems in
computer graphics:

1. The need to "bind" user data on geometric primitives that becomes available
   to shaders during rendering.
2. The need to specify a set of values associated with vertices or faces of a
   primitive that will interpolate across the primitive's surface under
   subdivision or shading.
3. The need to _inherit_ attributes down namespace to allow sparse authoring of
   sharable data that is compatible with
   \ref Usd_ScenegraphInstancing_Overview "native scenegraph instancing"

One example that involves the first two problems is _texture coordinates_
(commonly referred to as "uv's"), which are cast as primvars in UsdGeom.
UsdGeomPrimvar encapsulates a single primvar, and provides the features
associated with interpolating data across a surface. UsdGeomPrimvarsAPI
provides the interface for creating and querying primvars on a prim, as well
as the computations related to primvar inheritance.

### Imageable Purpose

Purpose is a concept we have found useful in our pipeline for
classifying geometry into categories that can each be independently
included or excluded from traversals of prims on a stage, such as
rendering or bounding-box computation traversals. The fallback
purpose, \em default indicates that a prim has "no special purpose"
and should generally be included in all traversals. Prims with purpose
\em render should generally only be included when performing a "final
quality" render. Prims with purpose \em proxy should generally only be
included when performing a lightweight proxy render (such as openGL).  
Finally, prims with purpose \em guide should generally only be included
when an interactive application has been explicitly asked to "show guides".

A prim that is Imageable with an authored opinion about its purpose will
always have the same effective purpose as its authored value. If the
prim is not Imageable or does not have an authored opinion about its own
purpose, then it will inherit the purpose of the closest Imageable
ancestor with an authored purpose opinion. If there are no Imageable
ancestors with an authored purpose opinion then this prim uses its
fallback purpose.

For example, if you have a prim tree like such

```
def "Root" {
    token purpose = "proxy"

    def Xform "RenderXform" {
        token purpose = "render"

        def "Prim" {
            token purpose = "default"

            def Xform "InheritXform" {
            }

            def Xform "GuideXform" {
                token purpose = "guide"
            }
        }
    }

    def Xform "Xform" {
    }
}
```

\li </Root> is not Imageable so its purpose attribute is ignored and its
effective purpose is \em default.
\li </Root/RenderXform> is Imageable and has an authored purpose of
\em render so its effective purpose is \em render.
\li </Root/RenderXform/Prim> is not Imageable so its purpose attribute is
ignored. ComputePurpose will return the effective purpose of
\em render, inherited from its parent Imageable's authored purpose.
\li </Root/RenderXform/Prim/InheritXform> is Imageable but with no authored
purpose. Its effective purpose is \em render, inherited from the
authored purpose of </Root/RenderXform>
\li </Root/RenderXform/Prim/GuideXform> is Imageable and has an authored
purpose of \em guide so its effective purpose is \em guide.
\li </Root/Xform> is Imageable but with no authored purpose. It also has
no Imageable ancestor with an authored purpose its effective purpose is
its fallback value of \em default.

Purpose \em render can be useful in creating "light blocker"
geometry for raytracing interior scenes. Purposes \em render and
\em proxy can be used together to partition a complicated model
into a lightweight proxy representation for interactive use, and a
fully realized, potentially quite heavy, representation for rendering.
One can use UsdVariantSets to create proxy representations, but doing
so requires that we recompose parts of the UsdStage in order to change
to a different runtime level of detail, and that does not interact
well with the needs of multithreaded rendering. Purpose provides us with
a better tool for dynamic, interactive complexity management.

As demonstrated in UsdGeomBBoxCache, a traverser should be ready to
accept combinations of included purposes as an input.

### Linear Algebra in UsdGeom

To ensure reliable interchange, we stipulate the following foundational
mathematical assumptions, which are codified in the
\ref gf_overview "Graphics Foundations (Gf) math module":

- Matrices are laid out and indexed in row-major order, such that, given
  a \c GfMatrix4d datum \em mat, \em mat[3][1] denotes the second column
  of the fourth row.
- GfVec datatypes are row vectors that **pre-multiply** matrices to
  effect transformations, which implies, for example, that it is the fourth
  row of a GfMatrix4d that specifies the translation of the transformation.
- All rotation angles are expressed in degrees, not radians.
- Vector cross-products and rotations intrinsically follow the
  <A HREF="https://en.wikipedia.org/wiki/Right-hand_rule">right hand rule.</A>

So, for example, transforming a vector **v** by first a Scale matrix **S**,
then a Rotation matrix **R**, and finally a Translation matrix **T** can be
written as the following mathematical expression:

\par
**vt** = **v** &times; **S** &times; **R** &times; **T**

Because Gf exposes transformation methods on Matrices, not Vectors, to
effect this transformation in Python, one would write:
\code{py}
vt = (S _ R _ T).Transform(v)
\endcode

### Coordinate System, Winding Order, Orientation, and Surface Normals

Deriving from the mathematical assumptions in the preceding section, UsdGeom
positions objects in a **right handed coordinate system**, and a UsdGeomCamera
views the scene in a right-handed coordinate system where
**up is +Y, right is +X, and the forward viewing direction is -Z** - this
is explained and diagrammed in \ref UsdRender_Camera "UsdRenderCamera". If you
find yourself needing to import USD into a system that operates in a left-handed
coordinate system, you may find [this article](https://towardsdatascience.com/change-of-basis-3909ef4bed43) useful.

UsdGeom also, by default, applies the right hand rule to compute the
"intrinsic", _surface normal_ (also sometimes referred to as the
_geometric normal_) for all non-implicit surface and solid types.  
That is, the normal computed from (e.g.) a polygon's sequential vertices
using the right handed winding rule determines the "front" or "outward"
facing direction, that typically, when rendered will receive lighting
calculations and shading.

Since not all modeling and animation packages agree on the right hand rule,
UsdGeomGprim introduces the \ref UsdGeomGprim::GetOrientationAttr() "orientation"
attribute to enable individual gprims to select the left hand winding rule,
instead. So, gprims whose _orientation_ is "rightHanded" (which is the
fallback) must use the right hand rule to compute their surface normal,
while gprims whose _orientation_ is "leftHanded" must use the left hand rule.

However, any given gprim's \ref
UsdGeomImageable::ComputeLocalToWorldTransform() "local-to-world transformation"
can _flip_ its effective orientation, when it contains an odd
number of negative scales. This condition can be reliably detected using the
(Jacobian) determinant of the local-to-world transform: if the determinant
is **less than zero**, then the gprim's orientation has been flipped, and
therefore one must apply the **opposite** handedness rule when computing its
surface normals (or just flip the computed normals) for the purposes of
hidden surface detection and lighting calculations.

### Applying Timesampled Velocities to Geometry

UsdGeomPointBased primitives and UsdGeomPointInstancer primitives all allow
the specification of \ref UsdGeomPointBased::GetVelocitiesAttr() "velocities"
and \ref UsdGeomPointInstancer::GetAccelerationsAttr() "accelerations"
to describe point (or instance) motion at off-sample UsdTimeCode s, as an
alternative to relying on native UsdStage linear sample interpolation.  
Using velocities is the **only reliable way** of encoding the motion of
primitives whose topology is varying over time, as adjacent samples' indices
may be unrelated to each other, and the samples themselves may not even
possess the same number of elements.

To help ensure that all consumers of UsdGeom data will compute identical posing
from the same dataset, we describe how the position, velocity, and acceleration
data should be sampled and combined to produce "interpolated" positions. There
are several cases to consider, for which we stipulate the following logic:

- If no _velocities_ are authored, then we fall back to the "standard"
  position computation logic: if the timeSamples bracketing a requested sample
  have the same number of elements, apply linear interpolation between the two
  samples; otherwise, use the value of the sample with the lower/earlier ordinate.

- If the bracketing timeSamples for _velocities_ from the
  requested timeSample have the _same ordinates_ as those for _points_ then **use
  the lower _velocities_ timeSample and the lower _points_ timeSample** for the
  computations described below.

- If _velocities_ are authored, but the sampling does not line up with that
  of _points_, fall back to standard position computation logic, as if
  no _velocities_ were authored. This is effectively a silent error case.

- If no _accelerations_ are authored, **use the lower _velocities_ timeSample
  and the lower _points_ timeSample** for the computations described below.
  _accelerations_ are set to 0 in all dimensions for the computations.

- If the bracketing timeSamples for _accelerations_ from the requested
  timeSample have the _same ordinates_ as those for _velocities_ and
  _points_ then **use the lower _accelerations_ timeSample, the lower
  _velocities_ timeSample and the lower _points_ timeSample** for the
  computations described below.

- If _accelerations_ are authored but the sampling does not line up with that
  of _velocities_, if the sampling of _velocities_ lines up with that of
  _positions_ **use the lower _velocities_ timeSample and the lower _points_
  timeSample** for the computations described below, as if no _accelerations_
  were authored. If the sampling of _velocities_ does not line up with that of
  _positions_, fall back to the "standard" position computation logic as if no
  _velocities_ or _accelerations_ were authored.

**In summary,** we stipulate that the sample-placement of the _points_,
_velocities_, and _accelerations_ attributes be identical in each range
over which we want to compute motion samples. We do not allow velocities
to be recorded at times at which there is not a corresponding _points_ sample.  
This is to simplify and expedite the calculations required to compute a position
at any requested time. Since most simulators produce both a position and
velocity at each timeStep, we do not believe this restriction should impose
an undue burden.

Note that the sampling requirements are applied to each requested motion
sampling interval independently. So, for example, if _points_ and _velocities_
have samples at times 0, 1, 2, 3, but then _velocities_ has an
extra sample at 2.5, and we are computing forward motion blur on each frame,
then we should get velocity-interpolated positions for the motion-blocks for
frames 0, 1, and 3, but no interpolation for frame 2.

#### Computing a Single Requested Position

If one requires a pose at only a single point in time, _sampleTime_, such as
when stepping through "sub-frames" in an application like _usdview_, then we
need simply apply the above rules, and if we successfully sample _points_,
_velocities_, and _accelerations_, let:

\par
<em>t<sub>points</sub></em> = the lower bracketing time sample for the
evaluated _points_ attribute

\par
_timeScale_ = 1.0 / <tt>stage->GetTimeCodesPerSecond()</tt>

... then

\par
<em> **pointsInterpolated** = **points** + (sampleTime - t<sub>points</sub>) _
timeScale _ (**velocities** + (0.5 _ (sampleTime - t<sub>points</sub>) _
timeScale \* **accelerations**))</em>

#### Computing a Range of Requested Positions

Computer graphics renderers typically simulate the effect of non-zero camera
shutter intervals (which introduces <a
href="https://en.wikipedia.org/wiki/Motion_blur">motion blur</a> into an
image) by sampling moving geometry at multiple, nearby sample times, for each
rendered image, linearly blending the results of each sample. Most, if not
all renderers introduce the simplifying assumption that for any given image
we wish to render, we will not allow the topology of geometry to change over
the time-range we sample for motion blur.

Therefore, if we are sampling a topologically varying,
_velocities_-possessing UsdGeomMesh at sample times <em>t<sub>1</sub></em>,
<em>t<sub>2</sub></em> ... <em>t<sub>n</sub></em> in order to render the
mesh with motion blur, we stipulate that all _n_ samples be computed from
<b>the same sampled _points_, _velocities_, and _accelerations_ values
sampled at*sampleTime*</b>. Therefore, we would compute all _n_ samples
using the above formula, but iterating over the _n_ samples, substituting
<em>t<sub>i</sub></em> for _sampleTime_.

Two things to note:

- Since we are applying strictly linear interpolation, why is it useful to
  compute more than two samples? For UsdGeomPointBased primitives, the
  object-space samples will not require more than two samples, although
  local-to-world transformations may introduce non-linear motion. For
  UsdGeomPointInstancer primitives, which also possess an _angularVelocities_
  attribute for the instances, it may often be desirable to sample the
  instance matrices (and therefore _positions_) at a higher frequency since
  angular motion is non-linear.

- If the range of <em>t<sub>1</sub></em> to <em>t<sub>n</sub></em> is greater
  than the recorded sampling frequency of _points_, then computing the
  "singular" value of _points_ at some time <em>t<sub>other</sub></em> that
  is within the range <em>t<sub>1</sub></em> to <em>t<sub>n</sub></em> may
  produce a different value (with differing number of elements) than the
  computed value for the same **singular** time using the motion blur
  technique. This derives from our requirement that over the given motion
  range, the topology must not change, so we specifically ignore any other
  _points_, _velocities_, or _accelerations_ samples that occur in the
  requested motion range.

#### MotionAPI: Modulating Motion and Motion Blur

UsdGeomMotionAPI is an applied schema whose properties describe how
scene sampling should be adjusted to achieve artist-specified changes to
perceived motion, such as adjusting the amount of motion-blur differently
for different objects in a scene. All of the properties defined by this schema
should be inherited down namespace, so that one can adjust the blurring of an
entire model with a single statement/opinion on the model's root prim.

#### Effectively Applying `motion:blurScale`

The _motion:blurScale_ attribute allows artists to
scale the **amount** of motion blur to be rendered for parts of the scene
without changing the recorded animation. We stipulate that this should
at least affect the primary geometric properties of prims, such as:

- Points (UsdGeomPointBased)
- Normals (UsdGeomPointBased)
- Transforms (UsdGeomXformable)
- Instance Transforms (UsdGeomPointInstancer)

Beyond that "geometric motion core" of properties, renderers should apply
_blurScale_ to any other attributes that they _can_ blur.

We can implement this feature by either mutating (scaling) the sample values
we send to a renderer, or by adjusting our sampling and sample times. We
suggest that the latter provides superior results, and therefore describe it
in more detail.

We begin by establishing the difference between the **sampling window** and
the **shutter window** when preparing data for a renderer. The **sampling
window** is the interval in _scene time_ in which we will sample the scene
for rendering any particular frame, and changes as we render successive
frames. The **shutter window** (as typically specified via UsdGeomCamera's
_shutter:open_ and _shutter:close_ properties) is the interval in which the
renderer will look for samples to consume, is often centered around zero,
and is usually the same for all frames.

This means we translate samples from the sampling domain to the shutter
domain by simply subtracting the "current frame time" from the time ordinate
of each sample. However, by scaling the sampling window and adding in a
compensatory inverse scale to the translation of sample time to shutter time,
we can very simply implement the _motion:blurScale_ behavior. More
precisely:
\par
We scale the sampling window by _motion:blurScale_, pivoting around the
current frame time, and then scale the ordinates of the
shutter-interval-space samples by 1.0 / _motion:blurScale_, pivoting around
zero.

For example, let us assume we are rendering a bouncing ball with a sampling
window of `[frameTime, frameTime+0.5]` and a shutter window of `[0, 0.5]`.

If we want to **reduce the blur by a factor of 2**, we set _motion:blurScale_
to `0.5`, **scaling** the sampling window by `0.5` (around the pivot of
`frameTime`), and "pushing out" the smaller window of samples by a factor of
two to make them fill the shutter window - we realize less blur by taking
samples closer to the shutter-open and "looking at them" longer. Concretely,
if we are taking the usual two samples, the first sample is unchanged (as we
would expect since it provides the anchoring pose); however, the _second_
sample is evaluated at scene time `frameTime + 0.25` instead of `frameTime +
0.5`, but the time ordinate we attach to it as we hand it to the renderer is
`0.5`.

If we want to **increase the blur by a factor of 3**, we set
_motion:blurScale_ to `3.0`, **scaling** the sampling window by a factor of
three (around the pivot of `frameTime`) which, for high-quality
render-preppers such as Hydra means that we will prepare **all** the samples
we find in the scene in the interval `[frameTime, frameTime+1.5]`, which will
likely encompass **more** samples, representing more motion. For those
samples to contribute to the render, they must be made to fit within the
shutter window, so we rescale the sample times such that, for example, if the
final sample were at frame-relative scene time `1.5`, it would be scaled by
1/3 to rest at shutter time `0.5`.

This technique works equally well for motion derived from simple,
interpolation-based sampling, and also for samples computed using velocities
and accelerations, as described in \ref UsdGeom_VelocityInterpolation .

### Stage Metrics

The classes described above are concerned with individual primitives and
properties. Some geometic quantities, however, describe aspects of an entire
scene, which we encode as _stage metadata_. For example it is UsdGeom that
allows \ref UsdGeomUpAxis_group and \ref UsdGeomLinearUnits_group.
