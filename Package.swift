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
    "-I/Applications/MaterialX.app/Contents/Resources/1.38.8/include",
    "-I/Applications/OSL.app/Contents/Resources/1.12.13/include",
    "-I/opt/homebrew/include",
    // macOS compiler flags
    "-fno-objc-arc", /* disable ARC, as it's done manually for objc USD source. */
  ]
#elseif os(Linux)
  let platformIncludes = [
    "-I/usr/include",
  ]
#endif

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
        "../third_party/renderman-24/plugin/rtx_glfImage/main.cpp",
        "../third_party/renderman-25/plugin/rtx_glfImage/main.cpp",
      ],
      publicHeadersPath: ".",
      cxxSettings: [
        .unsafeFlags([
          "-I.",
        ] + platformIncludes),
        .define("OPENEXR_EXPORT", to: "static")
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
