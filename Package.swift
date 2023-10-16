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
    "-I/opt/homebrew/Cellar/python@3.11/3.11.5/Frameworks/Python.framework/Versions/3.11/include/python3.11",
    "-I/opt/homebrew/Cellar/boost/1.82.0_1/include",
    "-I/opt/homebrew/include/Imath",
    // this is the wabi-preferred way to install ASWF projects on macOS
    // (gives users a launchable MaterialX Viewer, etc.), which can be
    // complicated to setup, especially for non-technical users.
    // wabi will offer app bundles for each ASWF project, on github.
    "-I/Applications/MaterialX.app/Contents/Resources/1.38.8/include",
    "-I/Applications/OSL.app/Contents/Resources/1.12.13/include",
    // from X11 (through XQuartz) on macOS.
    "-I/opt/X11/include",
    "-I/opt/homebrew/include",
    // macOS compiler flags
    "-fno-objc-arc", /* disable ARC, as it's done manually for objc USD source. */
  ]
  let platformExcludes = [
    // x11 source (diabled for all but linux but could be enabled on macOS through XQuartz).
    "imaging/garch/glPlatformContextGLX.h",
    "imaging/garch/glPlatformContextGLX.cpp",
    "imaging/garch/glPlatformDebugWindowGLX.h",
    "imaging/garch/glPlatformDebugWindowGLX.cpp",
    // msdos source not indended for anyone else.
    "imaging/garch/glPlatformContextWindows.h",
    "imaging/garch/glPlatformContextWindows.cpp",
    "imaging/garch/glPlatformDebugWindowWindows.h",
    "imaging/garch/glPlatformDebugWindowWindows.cpp",
  ]
#elseif os(Linux)
  let platformIncludes = [
    "-I/usr/include",
  ]
  let platformExcludes = [
    // macos source not indended for anyone else.
    "imaging/garch/glPlatformContextDarwin.h",
    "imaging/garch/glPlatformContextDarwin.mm",
    "imaging/garch/glPlatformDebugWindowDarwin.h",
    "imaging/garch/glPlatformDebugWindowDarwin.mm",
    // msdos source not indended for anyone else.
    "imaging/garch/glPlatformContextWindows.h",
    "imaging/garch/glPlatformContextWindows.cpp",
    "imaging/garch/glPlatformDebugWindowWindows.h",
    "imaging/garch/glPlatformDebugWindowWindows.cpp",
  ]
#else /* os(Windows) */
  let platformIncludes = []
  let platformExcludes = [
    // x11 source (diabled for all but linux but could be enabled on msdos through XMing/Cygwin).
    "imaging/garch/glPlatformContextGLX.h",
    "imaging/garch/glPlatformContextGLX.cpp",
    "imaging/garch/glPlatformDebugWindowGLX.h",
    "imaging/garch/glPlatformDebugWindowGLX.cpp",
    // macos source not indended for anyone else.
    "imaging/garch/glPlatformContextDarwin.h",
    "imaging/garch/glPlatformContextDarwin.mm",
    "imaging/garch/glPlatformDebugWindowDarwin.h",
    "imaging/garch/glPlatformDebugWindowDarwin.mm",
  ]
#endif /* os(Windows) */

let package = Package(
  name: "SwiftUSD",
  products: [
    .library(
      name: "USD",
      targets: ["USD"]
    ),
  ],
  targets: [
    .target(
      name: "USD",
      path: "pxr",
      exclude: [
        "base/tf/testenv/main.cpp",
        "usd/usd/testenv",
        "usd/usd/examples.cpp",
        "usd/usd/codegenTemplates",
        "imaging/plugin/hdEmbree",
        "imaging/glf/testGLContext.cpp",
        "../third_party/renderman-24/plugin/rtx_glfImage/main.cpp",
        "../third_party/renderman-25/plugin/rtx_glfImage/main.cpp",
      ] + platformExcludes,
      publicHeadersPath: ".",
      cxxSettings: [
        .unsafeFlags([
          "-I.",
        ] + platformIncludes),
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("OPENEXR_EXPORT", to: "static"),
      ],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),

    .testTarget(
      name: "USDTests",
      dependencies: ["USD"]
    ),
  ],
  cxxLanguageStandard: .cxx17
)
