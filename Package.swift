// swift-tools-version: 5.9

import PackageDescription

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
        "third_party/renderman-24/plugin/rtx_glfImage/main.cpp",
        "third_party/renderman-25/plugin/rtx_glfImage/main.cpp",
      ],
      publicHeadersPath: ".",
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),

    .testTarget(
      name: "USDTests",
      dependencies: ["USD"]
    ),
  ]
)
