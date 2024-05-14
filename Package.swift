// swift-tools-version: 5.10
import CompilerPluginSupport
import PackageDescription

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
      type: .dynamic,
      targets: ["Arch"]
    ),
    .library(
      name: "Tf",
      type: .dynamic,
      targets: ["Tf"]
    ),
    .library(
      name: "Js",
      type: .dynamic,
      targets: ["Js"]
    ),
    .library(
      name: "Gf",
      type: .dynamic,
      targets: ["Gf"]
    ),
    .library(
      name: "Trace",
      type: .dynamic,
      targets: ["Trace"]
    ),
    .library(
      name: "Vt",
      type: .dynamic,
      targets: ["Vt"]
    ),
    .library(
      name: "Work",
      type: .dynamic,
      targets: ["Work"]
    ),
    .library(
      name: "Plug",
      type: .dynamic,
      targets: ["Plug"]
    ),
    // ------------ Pixar.Usd -----
    .library(
      name: "Ar",
      type: .dynamic,
      targets: ["Ar"]
    ),
    .library(
      name: "Kind",
      type: .dynamic,
      targets: ["Kind"]
    ),
    .library(
      name: "Sdf",
      type: .dynamic,
      targets: ["Sdf"]
    ),
    .library(
      name: "Pcp",
      type: .dynamic,
      targets: ["Pcp"]
    ),
    .library(
      name: "Usd",
      type: .dynamic,
      targets: ["Usd"]
    ),
    .library(
      name: "Ndr",
      type: .dynamic,
      targets: ["Ndr"]
    ),
    .library(
      name: "Sdr",
      type: .dynamic,
      targets: ["Sdr"]
    ),
    .library(
      name: "UsdGeom",
      type: .dynamic,
      targets: ["UsdGeom"]
    ),
    .library(
      name: "UsdShade",
      type: .dynamic,
      targets: ["UsdShade"]
    ),
    .library(
      name: "UsdLux",
      type: .dynamic,
      targets: ["UsdLux"]
    ),
    .library(
      name: "UsdHydra",
      type: .dynamic,
      targets: ["UsdHydra"]
    ),
    .library(
      name: "SdrOsl",
      type: .dynamic,
      targets: ["SdrOsl"]
    ),
    .library(
      name: "UsdAbc",
      type: .dynamic,
      targets: ["UsdAbc"]
    ),
    .library(
      name: "UsdDraco",
      type: .dynamic,
      targets: ["UsdDraco"]
    ),
    .library(
      name: "UsdMedia",
      type: .dynamic,
      targets: ["UsdMedia"]
    ),
    .library(
      name: "UsdMtlx",
      type: .dynamic,
      targets: ["UsdMtlx"]
    ),
    .library(
      name: "UsdPhysics",
      type: .dynamic,
      targets: ["UsdPhysics"]
    ),
    .library(
      name: "UsdProc",
      type: .dynamic,
      targets: ["UsdProc"]
    ),
    .library(
      name: "UsdRender",
      type: .dynamic,
      targets: ["UsdRender"]
    ),
    .library(
      name: "UsdRi",
      type: .dynamic,
      targets: ["UsdRi"]
    ),
    .library(
      name: "UsdSkel",
      type: .dynamic,
      targets: ["UsdSkel"]
    ),
    .library(
      name: "UsdUI",
      type: .dynamic,
      targets: ["UsdUI"]
    ),
    .library(
      name: "UsdUtils",
      type: .dynamic,
      targets: ["UsdUtils"]
    ),
    .library(
      name: "UsdVol",
      type: .dynamic,
      targets: ["UsdVol"]
    ),
    // -------- Pixar.Imaging -----
    .library(
      name: "CameraUtil",
      type: .dynamic,
      targets: ["CameraUtil"]
    ),
    .library(
      name: "Hf",
      type: .dynamic,
      targets: ["Hf"]
    ),
    .library(
      name: "PxOsd",
      type: .dynamic,
      targets: ["PxOsd"]
    ),
    .library(
      name: "Hd",
      type: .dynamic,
      targets: ["Hd"]
    ),
    .library(
      name: "Garch",
      type: .dynamic,
      targets: ["Garch"]
    ),
    .library(
      name: "Hgi",
      type: .dynamic,
      targets: ["Hgi"]
    ),
    .library(
      name: "HgiMetal",
      type: .dynamic,
      targets: ["HgiMetal"]
    ),
    // .library(
    //   name: "HgiVulkan",
    //   targets: ["HgiVulkan"]
    // ),
    .library(
      name: "HgiGL",
      type: .dynamic,
      targets: ["HgiGL"]
    ),
    .library(
      name: "HgiInterop",
      type: .dynamic,
      targets: ["HgiInterop"]
    ),
    .library(
      name: "Hio",
      type: .dynamic,
      targets: ["Hio"]
    ),
    .library(
      name: "Glf",
      type: .dynamic,
      targets: ["Glf"]
    ),
    .library(
      name: "GeomUtil",
      type: .dynamic,
      targets: ["GeomUtil"]
    ),
    // ----- Pixar.UsdImaging -----
    .library(
      name: "UsdShaders",
      type: .dynamic,
      targets: ["UsdShaders"]
    ),
    // ----------------- Apps -----
    .executable(
      name: "UsdView",
      targets: ["UsdView"]
    ),
    // -------- Swift Plugins -----
    .plugin(
      name: "UsdGenSchemaPlugin",
      targets: ["UsdGenSchemaPlugin"]
    ),
    // ------- Monolithic USD -----
    .library(
      name: "PixarUSD",
      targets: ["PixarUSD"]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/MetaverseKit", from: "1.7.2"),
    .package(url: "https://github.com/furby-tm/swift-bundler", from: "2.0.9"),
    .package(url: "https://github.com/apple/swift-log.git", from: "1.5.3"),
    .package(url: "https://github.com/apple/swift-syntax.git", from: "509.0.0"),
    .package(url: "https://github.com/onevcat/Rainbow.git", from: "3.0.0"),
  ],
  targets: [
    .target(name: "pxr"),

    .target(
      name: "Arch",
      dependencies: [
        /* ------------ pxr Namespace. ---------- */
        .product(name: "pxr"),
        /* ------------ VFX Platform. ----------- */
        .product(name: "MetaTBB", package: "MetaverseKit"),
        .product(name: "PyBind11", package: "MetaverseKit"),
        .product(name: "MaterialX", package: "MetaverseKit"),
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
        .product(name: "CosmoGraph", package: "MetaverseKit"),
        /* ---------- Apple only libs. ---------- */
        .product(name: "Apple", package: "MetaverseKit", condition: .when(platforms: Arch.OS.apple.platform)),
        /* ---------- Console logging. ---------- */
        .product(name: "Logging", package: "swift-log"),
        .product(name: "Rainbow", package: "Rainbow", condition: .when(platforms: Arch.OS.apple.platform + Arch.OS.linux.platform))
      ] + Arch.OS.dependency(.boost),
      cxxSettings: [
        /* ---------- Turn everything on. ---------- */
        .define("PXR_USE_NAMESPACES", to: "1"),
        .define("PXR_PYTHON_SUPPORT_ENABLED", to: "1"),
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
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linux.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
        /* --------- Standard USD defines. --------- */
        .define("MFB_PACKAGE_NAME", to: "Arch"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Arch"),
        .define("MFB_PACKAGE_MODULE", to: "Arch"),
        .define("ARCH_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Tf",
      dependencies: [
        .product(name: "Arch"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Tf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Tf"),
        .define("MFB_PACKAGE_MODULE", to: "Tf"),
        .define("TF_EXPORTS", to: "1"),
        .define("BOOST_PYTHON_NO_PY_SIGNATURES", to: "1"),
        .define("BOOST_NO_CXX98_FUNCTION_BASE", to: "1"),
      ]
    ),

    .target(
      name: "Js",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Js"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Js"),
        .define("MFB_PACKAGE_MODULE", to: "Js"),
        .define("JS_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Gf",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Gf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Gf"),
        .define("MFB_PACKAGE_MODULE", to: "Gf"),
        .define("GF_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Trace",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Js"),
      ],
      cxxSettings: [
        /* --------- Fix missing TBB allocator funcs. --------- */
        .define("TBB_ALLOCATOR_TRAITS_BROKEN", to: "1", .when(platforms: Arch.OS.linux.platform)),
        /* --------- Standard USD source definitions. --------- */
        .define("MFB_PACKAGE_NAME", to: "Trace"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Trace"),
        .define("MFB_PACKAGE_MODULE", to: "Trace"),
        .define("TRACE_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Vt",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Vt"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Vt"),
        .define("MFB_PACKAGE_MODULE", to: "Vt"),
        .define("VT_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Work",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Work"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Work"),
        .define("MFB_PACKAGE_MODULE", to: "Work"),
        .define("WORK_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Plug",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Js"),
        .product(name: "Trace"),
        .product(name: "Work"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Plug"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Plug"),
        .define("MFB_PACKAGE_MODULE", to: "Plug"),
        .define("PLUG_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Ar",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Js"),
        .product(name: "Plug"),
        .product(name: "Vt"),
      ],
      resources: [
        .process("Resources"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Ar"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Ar"),
        .define("MFB_PACKAGE_MODULE", to: "Ar"),
        .define("AR_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Kind",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Plug"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Kind"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Kind"),
        .define("MFB_PACKAGE_MODULE", to: "Kind"),
        .define("KIND_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Sdf",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Plug"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Ar"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Sdf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Sdf"),
        .define("MFB_PACKAGE_MODULE", to: "Sdf"),
        .define("SDF_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Pcp",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Pcp"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Pcp"),
        .define("MFB_PACKAGE_MODULE", to: "Pcp"),
        .define("PCP_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Usd",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Plug"),
        .product(name: "Gf"),
        .product(name: "Kind"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
        .product(name: "Pcp"),
      ],
      resources: [
        .copy("codegenTemplates"),
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Usd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Usd"),
        .define("MFB_PACKAGE_MODULE", to: "Usd"),
        .define("USD_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Ndr",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Vt"),
        .product(name: "Plug"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Ndr"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Ndr"),
        .define("MFB_PACKAGE_MODULE", to: "Ndr"),
        .define("NDR_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Sdr",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Ndr"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Sdr"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Sdr"),
        .define("MFB_PACKAGE_MODULE", to: "Sdr"),
        .define("SDR_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdGeom",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Plug"),
        .product(name: "Gf"),
        .product(name: "Kind"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
        .product(name: "Pcp"),
        .product(name: "Usd"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdGeom"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdGeom"),
        .define("MFB_PACKAGE_MODULE", to: "UsdGeom"),
        .define("USDGEOM_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdShade",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "Ndr"),
        .product(name: "Sdr"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdShade"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdShade"),
        .define("MFB_PACKAGE_MODULE", to: "UsdShade"),
        .define("USDSHADE_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdShaders",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Ar"),
        .product(name: "Ndr"),
        .product(name: "Sdr"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdShaders"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdShaders"),
        .define("MFB_PACKAGE_MODULE", to: "UsdShaders"),
        .define("USDSHADERS_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdLux",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Vt"),
        .product(name: "Plug"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "Ndr"),
        .product(name: "Sdr"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdLux"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdLux"),
        .define("MFB_PACKAGE_MODULE", to: "UsdLux"),
        .define("USDLUX_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdHydra",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Ar"),
        .product(name: "Tf"),
        .product(name: "Plug"),
        .product(name: "Ndr"),
        .product(name: "Usd"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdHydra"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdHydra"),
        .define("MFB_PACKAGE_MODULE", to: "UsdHydra"),
        .define("USDHYDRA_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "SdrOsl",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Ar"),
        .product(name: "Ndr"),
        .product(name: "Sdr"),
        .product(name: "Vt"),
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
      ]
    ),

    .target(
      name: "UsdAbc",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdAbc"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdAbc"),
        .define("MFB_PACKAGE_MODULE", to: "UsdAbc"),
        .define("USDABC_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdDraco",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdDraco"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdDraco"),
        .define("MFB_PACKAGE_MODULE", to: "UsdDraco"),
        .define("USDDRACO_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdMedia",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdMedia"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdMedia"),
        .define("MFB_PACKAGE_MODULE", to: "UsdMedia"),
        .define("USDMEDIA_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdMtlx",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Vt"),
        .product(name: "Trace"),
        .product(name: "Ar"),
        .product(name: "Ndr"),
        .product(name: "Sdf"),
        .product(name: "Sdr"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
        .product(name: "UsdUI"),
        .product(name: "UsdUtils"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdMtlx"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdMtlx"),
        .define("MFB_PACKAGE_MODULE", to: "UsdMtlx"),
        .define("USDMTLX_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "UsdPhysics",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Plug"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdPhysics"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdPhysics"),
        .define("MFB_PACKAGE_MODULE", to: "UsdPhysics"),
        .define("USDPHYSICS_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdProc",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdProc"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdProc"),
        .define("MFB_PACKAGE_MODULE", to: "UsdProc"),
        .define("USDPROC_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdRender",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdRender"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdRender"),
        .define("MFB_PACKAGE_MODULE", to: "UsdRender"),
        .define("USDRENDER_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdRi",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdRi"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdRi"),
        .define("MFB_PACKAGE_MODULE", to: "UsdRi"),
        .define("USDRI_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdSkel",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Trace"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),

      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdSkel"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdSkel"),
        .define("MFB_PACKAGE_MODULE", to: "UsdSkel"),
        .define("USDSKEL_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdUI",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdUI"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdUI"),
        .define("MFB_PACKAGE_MODULE", to: "UsdUI"),
        .define("USDUI_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdUtils",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Vt"),
        .product(name: "Work"),
        .product(name: "Trace"),
        .product(name: "Plug"),
        .product(name: "Ar"),
        .product(name: "Kind"),
        .product(name: "Pcp"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
        .product(name: "UsdShade"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdUtils"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdUtils"),
        .define("MFB_PACKAGE_MODULE", to: "UsdUtils"),
        .define("USDUTILS_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "UsdVol",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Plug"),
        .product(name: "Work"),
        .product(name: "Vt"),
        .product(name: "Sdf"),
        .product(name: "Usd"),
        .product(name: "UsdGeom"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "UsdVol"),
        .define("MFB_ALT_PACKAGE_NAME", to: "UsdVol"),
        .define("MFB_PACKAGE_MODULE", to: "UsdVol"),
        .define("USDVOL_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "CameraUtil",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "CameraUtil"),
        .define("MFB_ALT_PACKAGE_NAME", to: "CameraUtil"),
        .define("MFB_PACKAGE_MODULE", to: "CameraUtil"),
        .define("CAMERAUTIL_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Hf",
      dependencies: [
        .product(name: "Plug"),
        .product(name: "Tf"),
        .product(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hf"),
        .define("MFB_PACKAGE_MODULE", to: "Hf"),
        .define("HF_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "PxOsd",
      dependencies: [
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Vt"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "PxOsd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "PxOsd"),
        .define("MFB_PACKAGE_MODULE", to: "PxOsd"),
        .define("PXOSD_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "Hd",
      dependencies: [
        .product(name: "Plug"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Vt"),
        .product(name: "Work"),
        .product(name: "Sdf"),
        .product(name: "CameraUtil"),
        .product(name: "Hf"),
        .product(name: "PxOsd"),
      ],
      resources: [
        .process("Resources"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hd"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hd"),
        .define("MFB_PACKAGE_MODULE", to: "Hd"),
        .define("HD_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "Garch",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Garch"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Garch"),
        .define("MFB_PACKAGE_MODULE", to: "Garch"),
        .define("GARCH_EXPORTS", to: "1"),
      ],
      linkerSettings: [
        .linkedLibrary("objc", .when(platforms: [.macOS])),
        .linkedFramework("OpenGL", .when(platforms: Arch.OS.apple.platform)),
        .linkedLibrary("glut", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("GL", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("GLU", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("m", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("X11", .when(platforms: Arch.OS.linux.platform)),
        .linkedLibrary("Xt", .when(platforms: Arch.OS.linux.platform)),
      ]
    ),

    .target(
      name: "Hgi",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Plug"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Trace"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hgi"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hgi"),
        .define("MFB_PACKAGE_MODULE", to: "Hgi"),
        .define("HGI_EXPORTS", to: "1"),
        // enable when swift supports std.unique_ptr
        .define("SWIFT_HAS_UNIQUE_PTR", to: "0"),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linux.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
      ]
    ),

    .target(
      name: "HgiMetal",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Hgi"),
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
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linux.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
      ],
      linkerSettings: [
        .linkedFramework("Metal", .when(platforms: Arch.OS.apple.platform)),
        .linkedFramework("AppKit", .when(platforms: [.macOS])),
      ]
    ),

    // .target(
    //   name: "HgiVulkan",
    //   dependencies: [
    //     .product(name: "Arch"),
    //     .product(name: "Tf"),
    //     .product(name: "Trace"),
    //     .product(name: "Hgi"),
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
    //     .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linux.platform)),
    //     .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
    //   ]
    // ),

    .target(
      name: "HgiGL",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Trace"),
        .product(name: "Garch"),
        .product(name: "Hgi"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HgiGL"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HgiGL"),
        .define("MFB_PACKAGE_MODULE", to: "HgiGL"),
        .define("HGIGL_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "HgiInterop",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Gf"),
        .product(name: "Garch"),
        .product(name: "Hgi"),
        .product(name: "HgiMetal", condition: .when(platforms: Arch.OS.apple.platform)),
        // .product(name: "HgiVulkan", condition: .when(platforms: Arch.OS.linux.platform)),
        .product(name: "HgiGL"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "HgiInterop"),
        .define("MFB_ALT_PACKAGE_NAME", to: "HgiInterop"),
        .define("MFB_PACKAGE_MODULE", to: "HgiInterop"),
        .define("HGIINTEROP_EXPORTS", to: "1"),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
        .define("PXR_METAL_SUPPORT_ENABLED", to: "0", .when(platforms: Arch.OS.linux.platform)),
        .define("PXR_VULKAN_SUPPORT_ENABLED", to: "0"),
      ],
      linkerSettings: [
        .linkedFramework("CoreVideo", .when(platforms: Arch.OS.apple.platform))
      ]
    ),

    .target(
      name: "Hio",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Js"),
        .product(name: "Plug"),
        .product(name: "Tf"),
        .product(name: "Vt"),
        .product(name: "Trace"),
        .product(name: "Ar"),
        .product(name: "Hf"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Hio"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Hio"),
        .define("MFB_PACKAGE_MODULE", to: "Hio"),
        .define("HIO_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "Glf",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Plug"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Trace"),
        .product(name: "Ar"),
        .product(name: "Sdf"),
        .product(name: "Garch"),
        .product(name: "Hf"),
        .product(name: "Hio"),
      ],
      resources: [
        .process("Resources")
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Glf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Glf"),
        .define("MFB_PACKAGE_MODULE", to: "Glf"),
        .define("GLF_EXPORTS", to: "1"),
      ]
    ),

    .target(
      name: "GeomUtil",
      dependencies: [
        .product(name: "Arch"),
        .product(name: "Tf"),
        .product(name: "Gf"),
        .product(name: "Vt"),
        .product(name: "PxOsd"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "GeomUtil"),
        .define("MFB_ALT_PACKAGE_NAME", to: "GeomUtil"),
        .define("MFB_PACKAGE_MODULE", to: "GeomUtil"),
        .define("GEOMUTIL_EXPORTS", to: "1"),
      ]
    ),

    .executableTarget(
      name: "UsdView",
      dependencies: [
        .target(name: "PixarUSD"),
      ],
      swiftSettings: [
        .interoperabilityMode(.Cxx),
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
        .target(name: "UsdAbc"),
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
        .target(name: "Hf"),
        .target(name: "PxOsd"),
        .target(name: "Hd"),
        .target(name: "Garch"),
        .target(name: "Hgi"),
        .target(name: "HgiMetal", condition: .when(platforms: Arch.OS.apple.platform)),
        // .target(name: "HgiVulkan", condition: .when(platforms: Arch.OS.linux.platform)),
        .target(name: "HgiGL"),
        .target(name: "HgiInterop"),
        .target(name: "Hio"),
        .target(name: "Glf"),
        .target(name: "GeomUtil"),
        // --- usd imaging. ------
        .target(name: "UsdShaders"),
        // -------- macros. ------
        .target(name: "PixarMacros"),
        // -----------------------
      ],
      cxxSettings: [
        // enable to debug swift retain/release calls.
        .define("DEBUG_MEMORY_MANAGEMENT", to: "0"),
      ],
      swiftSettings: [
        // enable to debug bundled (python, plugins, resources).
        .define("DEBUG_PIXAR_BUNDLE"),
        .interoperabilityMode(.Cxx),
      ]
    ),

    .testTarget(
      name: "PixarUSDTests",
      dependencies: [
        .target(name: "PixarUSD"),
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
  }
}
