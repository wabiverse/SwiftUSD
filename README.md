## Pixar's Universal Scene Description for Swift and the Metaverse

> [!IMPORTANT]
> ### Supporting SwiftUSD ❤️
> If you find **SwiftUSD** useful, please consider supporting me by [becoming a sponsor](https://github.com/sponsors/wabiverse). I spend a tremendous amount of time dedicating my life to open source projects, and each sponsorship helps me focus more time on making quality tools and software for the community.

Universal Scene Description (**USD**) is an efficient, scalable system for
authoring, reading, and streaming time-sampled scene description for
interchange between graphics applications.

For more details, please visit the web site [here](http://openusd.org).

# Swifting the Metaverse

<image src="https://www.dropbox.com/scl/fi/cmqz171jkketkvpyojtbx/swiftyusd.png?rlkey=rosui4p7dv410eqvztmynhz56&raw=1">

##### To use Pixar's USD in swift, add SwiftUSD as a package dependency in your project's Package.swift file.
```swift
dependencies: [
  .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "23.11.11"),
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
    .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "23.11.11")
  ],
  targets: [
    /* 📕 For library products... */
    .target(
      name: "MyMetaverseLibrary",
      dependencies: [
        /* add pixar usd as a library dependency. */
        .product(name: "Pixar", package: "SwiftUSD")
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
        .product(name: "Pixar", package: "SwiftUSD"),
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
  ]
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
import Pixar

@main
enum Creator
{
  static func main()
  {
    /* Setup all usd resources (python, plugins, resources). */

    Pixar.Bundle.shared.setup(.resources)

    /* Create a new USD stage with a transform and a sphere. */

    var stage = Pixar.Usd.Stage.createNew("HelloPixarUSD.usda")

    Pixar.UsdGeom.Xform.define(stage, path: "/Hello")
    Pixar.UsdGeom.Sphere.define(stage, path: "/Hello/World")

    stage.getPseudoRoot().set(doc: "Hello World Example (Swift)!")

    stage.save()
  }
}
```
<br>

> [!NOTE]
> Swift is an open source programming language that is fully supported across **Linux** and [**Swift on Server**](https://www.swift.org/server/), the entire **Apple** family of devices: **macOS**, **visionOS**, **iOS**, **tvOS**, **watchOS**, as well as support for **Microsoft Windows**. To learn more about Swift, please visit [swift.org](https://www.swift.org).

<br>
