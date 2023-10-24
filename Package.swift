// swift-tools-version: 5.9

import PackageDescription

/* --------------------------------------------------------------------------------------------- *
 * We will need to migrate these include paths once we provide each of Pixar's USD dependencies, *
 * we are also looking to the industry & community for guidance as to which versions we support. *
 * --------------------------------------------------------------------------------------------- */

#if os(macOS)
  let platformIncludes = [
    // macOS platform includes
    // this is the wabi-preferred way to install ASWF projects on macOS
    // (gives users a launchable MaterialX Viewer, etc.), which can be
    // complicated to setup, especially for non-technical users.
    // wabi will offer app bundles for each ASWF project, on github.
    "-I/Applications/MaterialX.app/Contents/Resources/1.38.8/include",
    "-I/Applications/OSL.app/Contents/Resources/1.12.13/include",
    // from X11 (through XQuartz) on macOS.
    "-I/opt/X11/include",
    "-I./imaging/hio/OpenEXR",
    "-I./imaging/hio/OpenEXR/deflate/lib",
    "-I./imaging/hio/OpenEXR/deflate/lib/arm"
  ]
  let platformExcludes = [
    // headers not intended for macOS.
    "include/pxr/imaging/garch/glPlatformContextGLX.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowGLX.h",
    "include/pxr/imaging/garch/glPlatformContextWindows.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowWindows.h",
    // source not intended for macOS.
    "imaging/garch/glPlatformContextGLX.cpp",
    "imaging/garch/glPlatformDebugWindowGLX.cpp",
    "imaging/garch/glPlatformContextWindows.cpp",
    "imaging/garch/glPlatformDebugWindowWindows.cpp",
  ]
#elseif os(Linux)
  let platformIncludes = [
    "-I/usr/include",
  ]
  let platformExcludes = [
    // headers not intended for linux.
    "include/pxr/imaging/garch/glPlatformContextDarwin.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowDarwin.h",
    "include/pxr/imaging/garch/glPlatformContextWindows.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowWindows.h",
    // source not intended for linux.
    "imaging/garch/glPlatformContextDarwin.mm",
    "imaging/garch/glPlatformDebugWindowDarwin.mm",
    "imaging/garch/glPlatformContextWindows.cpp",
    "imaging/garch/glPlatformDebugWindowWindows.cpp",
  ]
#elseif os(Windows)
  let platformIncludes = []
  let platformExcludes = [
    // headers not intended for windows.
    "include/pxr/imaging/garch/glPlatformContextGLX.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowGLX.h",
    "include/pxr/imaging/garch/glPlatformContextDarwin.h",
    "include/pxr/imaging/garch/glPlatformDebugWindowDarwin.h",
    // source not intended for windows.
    "imaging/garch/glPlatformContextGLX.cpp",
    "imaging/garch/glPlatformDebugWindowGLX.cpp",
    "imaging/garch/glPlatformContextDarwin.mm",
    "imaging/garch/glPlatformDebugWindowDarwin.mm",
  ]
#endif /* os(Windows) */

let package = Package(
  name: "SwiftUSD",
  platforms: [
    .macOS(.v11),
    .visionOS(.v1),
    .iOS(.v12),
    .tvOS(.v12),
    .watchOS(.v4),
  ],
  products: [
    .library(
      name: "Pixar",
      targets: ["Pixar"]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/MetaverseKit.git", from: "1.1.5"),
  ],
  targets: [
    .target(
      name: "Pixar",
      dependencies: [
        .product(name: "OneTBB", package: "MetaverseKit"),
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
        .product(name: "Shaderc", package: "MetaverseKit"),
        .product(name: "SPIRVCross", package: "MetaverseKit"),
        .product(name: "MoltenVK", package: "MetaverseKit", condition: .when(platforms: [.macOS, .iOS, .visionOS, .tvOS, .watchOS])),
      ],
      exclude: [
        "base/tf/testenv/main.cpp",
        "usd/usd/testenv",
        "usd/usd/examples.cpp",
        "usd/usd/codegenTemplates",
        "imaging/plugin/hdEmbree",
        "imaging/glf/testGLContext.cpp",
      ] + platformExcludes,
      publicHeadersPath: "include",
      cxxSettings: [
        .unsafeFlags(platformIncludes),
        /* ---------- Turn everything on. ---------- */
        .define("PXR_USE_NAMESPACES", to: "1"),
        .define("PXR_PYTHON_SUPPORT_ENABLED", to: "1"),
        .define("PXR_PREFER_SAFETY_OVER_SPEED", to: "1"),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OCIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_OIIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_PTEX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OPENVDB_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OSL_SUPPORT_ENABLED", to: "1"),
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_HDF5_SUPPORT_ENABLED", to: "1"),
        /* --------- Apple platforms only. --------- */
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: [.macOS, .iOS, .visionOS, .tvOS, .watchOS])),
      ],
      swiftSettings: [
        /* ------ C & CXX <-> Swift Interop. ------- */
        .interoperabilityMode(.Cxx),
      ]
    ),

    .testTarget(
      name: "USDTests",
      dependencies: ["Pixar"]
    ),
  ],
  cxxLanguageStandard: .cxx17
)
