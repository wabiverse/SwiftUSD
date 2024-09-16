// swift-tools-version: 5.10
import CompilerPluginSupport
import Foundation
import PackageDescription

/// previous versions of swift before 6.0 have issues
/// compiling swift macros, so galah is only supported
/// for swift 6.0+.
var galahDeps: [Package.Dependency] = []
var galahSettings: [SwiftSetting] = [.interoperabilityMode(.Cxx)]
var galahTargetDeps: [Target.Dependency] = [.target(name: "PixarUSD")]
_ = Galah()

let package = Package(
  name: "SwiftUSD",
  platforms: [
    .macOS(.v14),
    .visionOS(.v1),
    .iOS(.v17),
    .tvOS(.v17),
    .watchOS(.v10)
  ],
  products: [
    // ---------------- Pixar -----
    .library(
      name: "pxr",
      targets: ["pxr"]
    ),
    // ----------- Pixar.Base -----
    .library(
      name: "Arch",
      targets: ["Arch"]
    ),
    .library(
      name: "Tf",
      targets: ["Tf"]
    ),
    .library(
      name: "Js",
      targets: ["Js"]
    ),
    .library(
      name: "Gf",
      targets: ["Gf"]
    ),
    .library(
      name: "Trace",
      targets: ["Trace"]
    ),
    .library(
      name: "Vt",
      targets: ["Vt"]
    ),
    .library(
      name: "Work",
      targets: ["Work"]
    ),
    .library(
      name: "Pegtl",
      targets: ["Pegtl"]
    ),
    .library(
      name: "Plug",
      targets: ["Plug"]
    ),
    // ------------ Pixar.Usd -----
    .library(
      name: "Ar",
      targets: ["Ar"]
    ),
    .library(
      name: "Kind",
      targets: ["Kind"]
    ),
    .library(
      name: "Sdf",
      targets: ["Sdf"]
    ),
    .library(
      name: "Pcp",
      targets: ["Pcp"]
    ),
    .library(
      name: "Usd",
      targets: ["Usd"]
    ),
    .library(
      name: "Ndr",
      targets: ["Ndr"]
    ),
    .library(
      name: "Sdr",
      targets: ["Sdr"]
    ),
    .library(
      name: "UsdGeom",
      targets: ["UsdGeom"]
    ),
    .library(
      name: "UsdShade",
      targets: ["UsdShade"]
    ),
    .library(
      name: "UsdLux",
      targets: ["UsdLux"]
    ),
    .library(
      name: "UsdHydra",
      targets: ["UsdHydra"]
    ),
    .library(
      name: "SdrOsl",
      targets: ["SdrOsl"]
    ),
    .library(
      name: "UsdAbc",
      targets: ["UsdAbc"]
    ),
    .library(
      name: "UsdDraco",
      targets: ["UsdDraco"]
    ),
    .library(
      name: "UsdMedia",
      targets: ["UsdMedia"]
    ),
    .library(
      name: "UsdMtlx",
      targets: ["UsdMtlx"]
    ),
    .library(
      name: "UsdPhysics",
      targets: ["UsdPhysics"]
    ),
    .library(
      name: "UsdProc",
      targets: ["UsdProc"]
    ),
    .library(
      name: "UsdRender",
      targets: ["UsdRender"]
    ),
    .library(
      name: "UsdRi",
      targets: ["UsdRi"]
    ),
    .library(
      name: "UsdSkel",
      targets: ["UsdSkel"]
    ),
    .library(
      name: "UsdUI",
      targets: ["UsdUI"]
    ),
    .library(
      name: "UsdUtils",
      targets: ["UsdUtils"]
    ),
    .library(
      name: "UsdVol",
      targets: ["UsdVol"]
    ),
    // -------- Pixar.Imaging -----
    .library(
      name: "CameraUtil",
      targets: ["CameraUtil"]
    ),
    .library(
      name: "Hf",
      targets: ["Hf"]
    ),
    .library(
      name: "PxOsd",
      targets: ["PxOsd"]
    ),
    .library(
      name: "Hd",
      targets: ["Hd"]
    ),
    .library(
      name: "HdAr",
      targets: ["HdAr"]
    ),
    .library(
      name: "HdMtlx",
      targets: ["HdMtlx"]
    ),
    .library(
      name: "HdSi",
      targets: ["HdSi"]
    ),
    .library(
      name: "HdSt",
      targets: ["HdSt"]
    ),
    .library(
      name: "HdStorm",
      targets: ["HdStorm"]
    ),
    .library(
      name: "Hdx",
      targets: ["Hdx"]
    ),
    .library(
      name: "Garch",
      targets: ["Garch"]
    ),
    .library(
      name: "Hgi",
      targets: ["Hgi"]
    ),
    .library(
      name: "HgiMetal",
      targets: ["HgiMetal"]
    ),
    // .library(
    //   name: "HgiVulkan",
    //   targets: ["HgiVulkan"]
    // ),
    .library(
      name: "HgiGL",
      targets: ["HgiGL"]
    ),
    .library(
      name: "HgiInterop",
      targets: ["HgiInterop"]
    ),
    .library(
      name: "Hio",
      targets: ["Hio"]
    ),
    .library(
      name: "Glf",
      targets: ["Glf"]
    ),
    .library(
      name: "GeomUtil",
      targets: ["GeomUtil"]
    ),
    // ----- Pixar.UsdImaging -----
    .library(
      name: "UsdShaders",
      targets: ["UsdShaders"]
    ),
    .library(
      name: "UsdImaging",
      targets: ["UsdImaging"]
    ),
    .library(
      name: "UsdImagingGL",
      targets: ["UsdImagingGL"]
    ),
    // ----------------- Apps -----
    .executable(
      name: "UsdView",
      targets: ["UsdView"]
    ),
    .executable(
      name: "OpenUSD",
      targets: ["OpenUSD"]
    ),
    .executable(
      name: "Examples",
      targets: ["Examples"]
    ),
    // -------- Swift Plugins -----
    .plugin(
      name: "OpenUSDPlugin",
      targets: ["OpenUSDPlugin"]
    ),
    .plugin(
      name: "UsdGenSchemaPlugin",
      targets: ["UsdGenSchemaPlugin"]
    ),
    // ------------- Rust USD -----
    // .library(
    //   name: "rust-usd",
    //   type: .static,
    //   targets: ["rust-usd"]
    // ),
    // ------- Monolithic USD -----
    .library(
      name: "PixarUSD",
      targets: ["PixarUSD"]
    ),
  ],
  dependencies: [
    // prepare for SwiftCrossUI, for a cross-platform UsdView.
    // .package(url: "https://github.com/stackotter/swift-cross-ui", revision: "5c5d8c8"),
    .package(url: "https://github.com/wabiverse/MetaverseKit", from: "1.8.3"),
    .package(url: "https://github.com/apple/swift-log.git", from: "1.5.3"),
    .package(url: "https://github.com/apple/swift-syntax.git", from: "510.0.3"),
    .package(url: "https://github.com/apple/swift-argument-parser", from: "1.4.0"),
    .package(url: "https://github.com/apple/swift-docc-plugin", from: "1.3.0"),
    .package(url: "https://github.com/onevcat/Rainbow.git", from: "3.0.0"),
    .package(url: "https://github.com/mxcl/Version.git", from: "2.0.0"),
  ] + galahDeps,
  targets: [
    .target(
      name: "pxr",
      dependencies: [],
      publicHeadersPath: "include",
      cxxSettings: [
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Arch",
      dependencies: [
        /* ------------ pxr Namespace. ---------- */
        .target(name: "pxr"),
        /* ------------ VFX Platform. ----------- */
        .product(name: "MetaTBB", package: "MetaverseKit"),
        .product(name: "PyBind11", package: "MetaverseKit", condition: .when(platforms: Arch.OS.nix.platform)),
        .product(name: "MaterialX", package: "MetaverseKit"),
        .product(name: "Alembic", package: "MetaverseKit"),
        .product(name: "OpenColorIO", package: "MetaverseKit"),
        .product(name: "OpenImageIO", package: "MetaverseKit"),
        .product(name: "OpenEXR", package: "MetaverseKit"),
        .product(name: "OpenSubdiv", package: "MetaverseKit"),
        .product(name: "OpenVDB", package: "MetaverseKit"),
        .product(name: "Ptex", package: "MetaverseKit"),
        .product(name: "Draco", package: "MetaverseKit"),
        .product(name: "Eigen", package: "MetaverseKit"),
        .product(name: "CosmoGraph", package: "MetaverseKit"),
        /* ---------- Apple only libs. ---------- */
        .product(name: "Apple", package: "MetaverseKit", condition: .when(platforms: Arch.OS.apple.platform)),
        /* ---------- Console logging. ---------- */
        .product(name: "Logging", package: "swift-log"),
        .product(name: "Rainbow", package: "Rainbow")
      ] + Arch.OS.dependency(.boost),
      publicHeadersPath: "include",
      cxxSettings: [
        /* ---------- Turn everything on. ---------- */
        .define("PXR_USE_NAMESPACES", to: "1"),
        .define("PXR_PYTHON_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.nix.platform)),
        .define("PXR_PREFER_SAFETY_OVER_SPEED", to: "1"),
        .define("PXR_OCIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_OIIO_PLUGIN_ENABLED", to: "1"),
        .define("PXR_PTEX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_OPENVDB_SUPPORT_ENABLED", to: "1"),
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("PXR_HDF5_SUPPORT_ENABLED", to: "1"),
        /* --------- OSL is temp disabled. --------- */
        .define("PXR_OSL_SUPPORT_ENABLED", to: "0"),
        /* --------- GXAPI build settings. --------- */
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linwin.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
        /* --------- Standard USD defines. --------- */
        .define("MFB_PACKAGE_NAME", to: "Arch"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Arch"),
        .define("MFB_PACKAGE_MODULE", to: "Arch"),
        .define("ARCH_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
        .define("ARCH_COMPILER_MSVC", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Tf",
      dependencies: [
        .target(name: "Arch"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Tf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Tf"),
        .define("MFB_PACKAGE_MODULE", to: "Tf"),
        .define("TF_EXPORTS", to: "1"),
        .headerSearchPath("include/Tf"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Js",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Js"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Js"),
        .define("MFB_PACKAGE_MODULE", to: "Js"),
        .define("JS_EXPORTS", to: "1"),
        .headerSearchPath("include/Js"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Gf",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
      ],
      cxxSettings: [
        .headerSearchPath("include/Gf"),
        .headerSearchPath("include/Gf/nc"),
        .define("MFB_PACKAGE_NAME", to: "Gf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Gf"),
        .define("MFB_PACKAGE_MODULE", to: "Gf"),
        .define("GF_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Trace",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Js"),
      ],
      cxxSettings: [
        /* --------- Fix missing TBB allocator funcs. --------- */
        .define("TBB_ALLOCATOR_TRAITS_BROKEN", to: "1", .when(platforms: Arch.OS.linux.platform)),
        /* --------- Standard USD source definitions. --------- */
        .define("MFB_PACKAGE_NAME", to: "Trace"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Trace"),
        .define("MFB_PACKAGE_MODULE", to: "Trace"),
        .define("TRACE_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Vt",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Vt"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Vt"),
        .define("MFB_PACKAGE_MODULE", to: "Vt"),
        .define("VT_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Work",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Work"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Work"),
        .define("MFB_PACKAGE_MODULE", to: "Work"),
        .define("WORK_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Pegtl",
      dependencies: [
        .target(name: "Arch")
      ],
      cxxSettings: [
        .headerSearchPath("include/Pegtl"),
        .define("MFB_PACKAGE_NAME", to: "Pegtl"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Pegtl"),
        .define("MFB_PACKAGE_MODULE", to: "Pegtl"),
        .define("PEGTL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Plug",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Js"),
        .target(name: "Trace"),
        .target(name: "Work"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Plug"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Plug"),
        .define("MFB_PACKAGE_MODULE", to: "Plug"),
        .define("PLUG_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Ar",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Js"),
        .target(name: "Plug"),
        .target(name: "Vt"),
      ],
      resources: [
        .process("Resources"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Ar"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Ar"),
        .define("MFB_PACKAGE_MODULE", to: "Ar"),
        .define("AR_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Kind",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Plug"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Kind"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Kind"),
        .define("MFB_PACKAGE_MODULE", to: "Kind"),
        .define("KIND_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Sdf",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Plug"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Ar"),
        .target(name: "Pegtl"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Sdf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Sdf"),
        .define("MFB_PACKAGE_MODULE", to: "Sdf"),
        .define("SDF_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
        .define("YY_NO_UNISTD_H", .when(platforms: [.windows]))
      ]
    ),

    .target(
      name: "Pcp",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Pcp"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Pcp"),
        .define("MFB_PACKAGE_MODULE", to: "Pcp"),
        .define("PCP_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Usd",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Gf"),
        .target(name: "Kind"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Pcp"),
      ],
      resources: [
        .copy("codegenTemplates"),
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Usd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Usd"),
        .define("MFB_PACKAGE_MODULE", to: "Usd"),
        .define("USD_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Ndr",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Ar"),
        .target(name: "Sdf")
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Ndr"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Ndr"),
        .define("MFB_PACKAGE_MODULE", to: "Ndr"),
        .define("NDR_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Sdr",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Ndr"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Sdr"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Sdr"),
        .define("MFB_PACKAGE_MODULE", to: "Sdr"),
        .define("SDR_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdGeom",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Gf"),
        .target(name: "Kind"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Pcp"),
        .target(name: "Usd"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdGeom"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdGeom"),
        .define("MFB_PACKAGE_MODULE", to: "UsdGeom"),
        .define("USDGEOM_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdShade",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "Ndr"),
        .target(name: "Sdr"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdShade"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdShade"),
        .define("MFB_PACKAGE_MODULE", to: "UsdShade"),
        .define("USDSHADE_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdShaders",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Ar"),
        .target(name: "Ndr"),
        .target(name: "Sdr"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdShaders"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdShaders"),
        .define("MFB_PACKAGE_MODULE", to: "UsdShaders"),
        .define("USDSHADERS_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdLux",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "Ndr"),
        .target(name: "Sdr"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdLux"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdLux"),
        .define("MFB_PACKAGE_MODULE", to: "UsdLux"),
        .define("USDLUX_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdHydra",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Ar"),
        .target(name: "Tf"),
        .target(name: "Plug"),
        .target(name: "Ndr"),
        .target(name: "Usd"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdHydra"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdHydra"),
        .define("MFB_PACKAGE_MODULE", to: "UsdHydra"),
        .define("USDHYDRA_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "SdrOsl",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Ar"),
        .target(name: "Ndr"),
        .target(name: "Sdr"),
        .target(name: "Vt"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "SdrOsl"),
        .define("MFB_ALT_PACKAGE_NAME", to: "SdrOsl"),
        .define("MFB_PACKAGE_MODULE", to: "SdrOsl"),
        .define("SDROSL_EXPORTS", to: "1"),
        .define("PXR_OSL_SUPPORT_ENABLED", to: "0"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdAbc",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdAbc"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdAbc"),
        .define("MFB_PACKAGE_MODULE", to: "UsdAbc"),
        .define("USDABC_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdDraco",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdDraco"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdDraco"),
        .define("MFB_PACKAGE_MODULE", to: "UsdDraco"),
        .define("USDDRACO_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdMedia",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdMedia"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdMedia"),
        .define("MFB_PACKAGE_MODULE", to: "UsdMedia"),
        .define("USDMEDIA_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdMtlx",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Trace"),
        .target(name: "Ar"),
        .target(name: "Ndr"),
        .target(name: "Sdf"),
        .target(name: "Sdr"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
        .target(name: "UsdUI"),
        .target(name: "UsdUtils"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdMtlx"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdMtlx"),
        .define("MFB_PACKAGE_MODULE", to: "UsdMtlx"),
        .define("USDMTLX_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdPhysics",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Plug"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdPhysics"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdPhysics"),
        .define("MFB_PACKAGE_MODULE", to: "UsdPhysics"),
        .define("USDPHYSICS_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdProc",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdProc"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdProc"),
        .define("MFB_PACKAGE_MODULE", to: "UsdProc"),
        .define("USDPROC_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdRender",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdRender"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdRender"),
        .define("MFB_PACKAGE_MODULE", to: "UsdRender"),
        .define("USDRENDER_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdRi",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdRi"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdRi"),
        .define("MFB_PACKAGE_MODULE", to: "UsdRi"),
        .define("USDRI_EXPORTS", to: "1"),
        .headerSearchPath("include/UsdRi"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdSkel",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),

      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdSkel"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdSkel"),
        .define("MFB_PACKAGE_MODULE", to: "UsdSkel"),
        .define("USDSKEL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdUI",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdUI"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdUI"),
        .define("MFB_PACKAGE_MODULE", to: "UsdUI"),
        .define("USDUI_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdUtils",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Work"),
        .target(name: "Trace"),
        .target(name: "Plug"),
        .target(name: "Ar"),
        .target(name: "Kind"),
        .target(name: "Pcp"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdUtils"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdUtils"),
        .define("MFB_PACKAGE_MODULE", to: "UsdUtils"),
        .define("USDUTILS_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdVol",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Plug"),
        .target(name: "Work"),
        .target(name: "Vt"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdVol"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdVol"),
        .define("MFB_PACKAGE_MODULE", to: "UsdVol"),
        .define("USDVOL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "CameraUtil",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "CameraUtil"),
        .define("MFB_ALT_PACKAGE_NAME", to: "CameraUtil"),
        .define("MFB_PACKAGE_MODULE", to: "CameraUtil"),
        .define("CAMERAUTIL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Hf",
      dependencies: [
        .target(name: "Plug"),
        .target(name: "Tf"),
        .target(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hf"),
        .define("MFB_PACKAGE_MODULE", to: "Hf"),
        .define("HF_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "PxOsd",
      dependencies: [
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "PxOsd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "PxOsd"),
        .define("MFB_PACKAGE_MODULE", to: "PxOsd"),
        .define("PXOSD_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Hd",
      dependencies: [
        .target(name: "Plug"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Work"),
        .target(name: "Sdf"),
        .target(name: "Sdr"),
        .target(name: "CameraUtil"),
        .target(name: "Hf"),
        .target(name: "PxOsd"),
      ],
      resources: [
        .process("Resources"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hd"),
        .define("MFB_PACKAGE_MODULE", to: "Hd"),
        .define("HD_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Garch",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
      ],
      cxxSettings: [
        .define("PXR_GL_SUPPORT_ENABLED", .when(platforms: Arch.OS.noembeddedapple.platform)),
        .define("MFB_PACKAGE_NAME", to: "Garch"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Garch"),
        .define("MFB_PACKAGE_MODULE", to: "Garch"),
        .define("GARCH_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      linkerSettings: [
        .linkedFramework("OpenGL", .when(platforms: [.macOS])),
        .linkedFramework("UIKit", .when(platforms: Arch.OS.embeddedapple.platform)),
        .linkedLibrary("glut", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("GL", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("GLU", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("m", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("X11", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("Xt", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("opengl32", .when(platforms: Arch.OS.windows.platform)),
      ]
    ),

    .target(
      name: "Hgi",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Plug"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hgi"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hgi"),
        .define("MFB_PACKAGE_MODULE", to: "Hgi"),
        .define("HGI_EXPORTS", to: "1"),
        // enable when swift supports std.unique_ptr
        .define("SWIFT_HAS_UNIQUE_PTR", to: "0"),
        .define("PXR_GL_SUPPORT_ENABLED", .when(platforms: Arch.OS.noembeddedapple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linwin.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HgiMetal",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Hgi"),
        .target(name: "Vt"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HgiMetal"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HgiMetal"),
        .define("MFB_PACKAGE_MODULE", to: "HgiMetal"),
        .define("HGIMETAL_EXPORTS", to: "1"),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linwin.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      linkerSettings: [
        .linkedFramework("Foundation", .when(platforms: Arch.OS.apple.platform)),
        .linkedFramework("Metal", .when(platforms: Arch.OS.apple.platform)),
        .linkedFramework("AppKit", .when(platforms: [.macOS])),
        .linkedFramework("UIKit", .when(platforms: Arch.OS.embeddedapple.platform)),
      ]
    ),

    // .target(
    //   name: "HgiVulkan",
    //   dependencies: [
    //     .target(name: "Arch"),
    //     .target(name: "Tf"),
    //     .target(name: "Trace"),
    //     .target(name: "Hgi"),
    //   ],
    //   resources: [
    //     .process("Resources")
    //   ],
    //   cxxSettings: [
    //     .define("MFB_PACKAGE_NAME", to: "HgiVulkan"),
    //     .define("MFB_ALT_PACKAGE_NAME", to: "HgiVulkan"),
    //     .define("MFB_PACKAGE_MODULE", to: "HgiVulkan"),
    //     .define("HGIVULKAN_EXPORTS", to: "1"),
    //     .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
    //     .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linwin.platform)),
    //     .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
    //   ]
    // ),

    .target(
      name: "HgiGL",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Garch"),
        .target(name: "Hgi"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HgiGL"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HgiGL"),
        .define("MFB_PACKAGE_MODULE", to: "HgiGL"),
        .define("HGIGL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HgiInterop",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Gf"),
        .target(name: "Garch"),
        .target(name: "Hgi"),
        .target(name: "HgiMetal", condition: .when(platforms: Arch.OS.apple.platform)),
        // .target(name: "HgiVulkan", condition: .when(platforms: Arch.OS.linux.platform)),
        .target(name: "HgiGL", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HgiInterop"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HgiInterop"),
        .define("MFB_PACKAGE_MODULE", to: "HgiInterop"),
        .define("HGIINTEROP_EXPORTS", to: "1"),
        .define("PXR_GL_SUPPORT_ENABLED", .when(platforms: Arch.OS.noembeddedapple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linwin.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      linkerSettings: [
        .linkedFramework("Foundation", .when(platforms: Arch.OS.apple.platform)),
        .linkedFramework("CoreVideo", .when(platforms: Arch.OS.apple.platform))
      ]
    ),

    .target(
      name: "Hio",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Js"),
        .target(name: "Plug"),
        .target(name: "Tf"),
        .target(name: "Vt"),
        .target(name: "Trace"),
        .target(name: "Ar"),
        .target(name: "Hf"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hio"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hio"),
        .define("MFB_PACKAGE_MODULE", to: "Hio"),
        .define("HIO_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Glf",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Plug"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Trace"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Garch"),
        .target(name: "Hf"),
        .target(name: "Hio"),
      ],
      resources: [
        .copy("shaders"),
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Glf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Glf"),
        .define("MFB_PACKAGE_MODULE", to: "Glf"),
        .define("GLF_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      linkerSettings: [
        .linkedFramework("OpenGL", .when(platforms: [.macOS])),
      ]
    ),

    .target(
      name: "GeomUtil",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "PxOsd"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "GeomUtil"),
        .define("MFB_ALT_PACKAGE_NAME", to: "GeomUtil"),
        .define("MFB_PACKAGE_MODULE", to: "GeomUtil"),
        .define("GEOMUTIL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HdSi",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Plug"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Work"),
        .target(name: "Sdf"),
        .target(name: "CameraUtil"),
        .target(name: "GeomUtil"),
        .target(name: "Hf"),
        .target(name: "Hd"),
        .target(name: "PxOsd"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HdSi"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HdSi"),
        .define("MFB_PACKAGE_MODULE", to: "HdSi"),
        .define("HDSI_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HdMtlx",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Gf"),
        .target(name: "Hd"),
        .target(name: "Sdf"),
        .target(name: "Sdr"),
        .target(name: "UsdMtlx")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HdMtlx"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HdMtlx"),
        .define("MFB_PACKAGE_MODULE", to: "HdMtlx"),
        .define("HDMTLX_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HdSt",
      dependencies: [
        .target(name: "Hio"),
        .target(name: "Garch"),
        .target(name: "Glf"),
        .target(name: "Hd"),
        .target(name: "HdSi"),
        .target(name: "HgiGL", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "HgiInterop"),
        .target(name: "Sdr"),
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Trace"),
        .target(name: "HdMtlx"),
      ],
      resources: [
        .copy("shaders"),
        .copy("textures"),
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HdSt"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HdSt"),
        .define("MFB_PACKAGE_MODULE", to: "HdSt"),
        .define("HDST_EXPORTS", to: "1"),
        .define("PXR_MATERIALX_SUPPORT_ENABLED", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HdStorm",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Plug"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Work"),
        .target(name: "Hd"),
        .target(name: "HdSt", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HdStorm"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HdStorm"),
        .define("MFB_PACKAGE_MODULE", to: "HdStorm"),
        .define("HDSTORM_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "Hdx",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Work"),
        .target(name: "Sdf"),
        .target(name: "Garch"),
        .target(name: "Glf"),
        .target(name: "PxOsd"),
        .target(name: "Hd"),
        .target(name: "HdSt", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "Hgi"),
        .target(name: "HgiInterop"),
        .target(name: "CameraUtil"),
      ],
      resources: [
        .copy("shaders"),
        .copy("textures"),
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hdx"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hdx"),
        .define("MFB_PACKAGE_MODULE", to: "Hdx"),
        .define("HDX_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "HdAr",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Hd"),
        .target(name: "Ar"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HdAr"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HdAr"),
        .define("MFB_PACKAGE_MODULE", to: "HdAr"),
        .define("HDAR_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdImaging",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "GeomUtil"),
        .target(name: "Hd"),
        .target(name: "HdAr"),
        .target(name: "Hio"),
        .target(name: "PxOsd"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdLux"),
        .target(name: "UsdRender"),
        .target(name: "UsdShade"),
        .target(name: "UsdVol"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdImaging"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdImaging"),
        .define("MFB_PACKAGE_MODULE", to: "UsdImaging"),
        .define("USDIMAGING_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .target(
      name: "UsdImagingGL",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Gf"),
        .target(name: "Vt"),
        .target(name: "Plug"),
        .target(name: "Trace"),
        .target(name: "Work"),
        .target(name: "Hio"),
        .target(name: "Garch"),
        .target(name: "Glf"),
        .target(name: "Hd"),
        .target(name: "HdSi"),
        .target(name: "Hdx", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "Hgi"),
        .target(name: "PxOsd"),
        .target(name: "Ar"),
        .target(name: "Sdf"),
        .target(name: "Sdr"),
        .target(name: "Usd"),
        .target(name: "UsdGeom"),
        .target(name: "UsdHydra"),
        .target(name: "UsdShade"),
        .target(name: "UsdImaging"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdImagingGL"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdImagingGL"),
        .define("MFB_PACKAGE_MODULE", to: "UsdImagingGL"),
        .define("USDIMAGINGGL_EXPORTS", to: "1"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ]
    ),

    .executableTarget(
      name: "UsdView",
      dependencies: [
        .target(name: "PixarUSD"),
      ],
      cxxSettings: [
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),

    .executableTarget(
      name: "OpenUSD",
      dependencies: [
        .product(name: "Version", package: "Version"),
        .product(name: "ArgumentParser", package: "swift-argument-parser"),
        .product(name: "Logging", package: "swift-log"),
        .product(name: "Rainbow", package: "Rainbow")
      ],
      resources: [
        // usd source files that need modifications to work with swift are maintained out of these
        // directories, if a usd source file from upstream pixar is matching any of the respective
        // target/filename(.h|.cpp) patterns within any of these resource directories, the contents
        // of each of the matching upstream pixar files will have their contents replaced with each
        // of the respective source code files found in any of these directories.
        .copy("Resources/Work")
      ],
      cxxSettings: [
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      swiftSettings: [
        .enableUpcomingFeature("BareSlashRegexLiterals"),
      ]
    ),

    .plugin(
      name: "OpenUSDPlugin",
      capability: .command(
        intent: .custom(verb: "openusd", description: """
          Update the version of USD in the current package,
          this will fetch the latest version of USD from the
          Pixar USD repository and update this packages source
          code to the latest version.
          """),
        permissions: [
          .allowNetworkConnections(
            scope: .all(),
            reason: "Updating USD requires network access."
          ),
          .writeToPackageDirectory(
            reason: "Updating USD requires write access."
          ),
        ]
      ),
      dependencies: [
        .target(name: "OpenUSD")
      ]
    ),

    .plugin(
      name: "UsdGenSchemaPlugin",
      capability: .command(
        intent: .custom(verb: "genschema", description: """
          Customize and extend the layers of specific named API atop
          the underlying scene graph with schema definitions defined
          by prims, their properties, and (optionally) their default
          or fallback values.

          The schema definition files are written in a simple, human
          readable, text-based markup language from the (.usda) file
          format. The files are then processed with this plugin tool
          to generate their corresponding C++, Python, and Swift API
          code.

          The generated C++, Python, and Swift code are then sent to
          the compiler to generate their corresponding API code, and
          made available to the USD runtime. Where it can be used to
          bring the schema definition to life, and make it available
          to the end user for use in their own applications, plugins
          and tools.
          """),
        permissions: [
          .allowNetworkConnections(
            scope: .all(),
            reason: "Pixar.Ar may require network access to load assets."
          ),
          .writeToPackageDirectory(
            reason: "Generation of schema code requires write access."
          ),
        ]
      )
    ),

    .macro(
      name: "PixarMacros",
      dependencies: [
        .product(name: "SwiftSyntaxMacros", package: "swift-syntax"),
        .product(name: "SwiftCompilerPlugin", package: "swift-syntax"),
      ]
    ),

    // .target(
    //   name: "rust-usd",
    //   dependencies: [
    //     .product(name: "Ptex", package: "MetaverseKit"),
    //     .target(name: "pxr"),
    //   ],
    //   swiftSettings: [
    //     .interoperabilityMode(.Cxx),
    //   ]
    // ),

    .target(
      name: "PixarUSD",
      dependencies: [
        // ---------- base. ------
        .target(name: "Arch"),
        .target(name: "Tf"),
        .target(name: "Js"),
        .target(name: "Gf"),
        .target(name: "Trace"),
        .target(name: "Vt"),
        .target(name: "Work"),
        .target(name: "Pegtl"),
        .target(name: "Plug"),
        // ----------- usd. ------
        .target(name: "Ar"),
        .target(name: "Kind"),
        .target(name: "Sdf"),
        .target(name: "Pcp"),
        .target(name: "Usd"),
        .target(name: "Ndr"),
        .target(name: "Sdr"),
        .target(name: "SdrOsl"),
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
        .target(name: "UsdLux"),
        .target(name: "UsdHydra"),
        .target(name: "UsdAbc", condition: .when(platforms: Arch.OS.nix.platform)),
        .target(name: "UsdDraco"),
        .target(name: "UsdMedia"),
        .target(name: "UsdMtlx"),
        .target(name: "UsdPhysics"),
        .target(name: "UsdProc"),
        .target(name: "UsdRender"),
        .target(name: "UsdRi"),
        .target(name: "UsdSkel"),
        .target(name: "UsdUI"),
        .target(name: "UsdUtils"),
        .target(name: "UsdVol"),
        // ------- imaging. ------
        .target(name: "CameraUtil"),
        .target(name: "Garch"),
        .target(name: "GeomUtil"),
        .target(name: "Glf"),
        .target(name: "Hf"),
        .target(name: "Hd"),
        .target(name: "HdAr"),
        .target(name: "HdMtlx"),
        .target(name: "HdSi"),
        .target(name: "HdSt", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "HdStorm", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "Hdx", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "Hgi"),
        .target(name: "HgiMetal", condition: .when(platforms: Arch.OS.apple.platform)),
        // .target(name: "HgiVulkan", condition: .when(platforms: Arch.OS.linux.platform)),
        .target(name: "HgiGL", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        .target(name: "HgiInterop"),
        .target(name: "Hio"),
        .target(name: "PxOsd"),
        // --- usd imaging. ------
        .target(name: "UsdShaders"),
        .target(name: "UsdImaging"),
        .target(name: "UsdImagingGL", condition: .when(platforms: Arch.OS.noembeddedapple.platform)),
        // -------- macros. ------
        .target(name: "PixarMacros"),
        // -----------------------
      ],
      cxxSettings: [
        // enable to debug swift retain/release calls.
        .define("DEBUG_MEMORY_MANAGEMENT", to: "0"),
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      swiftSettings: [
        // enable to debug bundled (python, plugins, resources).
        .define("DEBUG_PIXAR_BUNDLE"),
        .interoperabilityMode(.Cxx),
      ]
    ),

    .executableTarget(
      name: "Examples",
      dependencies: galahTargetDeps,
      cxxSettings: [
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      swiftSettings: galahSettings
    ),

    .testTarget(
      name: "PixarUSDTests",
      dependencies: [
        .target(name: "PixarUSD"),
      ],
      cxxSettings: [
        .define("_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH", .when(platforms: [.windows])),
      ],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
      ]
    ),
  ],
  cxxLanguageStandard: .cxx17
)

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
    /// apple devices (macOS, visionOS, iOS, etc).
    case apple
    /// linux distros (ubuntu, centos, etc).
    case linux
    /// microsoft windows.
    case windows
    /// web (wasm).
    case web
    /// everything not windows (apple + linux).
    case nix
    /// everything not linux (apple + windows).
    case applewindows
    /// everything not apple (linux + windows).
    case linwin
    /// only embedded apple devices.
    case embeddedapple
    /// everything not embedded apple devices.
    case noembeddedapple

    public var platform: [Platform]
    {
      switch self
      {
        case .apple: [.macOS, .iOS, .visionOS, .tvOS, .watchOS]
        case .linux: [.linux, .android, .openbsd]
        case .windows: [.windows]
        case .web: [.wasi]
        case .nix: [.macOS, .iOS, .visionOS, .tvOS, .watchOS, .linux, .android, .openbsd]
        case .applewindows: [.macOS, .iOS, .visionOS, .tvOS, .watchOS, .windows]
        case .linwin: [.linux, .android, .openbsd, .windows]
        case .embeddedapple: [.iOS, .visionOS, .tvOS, .watchOS]
        case .noembeddedapple: [.macOS, .linux, .android, .openbsd, .windows]
      }
    }

    public static func dependency(_ dependency: Dependency) -> [Target.Dependency]
    {
      #if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
        [dependency.product(for: .apple)].compactMap { $0 }
      #elseif os(Linux) || os(Android) || os(OpenBSD) || os(FreeBSD)
        [dependency.product(for: .linux)].compactMap { $0 }
      #elseif os(Windows) || os(Cygwin)
        [dependency.product(for: .windows)].compactMap { $0 }
      #elseif os(WASI)
        [dependency.product(for: .web)].compactMap { $0 }
      #else
        []
      #endif
    }

    enum Dependency
    {
      case boost

      public func product(for os: OS) -> Target.Dependency?
      {
        switch self
        {
          case .boost:
            switch os
            {
              case .apple: .product(name: "Boost", package: "MetaverseKit")
              default: nil
            }
        }
      }
    }

    enum Python
    {
      public static func targets(enabled: Bool = false) -> [Target]
      {
        if enabled
        {
          [
            .target(
              name: "PyTf",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyTf",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Tf"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Tf"),
                .define("MFB_PACKAGE_MODULE", to: "Tf"),
              ]
            ),

            .target(
              name: "PyGf",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyGf",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Gf"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Gf"),
                .define("MFB_PACKAGE_MODULE", to: "Gf"),
              ]
            ),

            .target(
              name: "PyTrace",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyTrace",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Trace"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Trace"),
                .define("MFB_PACKAGE_MODULE", to: "Trace"),
              ]
            ),

            .target(
              name: "PyVt",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyVt",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Vt"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Vt"),
                .define("MFB_PACKAGE_MODULE", to: "Vt"),
              ]
            ),

            .target(
              name: "PyWork",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyWork",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Work"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Work"),
                .define("MFB_PACKAGE_MODULE", to: "Work"),
              ]
            ),

            .target(
              name: "PyPlug",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyPlug",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Plug"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Plug"),
                .define("MFB_PACKAGE_MODULE", to: "Plug"),
              ]
            ),

            .target(
              name: "PyAr",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyAr",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Ar"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Ar"),
                .define("MFB_PACKAGE_MODULE", to: "Ar"),
              ]
            ),

            .target(
              name: "PyKind",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyKind",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Kind"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Kind"),
                .define("MFB_PACKAGE_MODULE", to: "Kind"),
              ]
            ),

            .target(
              name: "PySdf",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PySdf",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Sdf"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Sdf"),
                .define("MFB_PACKAGE_MODULE", to: "Sdf"),
              ]
            ),

            .target(
              name: "PyPcp",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyPcp",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Pcp"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Pcp"),
                .define("MFB_PACKAGE_MODULE", to: "Pcp"),
              ]
            ),

            .target(
              name: "PyUsd",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsd",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Usd"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Usd"),
                .define("MFB_PACKAGE_MODULE", to: "Usd"),
              ]
            ),

            .target(
              name: "PyNdr",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyNdr",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Ndr"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Ndr"),
                .define("MFB_PACKAGE_MODULE", to: "Ndr"),
              ]
            ),

            .target(
              name: "PySdr",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PySdr",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Sdr"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Sdr"),
                .define("MFB_PACKAGE_MODULE", to: "Sdr"),
              ]
            ),

            .target(
              name: "PyUsdGeom",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdGeom",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdGeom"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdGeom"),
                .define("MFB_PACKAGE_MODULE", to: "UsdGeom"),
              ]
            ),

            .target(
              name: "PyUsdShade",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdShade",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdShade"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdShade"),
                .define("MFB_PACKAGE_MODULE", to: "UsdShade"),
              ]
            ),

            .target(
              name: "PyUsdLux",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdLux",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdLux"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdLux"),
                .define("MFB_PACKAGE_MODULE", to: "UsdLux"),
              ]
            ),

            .target(
              name: "PyUsdHydra",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdHydra",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdHydra"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdHydra"),
                .define("MFB_PACKAGE_MODULE", to: "UsdHydra"),
              ]
            ),

            .target(
              name: "PySdrOsl",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PySdrOsl",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "SdrOsl"),
                .define("MFB_ALT_PACKAGE_NAME", to: "SdrOsl"),
                .define("MFB_PACKAGE_MODULE", to: "SdrOsl"),
                .define("PXR_OSL_SUPPORT_ENABLED", to: "0"),
              ]
            ),

            .target(
              name: "PyUsdAbc",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdAbc",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdAbc"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdAbc"),
                .define("MFB_PACKAGE_MODULE", to: "UsdAbc"),
              ]
            ),

            .target(
              name: "PyUsdDraco",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdDraco",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdDraco"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdDraco"),
                .define("MFB_PACKAGE_MODULE", to: "UsdDraco"),
              ]
            ),

            .target(
              name: "PyUsdMedia",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdMedia",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdMedia"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdMedia"),
                .define("MFB_PACKAGE_MODULE", to: "UsdMedia"),
              ]
            ),

            .target(
              name: "PyUsdMtlx",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdMtlx",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdMtlx"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdMtlx"),
                .define("MFB_PACKAGE_MODULE", to: "UsdMtlx"),
              ]
            ),

            .target(
              name: "PyUsdPhysics",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdPhysics",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdPhysics"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdPhysics"),
                .define("MFB_PACKAGE_MODULE", to: "UsdPhysics"),
              ]
            ),

            .target(
              name: "PyUsdProc",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdProc",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdProc"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdProc"),
                .define("MFB_PACKAGE_MODULE", to: "UsdProc"),
              ]
            ),

            .target(
              name: "PyUsdRender",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdRender",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdRender"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdRender"),
                .define("MFB_PACKAGE_MODULE", to: "UsdRender"),
              ]
            ),

            .target(
              name: "PyUsdRi",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdRi",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdRi"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdRi"),
                .define("MFB_PACKAGE_MODULE", to: "UsdRi"),
              ]
            ),

            .target(
              name: "PyUsdSkel",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdSkel",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdSkel"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdSkel"),
                .define("MFB_PACKAGE_MODULE", to: "UsdSkel"),
              ]
            ),

            .target(
              name: "PyUsdUI",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdUI",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdUI"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdUI"),
                .define("MFB_PACKAGE_MODULE", to: "UsdUI"),
              ]
            ),

            .target(
              name: "PyUsdUtils",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdUtils",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdUtils"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdUtils"),
                .define("MFB_PACKAGE_MODULE", to: "UsdUtils"),
              ]
            ),

            .target(
              name: "PyUsdVol",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdVol",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdVol"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdVol"),
                .define("MFB_PACKAGE_MODULE", to: "UsdVol"),
              ]
            ),

            .target(
              name: "PyUsdShaders",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyUsdShaders",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "UsdShaders"),
                .define("MFB_ALT_PACKAGE_NAME", to: "UsdShaders"),
                .define("MFB_PACKAGE_MODULE", to: "UsdShaders"),
              ]
            ),

            .target(
              name: "PyCameraUtil",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyCameraUtil",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "CameraUtil"),
                .define("MFB_ALT_PACKAGE_NAME", to: "CameraUtil"),
                .define("MFB_PACKAGE_MODULE", to: "CameraUtil"),
              ]
            ),

            .target(
              name: "PyPxOsd",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyPxOsd",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "PxOsd"),
                .define("MFB_ALT_PACKAGE_NAME", to: "PxOsd"),
                .define("MFB_PACKAGE_MODULE", to: "PxOsd"),
              ]
            ),

            .target(
              name: "PyGarch",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyGarch",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Garch"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Garch"),
                .define("MFB_PACKAGE_MODULE", to: "Garch"),
              ]
            ),

            .target(
              name: "PyGlf",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyGlf",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "Glf"),
                .define("MFB_ALT_PACKAGE_NAME", to: "Glf"),
                .define("MFB_PACKAGE_MODULE", to: "Glf"),
              ]
            ),

            .target(
              name: "PyGeomUtil",
              dependencies: [
                .target(name: "PixarUSD"),
              ],
              path: "Python/PyGeomUtil",
              resources: [
                .process("Resources"),
              ],
              publicHeadersPath: "include",
              cxxSettings: [
                .define("MFB_PACKAGE_NAME", to: "GeomUtil"),
                .define("MFB_ALT_PACKAGE_NAME", to: "GeomUtil"),
                .define("MFB_PACKAGE_MODULE", to: "GeomUtil")
              ]
            )
          ]
        }
        else
        {
          []
        }
      }

      public static func products(enabled: Bool = false) -> [Product]
      {
        if enabled
        {
          [
            .library(
              name: "PyTf",
              type: .dynamic,
              targets: ["PyTf"]
            ),
            .library(
              name: "PyPlug",
              type: .dynamic,
              targets: ["PyPlug"]
            ),
            .library(
              name: "PyAr",
              type: .dynamic,
              targets: ["PyAr"]
            ),
            .library(
              name: "PyKind",
              type: .dynamic,
              targets: ["PyKind"]
            ),
            .library(
              name: "PyGf",
              type: .dynamic,
              targets: ["PyGf"]
            ),
            .library(
              name: "PyTrace",
              type: .dynamic,
              targets: ["PyTrace"]
            ),
            .library(
              name: "PyVt",
              type: .dynamic,
              targets: ["PyVt"]
            ),
            .library(
              name: "PyWork",
              type: .dynamic,
              targets: ["PyWork"]
            ),
            .library(
              name: "PySdf",
              type: .dynamic,
              targets: ["PySdf"]
            ),
            .library(
              name: "PyPcp",
              type: .dynamic,
              targets: ["PyPcp"]
            ),
            .library(
              name: "PyUsd",
              type: .dynamic,
              targets: ["PyUsd"]
            ),
            .library(
              name: "PyNdr",
              type: .dynamic,
              targets: ["PyNdr"]
            ),
            .library(
              name: "PySdr",
              type: .dynamic,
              targets: ["PySdr"]
            ),
            .library(
              name: "PyUsdGeom",
              type: .dynamic,
              targets: ["PyUsdGeom"]
            ),
            .library(
              name: "PyUsdLux",
              type: .dynamic,
              targets: ["PyUsdLux"]
            ),
            .library(
              name: "PyUsdShade",
              type: .dynamic,
              targets: ["PyUsdShade"]
            ),
            .library(
              name: "PyUsdHydra",
              type: .dynamic,
              targets: ["PyUsdHydra"]
            ),
            .library(
              name: "PySdrOsl",
              type: .dynamic,
              targets: ["PySdrOsl"]
            ),
            .library(
              name: "PyUsdAbc",
              type: .dynamic,
              targets: ["PyUsdAbc"]
            ),
            .library(
              name: "PyUsdDraco",
              type: .dynamic,
              targets: ["PyUsdDraco"]
            ),
            .library(
              name: "PyUsdMedia",
              type: .dynamic,
              targets: ["PyUsdMedia"]
            ),
            .library(
              name: "PyUsdMtlx",
              type: .dynamic,
              targets: ["PyUsdMtlx"]
            ),
            .library(
              name: "PyUsdPhysics",
              type: .dynamic,
              targets: ["PyUsdPhysics"]
            ),
            .library(
              name: "PyUsdProc",
              type: .dynamic,
              targets: ["PyUsdProc"]
            ),
            .library(
              name: "PyUsdRender",
              type: .dynamic,
              targets: ["PyUsdRender"]
            ),
            .library(
              name: "PyUsdRi",
              type: .dynamic,
              targets: ["PyUsdRi"]
            ),
            .library(
              name: "PyUsdSkel",
              type: .dynamic,
              targets: ["PyUsdSkel"]
            ),
            .library(
              name: "PyUsdUI",
              type: .dynamic,
              targets: ["PyUsdUI"]
            ),
            .library(
              name: "PyUsdUtils",
              type: .dynamic,
              targets: ["PyUsdUtils"]
            ),
            .library(
              name: "PyUsdVol",
              type: .dynamic,
              targets: ["PyUsdVol"]
            ),
            .library(
              name: "PyUsdShaders",
              type: .dynamic,
              targets: ["PyUsdShaders"]
            ),
            .library(
              name: "PyCameraUtil",
              type: .dynamic,
              targets: ["PyCameraUtil"]
            ),
            .library(
              name: "PyPxOsd",
              type: .dynamic,
              targets: ["PyPxOsd"]
            ),
            .library(
              name: "PyGarch",
              type: .dynamic,
              targets: ["PyGarch"]
            ),
            .library(
              name: "PyGlf",
              type: .dynamic,
              targets: ["PyGlf"]
            ),
            .library(
              name: "PyGeomUtil",
              type: .dynamic,
              targets: ["PyGeomUtil"]
            ),
          ]
        }
        else
        {
          []
        }
      }

      public static func all(enabled: Bool = false) -> [String]
      {
        if enabled
        {
          [
            "PyTf",
            "PyGf",
            "PyTrace",
            "PyVt",
            "PyWork",
            "PyPlug",
            "PyAr",
            "PyKind",
            "PySdf",
            "PyPcp",
            "PyUsd",
            "PyNdr",
            "PySdr",
            "PySdrOsl",
            "PyUsdGeom",
            "PyUsdShade",
            "PyUsdLux",
            "PyUsdHydra",
            "PyUsdAbc",
            "PyUsdDraco",
            "PyUsdMedia",
            "PyUsdMtlx",
            "PyUsdPhysics",
            "PyUsdProc",
            "PyUsdRender",
            "PyUsdRi",
            "PyUsdSkel",
            "PyUsdUI",
            "PyUsdUtils",
            "PyUsdVol",
            "PyCameraUtil",
            "PyPxOsd",
            "PyGarch",
            "PyGeomUtil",
            "PyGlf",
            "PyUsdShaders",
          ]
        }
        else
        {
          []
        }
      }
    }
  }
}

struct Galah
{
  /**
   * hacky way to detect if swift 6 might be available on your platform,
   * sadly there is no other way since swiftpm got even more restrictive
   * by not allowing executables to be called via Process() inside swift
   * package manifests anymore, as this now errors with a lovely output
   * of: ["error: permissionDenied\n"], so we cannot just simply call
   * 'swift --version' either. */
  init(supported: Bool = false)
  {
    var withGalah = supported

    // if we are on these platforms, we are on swift 6, enable galah.
    #if os(macOS)
      if #available(macOS 15, visionOS 2, iOS 18, tvOS 18, watchOS 18, *)
      {
        withGalah = true
      }
    #endif

    // if swift is version 6 or later, enable galah. need to check how
    // this preprocesses if linux has swift 6.0 installed (we want to
    // continue to allow a minimum swift-tools-version of 5.10, while
    // opening up features for later swift versions, if available).
    #if swift(>=6.0)
      withGalah = true
    #endif /* swift(>=6.0) */

    if withGalah { Galah.enableGalah() }
  }

  static func enableGalah()
  {
    galahDeps = [.package(url: "https://github.com/wabiverse/galah.git", from: "1.0.1")]
    galahSettings = [.interoperabilityMode(.Cxx), .define("WITH_GALAH")]
    galahTargetDeps = [.target(name: "PixarUSD"), .product(name: "GalahInterpreter", package: "galah")]
  }
}
