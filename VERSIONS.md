3rd Party Library and Application Versions
------------------------------------------

SwiftUSD relies on an ecosystem of libraries and applications, which are all automatically included through the usage of
[MetaverseKit](https://github.com/wabiverse/MetaverseKit), as a package dependency in the `Package.swift` file for **SwiftPM**.
This makes the complicated and time-consuming step of building all these dependencies entirely automatic for all users, since
**SwiftPM** automatically pulls in all dependencies and builds them locally at build time when users run:

```swift
// For building and running programs from a package
swift run SomeMetaverseApp

// Or, just for building all targets in a package
swift build

// Or, building and running package tests
swift test
```

This page outlines the versions of these libraries used and tested against
[MetaverseKit](https://github.com/wabiverse/MetaverseKit), our single package
dependency which brings in this whole ecosystem from one central place.

## Tested

Currently, through early development, Wabi is only using (arm64) macOS running on Apple silicon.
In the near term we will begin with (aarch64) Linux first, and Microsoft Windows support sometime after,
or in parallel.

| Software      | Linux                | macOS                           | Windows                        |
| ------------- | -------------------- | ----------------------------    | ------------------------------ |
| OS            | CentOS Linux 7       | macOS 14 (Sonoma)               | Windows 11                     |
| C++ Compiler  | ??? (TODO)           | Apple clang 15.0.0 (Xcode 15.1) | ??? (TODO)                     |
| Python        | 3.11.6               | 3.11.6                          | 3.11.6                         |
| PyBind11      | 2.11.1               | 2.11.1                          | 2.11.1                         |
| Boost         | 1.81.2               | 1.81.2                          | 1.81.2                         |
| oneTBB        | 2021.10.0            | 2021.10.0                       | 2021.10.0                      |
| OpenSubdiv    | 3.6.0                | 3.6.0                           | 3.6.0                          |
| OpenImageIO   | 2.5.4.0              | 2.5.4.0                         | 2.5.4.0                        |
| OpenColorIO   | 2.3.0                | 2.3.0                           | 2.3.0                          |
| OSL           | 1.12.14.0 (TODO)     | 1.12.14.0 (TODO)                | 1.12.14.0 (TODO)               |
| Ptex          | 2.4.2                | 2.4.2                           | 2.4.2                          |
| ImGui         | 1.89.9               | 1.89.9                          | 1.89.9                         |
| Embree        | ??? (TODO)           | ??? (TODO)                      | ??? (TODO)                     |
| RenderMan     | 24.4, 25.0 (TODO)    | 24.4, 25.0 (TODO)               | 24.4, 25.0 (TODO)              |
| Alembic       | 1.8.5                | 1.8.5                           | 1.8.5                          |
| OpenEXR       | 3.2.1                | 3.2.1                           | 3.2.1                          |
| Imath         | 3.1.9                | 3.1.9                           | 3.1.9                          |
| MaterialX     | 1.38.8               | 1.38.8                          | 1.38.8                         |
| OpenVDB       | 10.1.0               | 10.1.0                          | 10.1.0                         |
| Vulkan SDK    | 1.3.268.0            | 1.3.268.0                       | 1.3.268.0                      |
| HDF5          | 1.10.0               | 1.10.0                          | 1.10.0                         |
| Blosc         | 1.21.5               | 1.21.5                          | 1.21.5                         |
| Eigen         | 3.4.0                | 3.4.0                           | 3.4.0                          |
| Draco         | 1.5.6                | 1.5.6                           | 1.5.6                          |
| TurboJPEG     | 3.0.1                | 3.0.1                           | 3.0.1                          |
| TIFF          | 4.6.0                | 4.6.0                           | 4.6.0                          |
| LibPNG        | 1.6.40               | 1.6.40                          | 1.6.40                         |
| WebP          | 1.3.2                | 1.3.2                           | 1.3.2                          |
| RAW           | 0.21.1               | 0.21.1                          | 0.21.1                         |
| ZStandard     | 1.5.5                | 1.5.5                           | 1.5.5                          |
| LZMA2         | 5.4.4                | 5.4.4                           | 5.4.4                          |
| MiniZip       | 4.0.1                | 4.0.1                           | 4.0.1                          |
| Yaml          | 0.8.0                | 0.8.0                           | 0.8.0                          |
