// swift-tools-version: 5.9
import PackageDescription

let package = Package(
  name: "SwiftUSD",
  platforms: [
    .macOS(.v12),
    .visionOS(.v1),
    .iOS(.v12),
    .tvOS(.v12),
    .watchOS(.v4),
  ],
  products: [
    .library(
      name: "pxr",
      targets: ["pxr"]
    ),
    .library(
      name: "PXRBaseArch",
      targets: ["PXRBaseArch"]
    ),
    .library(
      name: "Pixar",
      targets: ["Pixar"]
    ),
  ],
  dependencies: [
    /* ----------------- a single dependency to rule them all. ----------------- */
    .package(url: "https://github.com/wabiverse/MetaverseKit.git", from: "1.2.5"),
    /* ------------------------------------------------------------------------- */
  ],
  targets: [
    .target(
      name: "pxr",
      dependencies: [],
      publicHeadersPath: "include"
    ),

    .target(
      name: "PXRBaseArch",
      dependencies: [
        /* ------------ pxr Namespace. ---------- */
        .target(name: "pxr"),
        /* ------------ VFX Platform. ----------- */
        .product(name: "MetaTBB", package: "MetaverseKit"),
        .product(name: "MaterialX", package: "MetaverseKit"),
        .product(name: "Boost", package: "MetaverseKit"),
        .product(name: "Python", package: "MetaverseKit"),
        .product(name: "MetaPy", package: "MetaverseKit"),
        .product(name: "Alembic", package: "MetaverseKit"),
        .product(name: "OpenColorIO", package: "MetaverseKit"),
        .product(name: "OpenImageIO", package: "MetaverseKit"),
        .product(name: "OpenEXR", package: "MetaverseKit"),
        .product(name: "OpenSubdiv", package: "MetaverseKit"),
        .product(name: "OpenVDB", package: "MetaverseKit"),
        .product(name: "Ptex", package: "MetaverseKit"),
        .product(name: "Draco", package: "MetaverseKit"),
        .product(name: "Eigen", package: "MetaverseKit"),
        /* ---------- Apple only libs. ---------- */
        .product(name: "Apple", package: "MetaverseKit", condition: .when(platforms: Arch.OS.apple.platform)),
        .product(name: "MoltenVK", package: "MetaverseKit", condition: .when(platforms: Arch.OS.apple.platform)),
      ],
      exclude: [
        /* ---------- Exclude example files. ---------- */
        // "usd/usd/examples.cpp",
        /* ---------- Exclude codegen files. ---------- */
        // "usd/usd/codegenTemplates",
        /* ---------- Exclude plugins files. ---------- */
        // "imaging/plugin/hdEmbree", // TODO: add Embree.
        // "usd/plugin/sdrOsl",       // TODO: add OSL.
        /* ---------- Exclude testing files. ---------- */
        // "imaging/glf/testGLContext.cpp",
        /* -------------------------------------------- */
      ],
      publicHeadersPath: "include",
      cxxSettings: [
        /* ---------- Turn everything on. ---------- */
        .define("PXR_USE_NAMESPACES", to: "1"),
        .define("PXR_PYTHON_SUPPORT_ENABLED", to: "1"),
        .define("PXR_PREFER_SAFETY_OVER_SPEED", to: "1"),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OCIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_OIIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_PTEX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OPENVDB_SUPPORT_ENABLED", to: "1"),
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_HDF5_SUPPORT_ENABLED", to: "1"),
        /* --------- OSL is temp disabled. --------- */
        .define("PXR_OSL_SUPPORT_ENABLED", to: "0"),
        /* --------- Apple platforms only. --------- */
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: [.macOS, .iOS, .visionOS, .tvOS, .watchOS])),
      ]
    ),

    .target(
      name: "Pixar",
      dependencies: [
        .target(name: "PXRBaseArch"),
      ],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),

    // .testTarget(
    //   name: "OpenUSDTests",
    //   dependencies: ["PXRBaseArch"]
    // ),
    .testTarget(
      name: "PixarTests",
      dependencies: ["Pixar"],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),
  ],
  cxxLanguageStandard: .cxx17
)

/* --- xxx --- */

/* ------------------------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                                          ::
 * ------------------------------------------------------------------------------
 * Pixar's USD is a pretty complicated build. That being said, this single config
 * is less than 100 lines of code. Compare that to the ~21419 lines of CMake code
 * across ~156 files as of the current release branch, SwiftPM brings substantial
 * improvements which drive maintainability and readability, and that's before we
 * even get to the benefits of Swift, ...or the fact it's now connected to a very
 * capable package manager, in a lot of ways, this is a game changer. Through the
 * Swift Package Manager, we can now leverage the power of USD, and what it means
 * to build plugins, and applications, in a way that is much more accessible to
 * the wider community. This is a very exciting time for the USD project, and we
 * are very excited to be a part of it.
 *
 *                       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * ------------------------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .  o  x  o    . : : : .
 * ------------------------------------------------------------------------------ */

/* --- xxx --- */

/** ------------------------------------------------
 * Just to tidy up the package configuration above,
 * we define some helper functions and types below.
 * ------------------------------------------------ */
enum Arch
{
  /** OS platforms, grouped by family. */
  enum OS
  {
    case apple
    case linux
    case windows
    case web

    public var platform: [Platform]
    {
      switch self
      {
        case .apple: [.macOS, .iOS, .visionOS, .tvOS, .watchOS]
        case .linux: [.linux, .android, .openbsd]
        case .windows: [.windows]
        case .web: [.wasi]
      }
    }
  }
}
