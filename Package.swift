// swift-tools-version: 5.9
import CompilerPluginSupport
import PackageDescription

let package = Package(
  name: "SwiftUSD",
  platforms: [
    /*
      the swiftpm docs are vague on this, however, this setting only
      currently applies to targeting minimum apple platform versions
      and the omission of linux and windows here (they do not exist
      on the SupportedPlatform struct) does not mean linux & windows
      are not supported. For now, one can disregard this setting on all
      platforms that are not apple.

      Note: the apple platform minimums are quite recent, this is due to
      CXX interop only appearing in recent versions of these apple SDKs,
      without setting these where they are - we would otherwise have to
      muck up the swift apis with @availibility macros, to avoid errors
      complaining about (ex. 'UsdStage is only available in macOS 14 or
      later').
     */
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
    // -------- Pixar.Imaging -----
    .library(
      name: "CameraUtil",
      targets: ["CameraUtil"]
    ),
    .library(
      name: "Hf",
      targets: ["Hf"]
    ),
    // ----- Pixar.UsdImaging -----
    .library(
      name: "UsdShaders",
      targets: ["UsdShaders"]
    ),
    // --------------- Python -----
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
      name: "PyUsdShade",
      type: .dynamic,
      targets: ["PyUsdShade"]
    ),
    .library(
      name: "PyUsdShaders",
      type: .dynamic,
      targets: ["PyUsdShaders"]
    ),
    .library(
      name: "PyUsdLux",
      type: .dynamic,
      targets: ["PyUsdLux"]
    ),
    .library(
      name: "PyCameraUtil",
      type: .dynamic,
      targets: ["PyCameraUtil"]
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
      targets: [
        "PixarUSD",
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
        "PyUsdGeom",
        "PyUsdShade",
        "PyUsdShaders",
        "PyUsdLux",
        "PyCameraUtil"
      ]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/MetaverseKit", from: "1.5.1"),
    .package(url: "https://github.com/furby-tm/swift-bundler", from: "2.0.9"),
    .package(url: "https://github.com/apple/swift-log.git", from: "1.5.3"),
    .package(url: "https://github.com/apple/swift-syntax.git", from: "509.0.0"),
    .package(url: "https://github.com/onevcat/Rainbow.git", from: "3.0.0"),
  ],
  targets: [
    .target(
      name: "pxr",
      dependencies: [],
      publicHeadersPath: "include"
    ),

    .target(
      name: "Arch",
      dependencies: [
        /* ------------ pxr Namespace. ---------- */
        .target(name: "pxr"),
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
        /* ---------- Apple only libs. ---------- */
        .product(name: "Apple", package: "MetaverseKit", condition: .when(platforms: Arch.OS.apple.platform)),
        /* ---------- Console logging. ---------- */
        .product(name: "Logging", package: "swift-log"),
        .product(name: "Rainbow", package: "Rainbow", condition: .when(platforms: Arch.OS.apple.platform + Arch.OS.linux.platform))
      ] + Arch.OS.dependency(.boost),
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
        /* --------- Apple build settings. --------- */
        .define("PXR_METAL_SUPPORT_ENABLED", to: "1", .when(platforms: Arch.OS.apple.platform)),
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
        .target(name: "Arch"),
      ],
      cxxSettings: [
        .define("MFB_PACKAGE_NAME", to: "Tf"),
        .define("MFB_ALT_PACKAGE_NAME", to: "Tf"),
        .define("MFB_PACKAGE_MODULE", to: "Tf"),
        .define("TF_EXPORTS", to: "1")
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
        .define("JS_EXPORTS", to: "1")
      ]
    ),

    .target(
      name: "Gf",
      dependencies: [
        .target(name: "Arch"),
        .target(name: "Tf"),
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
        .define("TRACE_EXPORTS", to: "1")
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
        .define("VT_EXPORTS", to: "1")
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
        .define("WORK_EXPORTS", to: "1")
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
        .define("PLUG_EXPORTS", to: "1")
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
        .define("AR_EXPORTS", to: "1")
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
        .define("KIND_EXPORTS", to: "1")
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
        .define("PCP_EXPORTS", to: "1")
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
        .define("USD_EXPORTS", to: "1")
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
        .define("NDR_EXPORTS", to: "1")
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
        .define("SDR_EXPORTS", to: "1")
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
        .define("USDGEOM_EXPORTS", to: "1")
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
        .define("USDSHADE_EXPORTS", to: "1")
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
        .define("USDSHADERS_EXPORTS", to: "1")
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
        .define("USDLUX_EXPORTS", to: "1")
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
        .define("CAMERAUTIL_EXPORTS", to: "1")
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
        .define("HF_EXPORTS", to: "1")
      ]
    ),

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
        .target(name: "UsdGeom"),
        .target(name: "UsdShade"),
        .target(name: "UsdLux"),
        // ------- imaging. ------
        .target(name: "CameraUtil"),
        .target(name: "Hf"),
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
        .product(name: "SwiftSyntaxMacrosTestSupport", package: "swift-syntax"),
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
