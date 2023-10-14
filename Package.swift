// swift-tools-version: 5.9

import PackageDescription

/* --------------------------------------------------------------------------------------------- *
 * We will need to migrate these include paths once we provide each of Pixar's USD dependencies, *
 * we are also looking to the industry & community for guidance as to which versions we support. *
 * --------------------------------------------------------------------------------------------- */

#if os(macOS)
  let platformIncludes = [
    "-I/opt/homebrew/Cellar/tbb/2021.10.0/include",
    "-I/opt/homebrew/Cellar/python@3.10/3.10.13/Frameworks/Python.framework/Versions/3.10/include/python3.10",
    "-I/opt/homebrew/Cellar/boost/1.82.0_1/include",
    "-I/opt/homebrew/include",
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
        "../third_party/renderman-24/plugin/rtx_glfImage/main.cpp",
        "../third_party/renderman-25/plugin/rtx_glfImage/main.cpp",
      ],
      publicHeadersPath: ".",
      cxxSettings: [
        .unsafeFlags([
          "-I.",
        ] + platformIncludes),
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
