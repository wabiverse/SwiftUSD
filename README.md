<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->


<div align="center">

# Universal Scene Description (USD) for Swift

</div>

<sup>
  <div>
    <a href="https://wabi.foundation/pixarusd/documentation/pixarusd">
      <img align=top src="https://img.shields.io/badge/Swift_USD_API_Docs-DocumentationSource?style=for-the-badge&color=F05138&logo=swift&logoColor=white">
    </a>
    <a href="mailto:devs@wabi.foundation?subject=%5BSwiftUSD%20Linux%20Inquiry%5D%20">
      <img align=right src="https://img.shields.io/badge/Linux_|_Support-LinuxAttr?style=for-the-badge&color=003366&logo=linuxFoundation">
    </a>
  </div>
</sup>

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
  .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "23.11.28"),
]
```


##### Then, for any target you'd like, add the monolithic USD **Pixar** product as a target dependency, a complete example.
```swift
let package = Package(
  name: "MyMetaversePackage",
  platforms: [
    .macOS(.v14),
    .visionOS(.v1),
    .iOS(.v16),
    .tvOS(.v16),
    .watchOS(.v9)
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
    .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "23.11.28")
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

    UsdStage("HelloPixarUSD", ext: .usda)
    {
      UsdPrim("Hello", type: .xform)
      {
        UsdPrim("World", type: .sphere)
      }
    }
    .set(doc: "Stay Swifty.")
    .save()
  }
}
```

# **OH SH!**
You can even run it in a tiny script, no package necessary, the comments next to the import
statements describe the git sources to pull from, and everything transitively linked will come flying
on in - checkout [**swift-sh**](https://github.com/mxcl/swift-sh)!

> [!IMPORTANT]
> You will need to use the **Wabi** [**fork of swift-sh**](https://github.com/wabiverse/swift-sh)
> in order for this to work with **Swift 5.9** cxx interop.


![image](https://github.com/wabiverse/SwiftUSD/assets/18516968/1ee63339-b0b3-4f50-920b-9f6beb7cc227)



<br>

> [!NOTE]
> Swift is an open source programming language that is fully supported across **Linux** and [**Swift on Server**](https://www.swift.org/server/), the entire **Apple** family of devices: **macOS**, **visionOS**, **iOS**, **tvOS**, **watchOS**, as well as support for **Microsoft Windows**. To learn more about Swift, please visit [swift.org](https://www.swift.org).

<br>
