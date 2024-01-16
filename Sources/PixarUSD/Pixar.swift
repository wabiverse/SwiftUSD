/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import CxxStdlib
@_exported import pxr

public extension Pixar
{
  /**
   * The current version of ``PixarUSD``.
   *
   * The semantic versioning used for ``PixarUSD`` tracks both the upstream
   * Pixar USD version, as well as the evolution iteration of the ``PixarUSD``
   * SwiftPM package, which is setup as follows:
   * - ``PXR_MINOR_VERSION``.``PXR_PATCH_VERSION``.``SWIFTUSD_EVOLUTION`` */
  static let version = "\(PXR_MINOR_VERSION).\(PXR_PATCH_VERSION).\(SWIFTUSD_EVOLUTION)"

  /**
   * # ``Arch``
   *
   * **Architecture Dependent**
   *
   * ## Overview
   *
   * **Arch** is a repository for all **architecture-dependent code**.
   * It's purpose is to isolate all platform dependencies into one small library,
   * serving as a common area for documentation of these multi-platform issues. */
  enum Arch
  {}

  /**
   * # ``Js``
   *
   * **JSON I/O**
   *
   * ## Overview
   *
   * **Js** is the **JSON I/O** library, it contains methods for parsing and
   * writing JSON data from C++, and converting between arbitrary recursive
   * container structures. */
  enum Js
  {}

  /**
   * # ``Tf``
   *
   * **Tools Foundations**
   *
   * ## Overview
   *
   * **Tf** is the **tools foundations** library, it contains foundation
   * classes and functions for all C/C++ software development. */
  enum Tf
  {}

  /**
   * # ``Gf``
   *
   * **Graphics Foundations**
   *
   * ## Overview
   *
   * **Gf** is the **graphics foundations** library, it contains foundation
   * classes and functions for working with the basic mathematical aspects
   * of computer graphics. */
  enum Gf
  {}

  /**
   * # ``Trace``
   *
   * **Performance Tracking**
   *
   * ## Overview
   *
   * **Trace** is the **performance tracking** library, it contains utility classes
   * for counting, timing, measuring, and recording events. */
  enum Trace
  {}

  /**
   * # ``Work``
   *
   * **Multithreaded Dispatch**
   *
   * ## Overview
   *
   * **Work** is intended to simplify the use of *multithreading* in the context of
   * our software ecosystem. */
  enum Work
  {}

  /**
   * # ``Plug``
   *
   * **Plugin Framework**
   *
   * ## Overview
   *
   * **Plug** is the **plugin-in framework** implementation, the ``Plug/PlugPlugin`` class
   * defines the interface to plug-in modules. The ``Plug/PlugRegistry`` class defines a
   * mechanism for registering and looking up plug-in modules both automatically upon
   * first use and manually at runtime by client calls to ``Plug/PlugRegistry/registerPlugins()``. */
  enum Plug
  {}

  /**
   * # ``Vt``
   *
   * **Value Types**
   *
   * ## Overview
   *
   * **Vt** is the **value types** library, it provides classes that represent
   * basic value types such as arrays, strings, and tokens. This library operates
   * on the level of language data types and there are differences in the C++ and
   * Python APIs. */
  enum Vt
  {}

  /**
   * # ``Ar``
   *
   * **Asset Resolution**
   *
   * ## Overview
   *
   * **Ar** is the **asset resolution** library, and is responsible for querying, reading, and
   * writing asset data. It provides several interfaces that allow **USD** to access
   * an asset without knowing how that asset is physically stored. */
  enum Ar
  {}

  /**
   * # ``Kind``
   *
   * **Extensible Categorization**
   *
   * ## Overview
   *
   * The **Kind** library provides a runtime-extensible taxonomy known as **"Kinds"**.
   * **Kinds** are just **TfToken** symbols, but the ``Kind/KindRegistry`` allows for organizing
   * kinds into taxonomies of related/refined concepts, and the ``Kind/KindRegistry.GetBaseKind()``
   * and ``Kind/KindRegistry.is(a:)`` queries enable reasoning about the hierarchy and classifying
   * objects by kind. */
  enum Kind
  {}

  /**
   * # ``Sdf``
   *
   * **Scene Description Foundations**
   *
   * ## Overview
   *
   * **Sdf** provides the foundations for serializing scene description to a reference text format,
   * or a multitude of plugin-defined formats.  It also provides the primitive abstractions for
   * interacting with scene description, such as ``SdfPath``, ``SdfLayer``, ``SdfPrimSpec``. */
  enum Sdf
  {}

  /**
   * # ``Ndr``
   *
   * **Node Definition Registry**
   *
   * ## Overview
   *
   * **Ndr** provides a framework in which you can, agnostic to the node's domain
   * (shading, lighting, compositing, etc), register nodes with **Ndr**, and they
   * subsequently ask for information about those nodes. The information **Ndr**
   * provides about these nodes will be fairly generic, given that **Ndr** must
   * not cater to any specific type of node. However, specialized registries can
   * derive from **Ndr**, and it is there that domain-specific logic can be
   * implemented. Additionally, node parsing and "discovery" are done via
   * plugins, again to keep **Ndr** generic and extendable. */
  enum Ndr
  {}

  /**
   * # ``Sdr``
   *
   * **Shader Definition Registry**
   *
   * ## Overview
   *
   * **Sdr** is a shading-specialized version of Ndr, and provides the following
   * specialized classes:
   * - ``Sdr/Registry``: A registry for nodes that describe shading information.
   * - ``Sdr/ShaderNode``: A node that describes a shader.
   * - ``Sdr/ShaderProperty``: A node that describes a shader property.
   *
   * For more details on the registry, nodes, or properties, see the base Ndr
   * classes:
   * - ``PixarUSD/__ObjC/Pixar/Ndr/Registry``: A registry for nodes that describe information.
   * - ``PixarUSD/__ObjC/Pixar/Ndr/Node``: Represents an abstract node.
   * - ``PixarUSD/__ObjC/Pixar/Ndr/Property``: Represents a property (input or output) that is part of a ``PixarUSD/__ObjC/Pixar/Ndr/Node``. */
  enum Sdr
  {}

  /**
   * # ``Pcp``
   *
   * **PrimCache Population (Composition)**
   *
   * ## Overview
   *
   * Pcp implements the core scenegraph composition semantics — the behavior
   * informally referred to as *Layering & Referencing*. */
  enum Pcp
  {}

  /**
   * # ``Usd``
   *
   * **Universal Scene Description (Core)**
   *
   * ## Overview
   *
   * **Usd** is the **universal scene description** library, it provides a
   * high-level API for reading, authoring, and layering scene description. */
  enum Usd
  {}

  /**
   * # ``UsdGeom``
   *
   * **USD Geometry Schema**
   *
   * ## Overview
   *
   * **UsdGeom** defines the 3D graphics-related prim and property schemas that
   * together form a basis for interchanging geometry between DCC tools in a
   * graphics pipeline. */
  enum UsdGeom
  {}

  /**
   * # ``UsdLux``
   *
   * **USD Lighting Schema**
   *
   * ## Overview
   *
   * **UsdLux** provides a representation for lights and related components that
   * are common to many graphics environments and therefore suitable for interchange. */
  enum UsdLux
  {}

  /**
   * # ``UsdShade``
   *
   * **USD Shading Schema**
   *
   * ## Overview
   *
   * **UsdLux** provides a representation for lights and related components that
   * are common to many graphics environments and therefore suitable for interchange. */
  enum UsdShade
  {}

  enum UsdVol
  {}

  enum UsdMedia
  {}

  enum UsdRender
  {}

  enum UsdHydra
  {}

  enum UsdRi
  {}

  enum UsdSkel
  {}

  enum UsdUI
  {}

  enum UsdUtils
  {}

  enum UsdPhysics
  {}

  enum UsdAbc
  {}

  enum UsdDraco
  {}

  enum Garch
  {}

  enum CameraUtil
  {}

  enum PxOsd
  {}

  enum Glf
  {}

  enum UsdImagingGL
  {}

  enum UsdAppUtils
  {}

  enum Usdview
  {}
}

/* --- xxx --- */
