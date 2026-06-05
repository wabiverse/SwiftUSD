//===----------------------------------------------------------------------===//
// This source file is taken from github.com/apple/SwiftUsd
//
// Copyright © 2025 Apple Inc. and the SwiftUsd project authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
//===----------------------------------------------------------------------===//

@_exported import pxr
import Tf
@_exported import USDOverlays

// MARK: Special case TfRefBase

/// TfRefPtr<TfRefBase> is not a supported template, so we handle
/// the conformance manually. (We want TfRefBase to be supported
/// so there's more fluency with casting and testing casting,
/// for example)
public extension Pixar {
  struct TfRefBase: Overlay._TfRefBaseProtocol {
    public typealias _TfRefPtrType = Never
    public typealias _TfConstRefPtrType = Never
    public func _asRefPtrType() -> Never {
      fatalError("Pixar.TfRefBase is not convertible to Pixar.TfRefPtr")
    }

    public static func _fromRefPtrType(_ p: Never) -> Pixar.TfRefBase? {}
    public static func _fromConstRefPtrType(_ p: Never) -> Pixar.TfRefBase? {}
  }
}

extension Never: Overlay._TfRefPtrProtocol, Overlay._TfConstRefPtrProtocol {
  public typealias _TfRefBaseType = Pixar.TfRefBase
  public static func _nullPtr() -> Never {
    fatalError("Pixar.TfRefBase has no TfRefPtr nullptr value")
  }

  public func _isNonnull() -> Bool {
    fatalError("Pixar.TfRefBase has no TfRefPtr type")
  }
}

extension Pixar.TfAnyWeakPtr: Equatable {}
extension Pixar.TfType: Equatable {}
extension Pixar.TfRefBase: Equatable {
  public static func ==(lhs: Pixar.TfRefBase, rhs: Pixar.TfRefBase) -> Bool {
    // __Overlay.operatorEqualsEquals(lhs, rhs)
    false
  }
}

extension Pixar.TfSimpleRefBase: Equatable {
  public static func ==(lhs: Pixar.TfSimpleRefBase, rhs: Pixar.TfSimpleRefBase) -> Bool {
    // __Overlay.operatorEqualsEquals(lhs, rhs)
    false
  }
}

extension Pixar.TfSimpleRefBase: Overlay._SwiftUSDReferenceTypeProtocol {
    public var _address: UnsafeMutableRawPointer {
      var mutableSelf = self
      return withUnsafeMutablePointer(to: &mutableSelf) {
        UnsafeMutableRawPointer($0)
      }
    }
  
    public typealias _SelfType = Pixar.TfSimpleRefBase
}
// extension Pixar.TfSimpleRefBase: Overlay._TfRefBaseProtocol {}
// extension __SwiftUSD_Typedef___ZN3Pixar15TfSimpleRefBaseE_RefPtr: Overlay._TfRefPtrProtocol {
//   public typealias _TfRefBaseType = Pixar.TfSimpleRefBase
// }
// extension __SwiftUSD_Typedef___ZN3Pixar15TfSimpleRefBaseE_ConstRefPtr: Overlay._TfConstRefPtrProtocol {
//   public typealias _TfRefBaseType = Pixar.TfSimpleRefBase
// }


extension Pixar.TfRefBase: Overlay._SwiftUSDReferenceTypeProtocol {
  public var _address: UnsafeMutableRawPointer {
    var mutableSelf = self
    return withUnsafeMutablePointer(to: &mutableSelf) {
      UnsafeMutableRawPointer($0)
    }
  }

  public typealias _SelfType = Pixar.TfRefBase
}

extension Pixar.UsdStage: Equatable {
  public static func ==(lhs: Pixar.UsdStage, rhs: Pixar.UsdStage) -> Bool {
    // __Overlay.operatorEqualsEquals(lhs, rhs)
    false
  }
}

extension Pixar.UsdStage: Overlay._SwiftUSDReferenceTypeProtocol {
  public typealias _SelfType = Pixar.UsdStage
}

extension Pixar.UsdStage: Overlay._TfRefBaseProtocol {}
extension __SwiftUSD_Typedef___ZN3Pixar8UsdStageE_RefPtr: Overlay._TfRefPtrProtocol {
  public typealias _TfRefBaseType = Pixar.UsdStage
}

extension __SwiftUSD_Typedef___ZN3Pixar8UsdStageE_ConstRefPtr: Overlay._TfConstRefPtrProtocol {
  public typealias _TfRefBaseType = Pixar.UsdStage
}

extension Pixar.UsdStage: Overlay._TfWeakBaseProtocol {}
extension __SwiftUSD_Typedef___ZN3Pixar8UsdStageE_WeakPtr: Overlay._TfWeakPtrProtocol {
  public typealias _TfWeakBaseType = Pixar.UsdStage
}

extension __SwiftUSD_Typedef___ZN3Pixar8UsdStageE_ConstWeakPtr: Overlay._TfConstWeakPtrProtocol {
  public typealias _TfWeakBaseType = Pixar.UsdStage
}
