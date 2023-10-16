### Universal Scene Description for the Open Source Metaverse

Universal Scene Description (**USD**) is an efficient, scalable system for
authoring, reading, and streaming time-sampled scene description for
interchange between graphics applications.

For more details, please visit the web site [here](http://openusd.org).

> **NOTE:** Swift is an open source programming language that is fully
supported across **Linux** and [**Swift on Server**](https://www.swift.org/server/),
the entire **Apple** family of devices: **macOS**, **visionOS**, **iOS**, **tvOS**, **watchOS**,
as well as support for **Microsoft Windows**. To learn more about Swift, please visit [swift.org](https://www.swift.org).
<br>

# Swifting the Metaverse

<image src="https://steamuserimages-a.akamaihd.net/ugc/110734252808679209/093302F19C70C4B7421C2A43200B205A650AB9B2/?imw=5000&imh=5000&ima=fit&impolicy=Letterbox&imcolor=%23000000&letterbox=false">

##### To use Pixar USD with Swift, add **SwiftUSD** as a **Package** dependency in your Package.swift file.
```swift
dependencies: [
  .package(url: "https://github.com/wabiverse/SwiftUSD.git", from: "23.0.8"),
]
```

##### Then, for any target you'd like, add **USD** as a **Product** of your **Target** dependencies.
```swift
targets: [
  /* 📕 For library products... */
  .target(
    name: "MyMetaverseLibrary",
    dependencies: [
      /* add pixar usd as a library dependency. */
      .product(name: "USD", package: "SwiftUSD")
    ]
  ),

  /* 📗 Or executable products... */
  .executableTarget(
    name: "MyMetaverseApp",
    dependencies: [
      /* add pixar usd as an executable dependency. */
      .product(name: "USD", package: "SwiftUSD"),
    ],
    plugins: [
      /* 📙 And, plugins are added like so. */
      .plugin(name: "SwiftUSDSchemaGenPlugin", package: "MetaverseSchemaGen"),
      .plugin(name: "ArnoldRenderEnginePlugin", package: "AutodeskArnold"),
      .plugin(name: "EpicAnimationNodesPlugin", package: "EpicAnimation")
    ]
  ),
]
```

```diff
@@ Dependency Notes @@
- Library Products allow clients that declare a dependency on this package to use the package’s functionality.
+ Executable Products vend an executable target. Use this only if you want to make the executable available to clients.
! Plugin Products vend plugin targets. This makes the plugin available to clients that integrate the Swift package.
# Swift's package manager, SwiftPM, is capabable of building Swift, Objective-C/C++, and C/C++ code.
```
<br>

Build Status
------------
|         |   Linux   |  Windows  |   macOS   |
|:-------:|:---------:|:---------:|:---------:|
|   dev   | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=dev&amp;jobName=Linux)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=dev) | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=dev&amp;jobName=Windows)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=dev) | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=dev&amp;jobName=macOS)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=dev) |
|  release | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=release&amp;jobName=Linux)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=release) | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=release&amp;jobName=Windows)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=release) | [![Build Status](https://dev.azure.com/PixarAnimationStudios/USD/_apis/build/status/PixarAnimationStudios.USD?branchName=release&amp;jobName=macOS)](https://dev.azure.com/PixarAnimationStudios/USD/_build/latest?definitionId=2&branchName=release) |

