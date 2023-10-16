// swift-tools-version: 5.9

import PackageDescription

/* --------------------------------------------------------------------------------------------- *
 * We will need to migrate these include paths once we provide each of Pixar's USD dependencies, *
 * we are also looking to the industry & community for guidance as to which versions we support. *
 * --------------------------------------------------------------------------------------------- */

#if os(macOS)
  let platformIncludes = [
    // macOS platform includes
    "-I/opt/homebrew/Cellar/tbb/2021.10.0/include",
    "-I/opt/homebrew/Cellar/boost/1.82.0_1/include",
    "-I/opt/homebrew/Cellar/imath/3.1.9/include",
    // Imath again because alembic likes it that way.
    "-I/opt/homebrew/Cellar/imath/3.1.9/include/Imath",
    "-I/opt/homebrew/Cellar/alembic/1.8.6/include",
    "-I/opt/homebrew/Cellar/openimageio/2.5.4.0/include",
    "-I/opt/homebrew/Cellar/opencolorio/2.2.1/include",
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
    "-I./imaging/hio/OpenEXR/deflate/lib/arm",
    // macOS compiler flags
    "-fno-objc-arc", /* disable ARC, as it's done manually for objc USD source. */
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
#else /* os(Windows) */
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
  products: [
    .library(
      name: "Pixar",
      targets: ["Pixar"]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/MetaverseKit.git", from: "1.0.0")
  ],
  targets: [
    .target(
      name: "Pixar",
      dependencies: [
        .product(name: "Draco", package: "MetaverseKit"),
        .product(name: "Eigen", package: "MetaverseKit"),
        .product(name: "Python", package: "MetaverseKit"),
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
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("OPENEXR_EXPORT", to: "static"),
      ],
      swiftSettings: [
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
