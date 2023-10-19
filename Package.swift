// swift-tools-version: 5.9

import PackageDescription

/* --------------------------------------------------------------------------------------------- *
 * We will need to migrate these include paths once we provide each of Pixar's USD dependencies, *
 * we are also looking to the industry & community for guidance as to which versions we support. *
 * --------------------------------------------------------------------------------------------- */

#if os(macOS)
  let platformIncludes = [
    // macOS platform includes
    "-I/opt/homebrew/Cellar/imath/3.1.9/include",
    // Imath again because alembic likes it that way.
    "-I/opt/homebrew/Cellar/imath/3.1.9/include/Imath",
    "-I/opt/homebrew/Cellar/alembic/1.8.6/include",
    "-I/opt/homebrew/Cellar/openimageio/2.5.4.0/include",
    "-I/opt/homebrew/Cellar/opencolorio/2.2.1/include",
    "-I/opt/homebrew/Cellar/ptex/2.4.2/include",
    "-I/opt/homebrew/Cellar/opensubdiv/3.6.0/include",
    "-I/opt/homebrew/Cellar/openvdb/10.0.1_2/include",
    "-I/opt/homebrew/Cellar/vulkan-headers/1.3.267/include",
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
    .watchOS(.v4)
  ],
  products: [
    .library(
      name: "Pixar",
      targets: ["Pixar"]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/MetaverseKit.git", from: "1.0.7")
  ],
  targets: [
    .target(
      name: "Pixar",
      dependencies: [
        .product(name: "OneTBB", package: "MetaverseKit"),
        .product(name: "Boost", package: "MetaverseKit"),
        .product(name: "Python", package: "MetaverseKit"),
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
