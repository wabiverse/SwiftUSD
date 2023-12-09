### <sub>PrimCache Population (Composition)</sub>
# <sup>**Pixar.Pcp**</sup>

### **Overview**

Pcp implements the core scenegraph composition semantics &mdash; the
behavior informally referred to as <em>Layering &amp; Referencing</em>.

Pcp specializes in providing low-level composition services on behalf of
higher-level scenegraph libraries (Usd, Csd, Mf) that instantiate scenegraph
objects based on the results.  Most clients will typically use one of
those libraries, rather than consulting Pcp directly.  The name "Pcp"
stands for <em>Prim Cache Population</em>, a historical term for this
area of the system.

### Motivation

Objects in the scenegraph are backed by scene description -- authored
data describing those objects.

A single file of scene description is sufficient to describe a hierarchy
of objects.  However, it is also useful to organize that data across
multiple files.  For one thing, this provides a way for multiple people
(such as in different departments) to collaborate while keeping their
contributions distinct.  For another, this provides a means of re-use:
an asset like a rig or model can be built once, then used many times as needed.

This instancing is expressed as a "reference arc" that points at the
external file.  The Pcp runtime detects and interprets these arcs
to bring together the disparate files into a single combined set of opinions.
By using a reference arc, the underlying external asset can be continually
worked on, with improvements automatically being picked up in downstream
assets.

There are other kinds of arcs that provide variations of this behavior.
Pcp provides the service of identifying and interpreting these composition
arcs.

### Capabilities

Pcp implements the following composition semantics:
  - sublayers
  - list-editing
  - references
  - payloads
  - inherits / classes
  - variants
  - "standin" variant preferences
  - relocates
  - permissions

> [!NOTE]
> See the [Semantics](Pcp/Semantics) page for a detailed discussion.

In support of this, the runtime provides these features:
  - caching and cache invalidation
  - change processing
  - dependency tracking
  - namespace editing support
  - path translation
  - error detection
  - payload inclusion control
  - diagnostic output

Pcp is all about finding sources of opinions that contribute to objects.
It has little to do with the interpretation of those opinions.  As a
result, there are some higher-level features which are sometimes
thought of as part of composition, but which are not part of Pcp:

  - model hierarchy
  - scenegraph structure, objects and their identity
  - value resolution
  - symmetry

### Usage

#### The PcpCache

The main entrypoint to the Pcp algorithm is the PcpCache.  It provides
a context to specify the key parameters that configure how composition
should be performed.  It also provides storage for caching the results
of composition queries.

The input parameters to the composition algorithm are:
  - a root layer
  - a session layer (optional)
  - a path resolver context
  - standin preferences (ex: render, anim, etc.)
  - payload inclusion set -- paths for which payloads should be included

Most of these are fixed when a PcpCache is created.  The payload inclusion set
can be modified at runtime to bring payloads into and out of the working set.

#### Computation Queries

Once a cache has been created, it can service composition queries.
These apply composition algorithms to the underlying scene description
data.  See the ComputeXXX methods on PcpCache.  The most fundamental queries
are PcpCache::ComputeLayerStack() and PcpCache::ComputePrimIndex().
These two provide the majority of the composition semantics and are the
basis for the other queries.  Different queries return different types
of result values.

#### Errors

The process of composition may discover errors in the structure of the
scene.  For example, a reference arc might target a file that cannot be
found (resolved), or it might create a reference cycle.

These errors get first-class treatment in Pcp.  That is, errors are
not a side-effect; they are treated as a formal output of the composition
algorithms and returned alongside the primary results describing the
structure of the scene.  Pcp does not embed any error handling or
reporting policy.  It is entirely up to Pcp clients to dispatch errors.

> [!NOTE]
> Pcp **does** participate in the TfError reporting system when it
encounters API misuse (coding errors), as do the lower-level
modules it uses.  Pcp only treats errors in authored scene description
specially.

Errors are represented as instances of a PcpErrorBase base class.  Each
error sub-type contains semantic information about the source and exact
details of the error, as would be required to report the error to the
user, check if the error still applies, or programmatically address it.

Each Pcp computation stores a "local" set of errors that are specific to
that computation.  If one computation requires recursive computation --
such as one prim needing to compute a layer stack across a reference arc
-- the errors for the nested computation will be stored locally with
that nested computation.  Each Pcp result provides a GetLocalErrors()
API to examine its local errors.  Since errors are first-class results
of Pcp and stored as part of the primary composition outputs, they are
cached along with those outputs.

Clients of Pcp typically want to report errors when they are
first discovered.  They want to do this without needing knowledge
about the cache hit/miss behavior or the recursive nature of
composition queries.  To facilitate this common usage, Pcp API
provides an "allErrors" output argument that will accumulate any
newly discovered errors.  In the case of cache hits, existing errors
will not be reported.

For simple cases where you just want to raise Pcp errors as Tf
runtime errors, see PcpRaiseErrors().

#### Dependencies

In addition to the primary result and errors, computations also internally
retain the dependencies discovered by a cached computation result.
For example, computing a PcpPrimIndex that contains a reference will
internally record a dependency representing that reference.  This
dependency internally retains the scene description layer across the
reference.  Dependencies also provide a means to analyze and propagate
changes to the scene, as well as to implement namespace editing
(rename, reparent, and delete operations), which want to fix up
dependent scene opinions accordingly.  PcpCache has API to query
dependencies; for example, see PcpCache::GetPathsUsingSite().

#### Namespace Editing

The phrase "namespace editing" means operations that edit namespace:
renaming, reparenting, or removing composed objects.  Although Pcp
does not maintain a scenegraph of composed objects, it does provide
utilities for such a library to implement these operations, making
use of the Pcp dependencies to build a list of necessary edits to
the underlying layers that keep them consistent with one another.
See PcpCache::ComputeNamespaceEdits().

#### Change Processing

Pcp caches computation results derived from the underlying
scene description data.  When that underlying data changes, those
computations are no longer valid.  Pcp provides assistance to
determine which computations have been invalidated, and to re-compute
them as desired.  PcpChanges represents the effect that a set of changes
to scene description have on a PcpCache.  Processing changes has two
phases: the first is to build up the list of changes, (including chasing
dependencies to find all the affected caches); the second is to apply those
changes, invalidating the internal caches.  It is up to the client to
re-pull on any affected caches.  Since dependencies are dropped when
the cached computations that yielded them are invalidated, PcpLifeboat
provides a way to retain the underlying referenced data for the duration
of time until the client can re-pull on the cached computations.

Every PcpChanges object requested by a scenegraph client contains a
PcpLifeboat, so clients should rarely need to interact with one directly.

#### Path Translation

Composition arcs pull together scene description from different
places in layers.  Part of this process requires rebinding those
opinions to new paths.  For example, a model at the path
<tt> \</World/anim/chars/MeridaGroup/Merida\> </tt> may reference a model at
the source path <tt> \</Merida\> </tt>.  Now imagine a relationship authored
within <tt> \</Merida/rig/FaceRig\> </tt> to <tt> \</Merida/anim/Face\>. </tt>  To resolve
that relationship path, composition needs to transform the authored
values flowing across the arc so that they re-bind to the new namespace
position of Merida, in <tt> \</World/anim/chars/MeridaGroup/Merida/anim/Face\> </tt>.
This process is known as "path translation", and is one of the more subtle
and important behaviors of Pcp.  See PcpTranslatePathFromNodeToRoot()
and PcpTranslatePathFromRootToNode().

#### Diagnostics

Composition is a large subsystem and have can have complicated results.

To help analyze the system we provide a few features:
  - PcpPrimIndex::DumpToString() - to dump out a prim's structure
  - PcpPrimIndex::PrintStatistics() - to analyze a prim's structure
  - PcpCache::PrintStatistics() - to analyze a cache's overall footprint
  - TF_DEBUG runtime debugging flags -- see pcp/debugCodes.h
  - Optional additional runtime validation that must be compiled in: \p PCP_DIAGNOSTIC_VALIDATION
