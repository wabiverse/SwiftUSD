# ``Ar``

## Overview

The **Ar** (Asset Resolution) library is responsible for querying, reading, and
writing asset data. It provides several interfaces that allow **USD** to access
an asset without knowing how that asset is physically stored.

**Ar** ships with implementations based on a traditional filesystem. However,
users can provide custom implementations to integrate their own asset storage
system and behaviors with **USD**. For example, a user might have an asset system
that stores assets in a database and uses special identifiers to address those
assets. That user could create a custom implementation of the **ArResolver**
interface that interprets those identifiers and a custom implementation of the
**ArAsset** interface that reads data straight from the database. This would
allow the user to use those identifiers for references, payloads, and sublayer
composition arcs and other places throughout **USD**.

### **ArResolver**

**ArResolver** is the central interface for asset operations in **Ar**. Clients can
implement subclasses of this interface to customize behaviors for their asset
system.

**Ar** manages a set of ArResolver subclasses for handling different asset paths,
which are described below. These subclasses are discovered and instantiated via the
plugin system and managed internally by **Ar**. Instead of using these subclasses
directly, clients just use a single resolver that is accessed through calling the
[**ArGetResolver**](#ArGetResolver) class. When methods are called on this resolver,
**Ar** will determine the appropriate subclass for handling the given input paths and
forward the call to that subclass.

### **Primary Resolver**

The primary resolver is the **ArResolver** subclass that Ar uses to handle
all asset paths that are not handled by the other resolvers described below.

> Warning: **Ar** does not support custom resolvers implemented in Python to avoid performance issues, especially for multi-threaded consumers.

To create a custom primary resolver:

- Implement an ArResolver subclass

  ```cpp
  class CustomResolver : public ArResolver
  {}
  ```

- Use `#AR_DEFINE_RESOLVER` to define the subclass as a resolver

  ```cpp
  // In the custom resolver's .cpp file
  AR_DEFINE_RESOLVER(CustomResolver, ArResolver);
  ```

- Declare the subclass in the plugin's plugInfo.json file.
  See [**Plug Registry**](PlugRegistry) for more details.

  ```json
  /* plugInfo.json */
  {
    "Plugins": [
      {
        "Info": {
          "Types": {
            "CustomResolver": {
              "bases": ["ArResolver"]
            }
          }
        }
        /* ... */
      }
    ]
  }
  ```

  > Important: Ensure that the resolver plugin is located where the plugin system can find it.

<br/>

At runtime **Ar** will query the plugin system to discover any classes that have
**ArResolver** or another subclass of **ArResolver** declared as a base type, then
instantiate that class when needed. Keep in mind that the class may be
constructed at any time; at a minimum, the class will be constructed during the
first call to `ArGetResolver`.

If no custom resolver is found, **Ar** will use **ArDefaultResolver** as the
primary resolver. This resolver assumes all asset paths it encounters are
filesystem paths. **ArDefaultResolver** also performs simple search path based
resolution that will search for an asset in a specified list of directories.

> See the documentation regarding the behavior of
> [**ArDefaultResolver**](ArDefaultResolver) for
> more information on it's configuration options.

### **URI Resolvers**

**URI** resolvers are **ArResolver** subclasses that
are associated with particular **URI** schemes.

When **Ar** encounters an asset path or resolved path of the form `...`, it
will check if any **ArResolver** subclasses have been registered for the scheme.
If so, it will dispatch the path to that subclass for handling. If not, it will
dispatch the path to the primary resolver for handling.

For example, if there were an **HTTPResolver** subclass of ArResolver
that was registered to handle the `http` scheme, if the following was called:

```cpp
ArGetResolver().Resolve("http://mynetwork/model.usd")
```

**Ar** would inspect the given path, find the `http` scheme and determine that
`http` was associated with HTTPResolver. **Ar** would create an instance of the
`HTTPResolver` (if one had not already been created), then call it's respective
`HTTPResolver::Resolve` function on that instance with the given path.

To create a **URI** resolver:

- Implement a subclass of **ArResolver** as described in the
  [**Primary Resolver**](PrimaryResolver) section above.

- In the entry for the subclass in the plugin's plugInfo.json file,
  add a "uriSchemes" key with a list of URI schemes associated with the
  resolver.
  ```json
  /* plugInfo.json */
  {
    "Plugins": [
      {
        "Info": {
          "Types": {
            "HTTPResolver": {
              "bases": ["ArResolver"],
              "uriSchemes": ["http", "https"]
            }
          }
        }
        /* ... */
      }
    ]
  }
  ```

### **Asset Path Resolution**

An **asset path** is a string that describes the location of an asset in a user's
system. These paths are used extensively throughout **USD**; for example, asset
paths are used to specify **sublayers**, **references**, and **payloads** in scene
description.

One of **ArResolver's** primary responsibilities is to resolve an input asset
path by determining if an asset exists at the given path and, if so, returning
a resolved path that may be used by other **ArResolver** API and in other parts
of the system. This is done via calls to `ArResolver::Resolve`. This process
allows ArResolver subclasses to apply custom logic to determine the actual asset
that a logical asset path refers to.

For example, the filesystem-based **ArDefaultResolver** implements search-path logic
in its asset path resolution. When **ArDefaultResolver** is given a relative filesystem
asset path to resolve like `Foo/Bar/Baz.usd`, it will look for that file relative to
the current working directory, then relative to a set of search paths. Once it finds
an existing file, it will return the absolute path to that file as the resolved path.

For more details, see:

- [**Path Resolution Operations**](ArResolver_resolution)
- [**Implementation**](ArResolver_implementation)

### **Resolver Contexts**

A resolver context is an object that stores configuration or other information that
can be used by a resolver to guide path resolution and other operations. Resolver
contexts can be bound within blocks of code to affect resolver operations within
that scope via an **ArResolverContextBinder**. **UsdStage** uses this functionality
heavily to allow different stages to resolve asset paths differently.

For example, **ArDefaultResolver** has a context object **ArDefaultResolverContext**
that contains a set of search paths for use during resolution that prepend to this
**ArDefaultResolver's** list of global search paths.

A client might use this to set up stages that look in different
locations for assets:

```cpp
// Configure ArDefaultResolver's global search paths.
ArDefaultResolver::SetDefaultSearchPath({"/Global/assets"});

// Create a resolver context with an additional search path and
// use it for opening the UsdStage for ShotA.usd.
//
// If ShotA.usd contains an asset path like "Foo/Bar/Baz.usd",
// ArDefaultResolver will search for this file at:
//  - <current working dir>/Foo/Bar/Baz.usd
//  - /ShotA/assets/Foo/Bar/Baz.usd
//  - /Global/assets/Foo/Bar/Baz.usd
ArDefaultResolverContext shotACtx({"/ShotA/assets"})
UsdStageRefPtr shotA = UsdStage::Open("ShotA.usd", shotACtx);

// Create a resolver context with an additional search path and
// use it for opening the UsdStage for ShotB.usd.
//
// If ShotB.usd contains the same asset path as above in ShotA,
// ArDefaultResolver will search for this file at:
//  - <current working dir>/Foo/Bar/Baz.usd
//  - /ShotB/assets/Foo/Bar/Baz.usd
//  - /Global/assets/Foo/Bar/Baz.usd
ArDefaultResolverContext shotBCtx({"/ShotB/assets"})
UsdStageRefPtr shotB = UsdStage::Open("ShotB.usd", shotBCtx);
```

It's important to note that any information in a resolver context that is used
during path resolution should be factored into the resulting resolved path. This
is because resolved paths may be passed to downstream clients or over to external
libraries that will not (or can not) have a context object bound when the resolved
path is used to open an asset. Put another way: a resolved path should be usable by
downstream clients that do not have a resolver context bound.

Context binding and unbinding are thread-specific. If you bind a context in a
thread, that binding will only be visible to that thread. If you want to use
the same context to resolve asset paths in multiple threads, you’ll need to
bind the context in multiple threads.

For more details, see:

- [`ArResolverContext`](ArResolverContext)
- [`ArResolverContextBinder`](ArResolverContextBinder)
- [Asset Resolver Context Operations](AssetResolverContextOperations)
- [Context Operations Implementation](ContextOperationsImplementation)

### **Resolver Scoped Caches**

A resolver scoped cache is a cache of asset resolution results that is
active during a given block of code. Clients can activate a scoped cache
by using an **ArResolverScopedCache** object.

Resolving asset paths may be expensive and a **UsdStage** may need to resolve
hundreds to thousands of asset paths (or more) depending on the complexity of
the scene, many of which may be repeated. A scoped cache helps to minimize that
expense. A scoped cache also ensures that resolving a given asset path multiple
times returns the same result, which is important for consistency and correctness.

**Ar** provides default scoped cache behaviors for all ArResolver subclasses.
However, this default behavior is very basic. Subclasses may provide their
own scoped cache implementations that can take advantage of implementation
details of their underlying asset system to maximize efficiency. For such
cases **Ar** provides the **ArThreadLocalScopedCache** utility class to help
with this.

For more details, see:

- [Scoped Resolution Cache](ArResolver_scopedCache)
- [Scoped Resolution Cache Implementation](ArResolver_scopedCacheImplementation)

### **Asset Paths and Resolved Paths**

In general, **Ar** does not impose any requirements or restrictions on the format of
an asset path or resolved path. Users are free to use whatever path syntax they want
as long as they are supported by their underlying resolver implementations. For example,
the filesystem-based **ArDefaultResolver** simply uses filesystem paths, while some other
implementations might use special **URIs** or database identifiers.

**Ar** reserves trailing bracket-enclosed paths as syntax for package-relative asset
paths.

For example, paths like:

- ```brainfuck
  /foo/baz.usdz[file.usd]
  ```
- ```brainfuck
  my_uri://foo/baz.usdz[file.usd]
  ```

Will be recognized by **Ar** as a package-relative asset path and will be split so that
**ArResolver** subclasses will only see the path `/foo/baz.usdz` or `my_uri://foo/baz.usdz`.
For more details, see [**Package Relative Paths**](Ar_packagePaths).
