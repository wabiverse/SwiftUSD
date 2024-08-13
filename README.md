<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

<h1 align="center">
    <a href="https://wabi.foundation/pixarusd/documentation/pixarusd#gh-light-mode-only">
      <img width="350" src="swiftlymetaversingwordslight.svg">
    </a>
    <a href="https://wabi.foundation/pixarusd/documentation/pixarusd#gh-dark-mode-only">
      <img width="350" src="swiftlymetaversingwordsdark.svg">
    </a>
</h1>

<p align="center">
  <i align="center">Pixar's universal scene description for <b>swift</b> and the open source <b>metaverse</b>.</i>
</p>

</div>

<h4 align="center">
  <a href="https://wabiverse.github.io/SwiftUSD/documentation/pixarusd/">
    <img src="https://img.shields.io/badge/v23%2E11%2E43-DocumentationSource?style=flat-square&label=docs&labelColor=F05138&logo=swift&color=gray&logoColor=white">
  </a>
  <a href="https://github.com/wabiverse/SwiftUSD/actions/workflows/swift-ubuntu.yml">
    <img src="https://img.shields.io/github/actions/workflow/status/wabiverse/SwiftUSD/swift-ubuntu.yml?style=flat-square&label=ubuntu%20&labelColor=E95420&logoColor=FFFFFF&logo=ubuntu">
  </a>
  <a href="https://github.com/wabiverse/SwiftUSD/actions/workflows/swift-macos.yml">
    <img src="https://img.shields.io/github/actions/workflow/status/wabiverse/SwiftUSD/swift-macos.yml?style=flat-square&label=macOS&labelColor=000000&logo=apple">
  </a>
  <a href="https://github.com/wabiverse/SwiftUSD/graphs/contributors">
    <img src="https://img.shields.io/github/contributors-anon/wabiverse/SwiftUSD?color=8A2BE2&style=flat-square" alt="contributors" style="height: 20px;">
  </a>
  <br>
  <a href="https://discord.gg/bfW4NyKpuA">
    <img src="https://img.shields.io/badge/discord-7289da.svg?style=flat-square&logo=discord" alt="discord" style="height: 20px;">
  </a>
  <a href="https://wabi.foundation">
    <img src="https://img.shields.io/badge/wabi_foundation-black?style=flat-square&logo=data:image/svg%2bxml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiPz4KPHN2ZyBpZD0iTGF5ZXJfMSIgZGF0YS1uYW1lPSJMYXllciAxIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA1MDAgNTAwIj4KICA8ZGVmcz4KICAgIDxzdHlsZT4KICAgICAgLmNscy0xIHsKICAgICAgICBmaWxsOiAjNDM0MzQzOwogICAgICB9CgogICAgICAuY2xzLTEsIC5jbHMtMiB7CiAgICAgICAgc3Ryb2tlLXdpZHRoOiAwcHg7CiAgICAgIH0KCiAgICAgIC5jbHMtMiB7CiAgICAgICAgZmlsbDogI2ZmZjsKICAgICAgfQogICAgPC9zdHlsZT4KICA8L2RlZnM+CiAgPHBhdGggY2xhc3M9ImNscy0yIiBkPSJNMTMyLjQyLDMzOS42NXMtMzQuOS0yOC40OC00NS41Ny05OC42MmMtMy4xMy0yNy4yNS4xMS01My42NywxMC4xNS03OS4yMiwxMS40OS0yOS4yNSwyOS44OC01My4xOCw1NC45OS03Mi4wMyw0Ljk5LTMuNzQsMTAuNDUtNi44OCwxNC42LTExLjc1LDYuMDEtNy4wNiw3LjkxLTE1LjE0LDYuNzctMjQuMTUtLjg3LTYuNzUtMy4zNC0xMy01LjkzLTE5LjItMS42LTMuODUtMy4zNy03LjY2LTMuODktMTEuODgtLjk5LTcuODgsMy4yOS0xNC43NiwxMC43Mi0xNy42NSw3Ljg0LTMuMDcsMTUuODMtMi45NywyMy45Mi0xLjY1LDEyLjYsMi4wOCwyNC43Miw1LjkzLDM2LjY2LDEwLjM3LDIxLjg3LDguMTMsNDIuNjQsMTguNSw2Mi40MiwzMC44NiwyMi45OSwxNC4zNSw0NC4wNiwzMS4wOCw2Mi41Niw1MC45NiwxMy4zNywxNC4zOCwyNS4wOCwyOS45NiwzNC4zOCw0Ny4yNSwxOC4xMSwzMy42NywyNC4wMyw2OS40MiwxNy41OCwxMDcuMTctMi4yNSwxMy4yLTYuMTgsMjUuNzQtMTIuOTgsMzcuMzctMTIuMjMsMjAuODgtMzAuNDYsMzEuMTctNTQuNTUsMzEuNS0xMy4xNC4xNy0yNS41MS0zLjA0LTM3LjQ4LTguMDktMTEuMy00Ljc1LTIyLjA2LTEwLjQ2LTMyLjU3LTE2LjY2LTExLjY5LTYuODktOTguMzQtNjkuNzgtMTIwLjM0LTc0LjYxLTE3Ljk0LDMuMTYtMzMuNTYsNy45Ni00MS4xMSwyNC43LTM0LjU1LDMzLjg2LDE5LjcyLDk1LjM1LDE5LjcyLDk1LjM1aC0uMDNaTTMxMS42NSwyNTYuNjhjLjAzLTguMi05Ljc3LTE2LjE5LTE4LjE5LTE0Ljg0LTYuNTYsMS4wNS05Ljg1LDYuNjctNy41OCwxMi45MywyLjI3LDYuMjksOC43OCwxMC45NywxNS40NSwxMS4wOSw1LjkyLjEzLDEwLjI5LTMuNzksMTAuMzItOS4ydi4wMloiLz4KICA8cGF0aCBjbGFzcz0iY2xzLTIiIGQ9Ik0yOTguNCwzMzMuODZjMi43MS0xLjQ4LTczLjksODYuMTgtMTY2LjIsNS45LTIyLjk2LTE5Ljk3LTY3LjU2LTEyMC42Nyw1LjI0LTEyMi43MSw0Ni4yNy0xLjI5LDExOC4xMyw2NC42OCwxMTguMTMsNjQuNjgtMjguOTItMTkuNTQtODcuMDctNTkuMjktMTIyLjE1LTI3Ljk0LTQ3LjcyLDQyLjY2LDI0LjM2LDE1Ni4zNSwxNjQuOTcsODAuMDdoMFoiLz4KICA8cGF0aCBjbGFzcz0iY2xzLTIiIGQ9Ik0yMzIuNzEsMzU3LjljMTAuNy0zLjA3LDIwLjYzLTguMDQsMzAuODEtMTIuMzcsMTAuNy00LjU1LDIxLjQzLTkuMDMsMzIuOS0xMS4zOCw3LjExLTEuNDUsMTQuODgtMS40MiwxOS44Ny4xMS01LjYzLDguMTUtMTAuMjcsMTYuODItMTUuNTUsMjUuMTMtMi4xNCwzLjM4LTQuNTUsNi42MS03LjMsOS41Mi0xMS45MywxMi41Ny0yNi40NywxNy44My00Mi43NywxOC4wNi00LjE0LjA2LTguMjksMC0xMy4yLDAsNy4yOSwxLjUzLDEzLjc1LDMuMTMsMjAuMDYsNS40OSwxNS45MSw1Ljk2LDI1LjI3LDE3LjU2LDI5LjExLDMzLjc1LDQuMTksMTcuNjcsNi44NCwzNS42OSwxMS40NCw1My4yOSwxLjQyLDUuNDQsMi42NiwxMC45NSw0LjYxLDE2LjI0LjQ3LDEuMjYuNTIsMS44MS0xLjE2LDEuNTktMTcuNTktMi40MS0zNC42LTYuNjEtNTAuMTUtMTUuNTYtMTMuOTItOC4wMi0yNC43NS0xOS4xNi0zMy4yOC0zMi43LTcuOTYtMTIuNjUtMTMuNTgtMjYuNDctMTkuNy00MC4wMy0zLjIxLTcuMTEtNS4zMi0xMi45LTkuNDYtMTkuMTYtNC41My02LjgzLTEwLjU5LTEyLjUxLTE3LjUtMTYuOTMtMjguMzctMTguMTctNDQuNjUtMzguODgtNDUuMDgtMzkuMzQsMCwwLDI5LjU4LDM1LjczLDg0LjksMzAuMyw3LjMtMS40NSwxNC41NS0zLjA0LDIxLjQxLTYuMDFsLjAyLS4wMloiLz4KICA8cGF0aCBjbGFzcz0iY2xzLTEiIGQ9Ik0zMTEuNjMsMjU2LjY4Yy0uMDIsNS40MS00LjQxLDkuMzEtMTAuMzIsOS4yLTYuNjctLjE0LTEzLjE5LTQuODEtMTUuNDUtMTEuMDktMi4yNy02LjI4LDEuMDItMTEuODgsNy41OC0xMi45Myw4LjQyLTEuMzUsMTguMjIsNi42NCwxOC4xOSwxNC44NHYtLjAyWiIvPgo8L3N2Zz4=" alt="wabi foundation" style="height: 20px;">
  </a>
  <a href="https://openusd.org/release/index.html">
    <img src="https://img.shields.io/badge/openusd-blue.svg?style=flat-square&logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMjQiIGhlaWdodD0iMjQiIHZpZXdCb3g9IjAgMCAxMiAxMiIgZmlsbD0ibm9uZSIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj4KPHBhdGggZD0iTTYuOTQwMzEgMTEuMzU4MlY3LjQ3NzY0VjMuNjU2NzRMMCAxLjI2ODY4VjguOTg1MUw2Ljk0MDMxIDExLjM1ODJaTTEuMjY4NjYgOC4wMTQ5NVYzLjE3OTEzTDUuNjExOTUgNC42NTY3NFY5LjQ5MjU3TDEuMjY4NjYgOC4wMTQ5NVoiIGZpbGw9IiMyMDhFQ0QiLz4KPHBhdGggZD0iTTEuNzc2MTIgNy41OTcwM0w1LjA4OTU2IDguNzMxMzZWNS4wNzQ2NEwxLjc3NjEyIDMuOTQwMzFWNy41OTcwM1oiIGZpbGw9IiM3REQxRjYiLz4KPHBhdGggZD0iTTguOTI1MzQgNS41OTcwMkw5Ljk5OTk3IDUuOTcwMTZWMS4zNTgyMUw2LjA0NDc0IDBWMS4xNjQxOEw4LjkyNTM0IDIuMTY0MThWNS41OTcwMloiIGZpbGw9IiM3REQxRjYiLz4KPHBhdGggZD0iTTIuOTg1MTEgMC41OTcwMTVWMS43NjEyTDcuMzczMTcgMy4yODM1OVY4LjI1Mzc0TDguNDQ3OCA4LjYxMTk1VjIuNDc3NjFMMi45ODUxMSAwLjU5NzAxNVoiIGZpbGw9IiMzNUMzRjEiLz4KPC9zdmc+Cg==" alt="youtube" style="height: 20px;">
  </a>
</h4>

<image align=top src="https://www.dropbox.com/scl/fi/cmqz171jkketkvpyojtbx/swiftyusd.png?rlkey=rosui4p7dv410eqvztmynhz56&raw=1">

> [!IMPORTANT]
> #### Supporting SwiftUSD ❤️
> If you find **SwiftUSD** useful, please consider supporting me by [becoming a sponsor](https://github.com/sponsors/wabiverse). I spend a tremendous amount of time dedicating my life to open source projects, and each sponsorship helps me focus more time on making quality tools and software for the community.

<br/>

<div align="center">

# Swifting the Metaverse

</div>

<div align="center">

# <img width="350" src="https://www.dropbox.com/scl/fi/96fxs64ap4aaq9f7vp0yf/swiftusdcropped.png?rlkey=wvgzfodi8skub1svqf1w4g07g&raw=1">

</div>

Universal Scene Description (**USD**) is an efficient, scalable system for
authoring, reading, and streaming time-sampled scene description for
interchange between graphics applications.

For more details, please visit the web site [here](http://openusd.org).

##### To use Pixar's USD in swift, add SwiftUSD as a package dependency in your project's Package.swift file.
```swift
dependencies: [
  .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "24.8.0"),
]
```


##### Then, for any target you'd like, add the monolithic USD **Pixar** product as a target dependency, a complete example.
```swift
// swift-tools-version: 5.10
import PackageDescription

let package = Package(
  name: "MyMetaversePackage",
  platforms: [
    .macOS(.v14),
    .visionOS(.v1),
    .iOS(.v17),
    .tvOS(.v17),
    .watchOS(.v10)
  ],
  // --- 📦 Package Products. ---
  products: [
    .library(
      name: "MyMetaverseLibrary",
      targets: ["MyMetaverseLibrary"]
    ),
    .executable(
      name: "MyMetaverseApp",
      targets: ["MyMetaverseApp"]
    ),
  ],
  dependencies: [
    .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "24.8.0")
  ],
  targets: [
    /* 📕 For library products... */
    .target(
      name: "MyMetaverseLibrary",
      dependencies: [
        /* add pixar usd as a library dependency. */
        .product(name: "PixarUSD", package: "SwiftUSD"),
      ],
      swiftSettings: [
        /* needed for SwiftUSD. */
        .interoperabilityMode(.Cxx)
      ]
    ),

    /* 📗 Or executable products... */
    .executableTarget(
      name: "MyMetaverseApp",
      dependencies: [
        /* add pixar usd as an executable dependency. */
        .product(name: "PixarUSD", package: "SwiftUSD"),
      ],
      swiftSettings: [
        /* needed for SwiftUSD. */
        .interoperabilityMode(.Cxx)
      ],
      plugins: [
        /* 📙 And, plugins are added like so. */
        .plugin(name: "UsdGenSchemaPlugin", package: "SwiftUSD")
      ]
    ),
  ],
  cxxLanguageStandard: .cxx17
)
```

```diff
@@ Dependency Notes @@
- Library Products allow clients that declare a dependency on this package to use the package’s functionality.
+ Executable Products vend an executable target. Use this only if you want to make the executable available to clients.
! Plugin Products vend plugin targets. This makes the plugin available to clients that integrate the Swift package.
# Swift's package manager, SwiftPM, is capabable of building Swift, Objective-C/C++, and C/C++ code.
```

##### Finally, author scene description, this is a working example of creating a new USD stage with a transform and a sphere in swift.
```swift
import Foundation
import PixarUSD

@main
enum Creator
{
  static func main()
  {
    /* Setup all usd resources (python, plugins, resources). */

    Pixar.Bundler.shared.setup(.resources)

    /* Create a new USD stage with a transform and a sphere. */

    let stage = Usd.Stage.createNew("HelloPixarUSD.usda")

    UsdGeom.Xform.define(stage, path: "/Hello")
    UsdGeom.Sphere.define(stage, path: "/Hello/World")

    stage.getPseudoRoot().set(doc: "Hello World Example (Swift)!")

    stage.save()
  }
}
```

##### Or, if you prefer those swifty declarative APIs...
```swift
import Foundation
import PixarUSD

@main
enum Creator
{
  static func main()
  {
    /* Setup all usd resources (python, plugins, resources). */

    Pixar.Bundler.shared.setup(.resources)

    /* Create a new USD stage with a transform and a sphere. */

    USDStage("HelloPixarUSD", ext: .usda)
    {
      USDPrim("Hello", type: .xform)
      {
        USDPrim("World", type: .sphere)
      }
    }
    .set(doc: "Stay Swifty.")
    .save()
  }
}
```

<br/>

# **UsdView (Under Development)**

  The **UsdView** application in this project is written entirely in **Swift**, and serves as a living example of both **Swift/C++** interop
  and creating **cross platform UI** applications in **Swift** (utilizing [**SwiftCrossUI**](https://github.com/stackotter/swift-cross-ui)).

  ### Linux

  > [!IMPORTANT]
  > The [**bundler**](https://github.com/stackotter/swift-bundler.git) is currently in development to support bundling apps on **Linux**, until then please follow these instructions to run **UsdView** on **Linux**:

<div align="center">

  <div align="left">

  ```pwsh
  git clone https://github.com/wabiverse/SwiftUSD
  cd SwiftUSD

  swift run -c release UsdView
  ```

  </div>

</div>

  ### Apple Devices (macOS, visionOS, iOS)

  > [!TIP]
  > Install the [**bundler**](https://github.com/stackotter/swift-bundler.git) locally by running the following commands in your terminal:

<div align="center">

  <div align="left">

  ```pwsh
  git clone https://github.com/stackotter/swift-bundler
  cd swift-bundler

  swift build -c release
  sudo cp .build/release/swift-bundler /usr/local/bin/
  ```

  </div>


  <div align="left">

  Finally, to run and bundle **UsdView** or any other app (such as your own!) with the bundler installed locally, run the following commands:
  ```pwsh
  git clone https://github.com/wabiverse/SwiftUSD
  cd SwiftUSD
  ```

  #### **macOS**

  Run and bundle **UsdView** on **macOS**.
  ```pwsh
  swift bundler run -c release UsdView
  ```

  #### **visionOS** or **iOS**

  Run and bundle **UsdView** on **visionOS** or **iOS**.
  ```pwsh
  # list available iOS and visionOS simulators.
  swift bundler simulators

  # boot a simulator from the list.
  swift bundler simulators boot [id-of-device]

  # if you booted a visionOS device.
  swift bundler run -p visionOSSimulator -c release UsdView

  # if you booted a iOS device.
  swift bundler run -p iOSSimulator -c release UsdView
  ```

  </div>

</div>

<br/>

# **OH SH!**
You can even run it in a tiny script, no package necessary, the comments next to the import
statements describe the git sources to pull from, and everything transitively linked will come flying
on in - checkout [**swift-sh**](https://github.com/mxcl/swift-sh)!

> [!IMPORTANT]
> You will need to use the **Wabi** [**fork of swift-sh**](https://github.com/wabiverse/swift-sh)
> in order for this to work with **Swift 5.9** cxx interop.


![image](https://www.dropbox.com/scl/fi/66ohshzkx6jg0ym69znqw/297358393-1ee63339-b0b3-4f50-920b-9f6beb7cc227.png?rlkey=3i8cr6qjwnjrc36qycjkcz291&raw=1)



<br>

> [!NOTE]
> Swift is an open source programming language that is fully supported across **Linux** and [**Swift on Server**](https://www.swift.org/server/), the entire **Apple** family of devices: **macOS**, **visionOS**, **iOS**, **tvOS**, **watchOS**, as well as support for **Microsoft Windows**. To learn more about Swift, please visit [swift.org](https://www.swift.org).

<br>

<hr/>

###### *if you can `mmap` a **pixel**, you can `mmap` a **metaverse**.*
###### SwiftUSD is licensed under the terms of the [Tomorrow Open Source Technology 1.0 License](https://openusd.org/license).
