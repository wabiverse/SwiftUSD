//===----------------------------------------------------------------------===//
// This source file is part of github.com/apple/SwiftUsd
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

import Foundation
@_exported import pxr
@_exported import USDOverlays

// MARK: SwiftUSDReferenceTypeProtocol definition

public extension Overlay {
  /// Protocol representing all foreign reference types in OpenUSD. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _SwiftUSDReferenceTypeProtocol: Equatable /* , Hashable, Comparable */ {
    /// A stand-in for `Self` that works around a compiler crash involving non-final FRT casting
    associatedtype _SelfType

    /// The address of the reference type
    var _address: UnsafeMutableRawPointer { get }
  }
}

public extension Overlay {
  /// Protocol representing immortal reference types in OpenUSD. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _SwiftUSDImmortalReferenceTypeProtocol: _SwiftUSDReferenceTypeProtocol {}
}

// MARK: TfRefBaseProtocol, TfRefPtrProtocol definition

public extension Overlay {
  /// Protocol representing `Pixar::TfRefBase` subclasses. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfRefBaseProtocol: _SwiftUSDReferenceTypeProtocol where _SelfType: _TfRefBaseProtocol {
    /// The type of `Pixar::TfRefPtr<Self>`
    associatedtype _TfRefPtrType: Overlay._TfRefPtrProtocol where _TfRefPtrType._TfRefBaseType == _SelfType
    /// The type of `Pixar::TfRefPtr<const Self>`
    associatedtype _TfConstRefPtrType: Overlay._TfConstRefPtrProtocol where _TfConstRefPtrType._TfRefBaseType == _SelfType

    /// Wraps `self` in a `Pixar::TfRefPtr`
    func _asRefPtrType() -> _TfRefPtrType
    /// Dereferences the `Pixar::TfRefPtr`, returning either `Self` or nil
    static func _fromRefPtrType(_ p: _TfRefPtrType) -> _SelfType?
    /// Dereferences the `Pixar::TfRefPtr`, returning either `Self` or nil
    static func _fromConstRefPtrType(_ p: _TfConstRefPtrType) -> _SelfType?

    // Performs a dynamic cast from the raw pointer
    // static func _fromRawPointer(_ p: UnsafeMutableRawPointer?) -> _SelfType?
  }

  /// Protocol representing `Pixar::TfRefPtr<T>` specializations. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfRefPtrProtocol {
    /// The type of `T`
    associatedtype _TfRefBaseType: Overlay._TfRefBaseProtocol where _TfRefBaseType._TfRefPtrType == Self
    /// Returns a `Self` pointing to null
    static func _nullPtr() -> Self
    /// Returns `true` if `self` is not pointing to null
    func _isNonnull() -> Bool
  }

  /// Protocol representing `Pixar::TfRefPtr<const T>` specializations. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfConstRefPtrProtocol {
    /// The type of `T`, without const qualification
    associatedtype _TfRefBaseType: Overlay._TfRefBaseProtocol where _TfRefBaseType._TfConstRefPtrType == Self
    /// Returns `true` is `self` is not pointing to null
    func _isNonnull() -> Bool
  }
}

// MARK: TfWeakBaseProtocol, TfWeakPtrProtocol definition

public extension Overlay {
  /// Protocol representing `Pixar::TfWeakBase` subclasses. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfWeakBaseProtocol: _SwiftUSDReferenceTypeProtocol where _SelfType: _TfWeakBaseProtocol {
    /// The type of `Pixar::TfWeakPtr<Self>`
    associatedtype _TfWeakPtrType: Overlay._TfWeakPtrProtocol where _TfWeakPtrType._TfWeakBaseType == _SelfType
    /// The type of `Pixar::TfWeakPtr<const Self>`
    associatedtype _TfConstWeakPtrType: Overlay._TfConstWeakPtrProtocol where _TfConstWeakPtrType._TfWeakBaseType == _SelfType

    /// Wraps `self` in a `Pixar::TfWeakPtr`
    func _asWeakPtrType() -> _TfWeakPtrType
    /// Dereferences the `Pixar::TfWeakPtr`, returning either `Self` or nil
    static func _fromWeakPtrType(_ p: _TfWeakPtrType) -> _SelfType?
    /// Dereferences the `Pixar::TfWeakPtr`, returning either `Self` or nil
    static func _fromConstWeakPtrType(_ p: _TfConstWeakPtrType) -> _SelfType?
  }

  /// Protocol representing `Pixar::TfWeakPtr<T>` specializations. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfWeakPtrProtocol {
    /// The type of `T`
    associatedtype _TfWeakBaseType: Overlay._TfWeakBaseProtocol where _TfWeakBaseType._TfWeakPtrType == Self
    /// Converts `self` to a `Pixar::TfAnyWeakPtr`
    func _asAnyWeakPtr() -> Pixar.TfAnyWeakPtr
    /// Converts the argument to `Self`, which may be null if dynamic casting failed
    static func _fromAnyWeakPtr(_ p: Pixar.TfAnyWeakPtr) -> Self
    /// Returns a `Self` pointing to null
    static func _nullPtr() -> Self
    /// Returns `true` if `self` is not pointing to null
    func _isNonnull() -> Bool
  }

  /// Protocol representing `Pixar::TfWeakPtr<const T>` specializations. Don't use this unless you know what you're doing
  @_documentation(visibility: public)
  protocol _TfConstWeakPtrProtocol {
    /// The type of `T`, without const qualification
    associatedtype _TfWeakBaseType: Overlay._TfWeakBaseProtocol where _TfWeakBaseType._TfConstWeakPtrType == Self
    /// Returns `true` is `self` is not pointing to null
    func _isNonnull() -> Bool
  }
}

public extension Overlay {
  /// Holds a `Pixar::TfWeakBase` subclass weakly
  @_documentation(visibility: public)
  struct WeakReferenceHolder<T: Overlay._TfWeakBaseProtocol>: Equatable /* , Hashable, Comparable */ where T._SelfType == T {
    /// Holds the argument weakly
    public init(value: T?) {
      _storage = Overlay.TfWeakPtr(value)
    }

    /// Backing storage
    var _storage: T._TfWeakPtrType

    /// The value being held weakly
    public var value: T? {
      get {
        Overlay.DereferenceOrNil(_storage)
      } set {
        _storage = Overlay.TfWeakPtr(newValue)
      }
    }

    public static func ==(lhs: Self, rhs: Self) -> Bool {
      lhs.value == rhs.value
    }

    // public func hash(into hasher: inout Hasher) {
    //   hasher.combine(value)
    // }

    // public static func <(lhs: Self, rhs: Self) -> Bool {
    //  switch (lhs.value, rhs.value) {
    //    case let (.some(l), .some(r)): return l < r
    //    case (nil, nil): return false
    //    default: return lhs.value == nil
    //  }
    // }
  }
}

// MARK: Pointer conversion functions

public extension Overlay {
  /// Dereferences a `Pixar::TfRefPtr<T>`. Crashes if the pointer is null
  static func Dereference<T: Overlay._TfRefPtrProtocol>(_ x: T) -> T._TfRefBaseType {
    Overlay.DereferenceOrNil(x)!
  }

  /// Dereferences a `Pixar::TfWeakPtr<T>`. Crashes if the pointer is null
  static func Dereference<T: Overlay._TfWeakPtrProtocol>(_ x: T) -> T._TfWeakBaseType {
    Overlay.DereferenceOrNil(x)!
  }

  /// Dereferences a `Pixar::TfAnyWeakPtr`. Crashes if the pointer is null or dynamic casting fails
  internal static func _Dereference<T: Overlay._TfWeakBaseProtocol>(_ x: Pixar.TfAnyWeakPtr, as: T.Type) -> T where T._SelfType == T {
    Overlay._DereferenceOrNil(x, as: T.self)!
  }

  /// Dereferences a `Pixar::TfRefPtr<const T>`. Crashes if the pointer is null
  static func Dereference<T: Overlay._TfConstRefPtrProtocol>(_ x: T) -> T._TfRefBaseType {
    Overlay.DereferenceOrNil(x)!
  }

  /// Dereferences a `Pixar::TfWeakPtr<const T>`. Crashes if the pointer is null
  static func Dereference<T: Overlay._TfConstWeakPtrProtocol>(_ x: T) -> T._TfWeakBaseType {
    Overlay.DereferenceOrNil(x)!
  }

  /// Dereferences a `Pixar::TfRefPtr<T>`, returning either `T` or `nil`
  static func DereferenceOrNil<T: Overlay._TfRefPtrProtocol>(_ x: T) -> T._TfRefBaseType? {
    T._TfRefBaseType._fromRefPtrType(x)
  }

  /// Dereferences a `Pixar::TfWeakPtr<T>`, returning either `T` (held strongly) or `nil`
  static func DereferenceOrNil<T: Overlay._TfWeakPtrProtocol>(_ x: T) -> T._TfWeakBaseType? {
    T._TfWeakBaseType._fromWeakPtrType(x)
  }

  /// Dereferences a `Pixar::TfAnyWeakPtr`, returning either `T` or `nil`. Returns `nil` if dynamic casting fails
  internal static func _DereferenceOrNil<T: Overlay._TfWeakBaseProtocol>(_ x: Pixar.TfAnyWeakPtr, as: T.Type) -> T? where T._SelfType == T {
    Overlay.DereferenceOrNil(Overlay._TfWeakPtr(x, pointingTo: T.self))
  }

  /// Dereferences a `Pixar::TfRefPtr<const T>`, returning either `T` (without const qualification) or `nil`
  static func DereferenceOrNil<T: Overlay._TfConstRefPtrProtocol>(_ x: T) -> T._TfRefBaseType? {
    T._TfRefBaseType._fromConstRefPtrType(x)
  }

  /// Dereferences a `Pixar::TfWeakPtr<const T>`, returning either `T` (without const qualification) or `nil`
  static func DereferenceOrNil<T: Overlay._TfConstWeakPtrProtocol>(_ x: T) -> T._TfWeakBaseType? {
    T._TfWeakBaseType._fromConstWeakPtrType(x)
  }

  /// Wraps the argument in a `Pixar::TfRefPtr<T>`
  static func TfRefPtr<T: Overlay._TfRefBaseProtocol>(_ x: T?) -> T._TfRefPtrType {
    x?._asRefPtrType() ?? ._nullPtr()
  }

  /// Wraps the argument in a `Pixar::TfRefPtr<T>`
  /// Disfavored overload to allow for passing nil as a literal in limited type inference contexts
  @_disfavoredOverload
  static func TfRefPtr<T: Overlay._TfRefPtrProtocol>(_ x: T._TfRefBaseType?) -> T {
    x?._asRefPtrType() ?? ._nullPtr()
  }

  // Converts a `Pixar::TfWeakPtr<T>` into a `Pixar::TfRefPtr<T>`
  // public static func TfRefPtr<T>(_ x: T) -> T._TfWeakBaseType._TfRefPtrType where T: Overlay._TfWeakPtrProtocol, T._TfWeakBaseType: Overlay._TfRefBaseProtocol { Overlay.TfRefPtr(Overlay.DereferenceOrNil(x)) }
  // Converts a `Pixar::TfAnyWeakPtr` into a `Pixar::TfRefPtr<T>`
  // internal static func _TfRefPtr<T>(_ x: Pixar.TfAnyWeakPtr, pointingTo: T.Type) -> T._TfRefPtrType where T: Overlay._TfRefBaseProtocol & Overlay._TfWeakBaseProtocol, T._SelfType == T { Overlay.TfRefPtr(Overlay._DereferenceOrNil(x, as: T.self)) }

  /// Wraps the argument in a `Pixar::TfWeakPtr<T>`
  static func TfWeakPtr<T: Overlay._TfWeakBaseProtocol>(_ x: T?) -> T._TfWeakPtrType {
    x?._asWeakPtrType() ?? ._nullPtr()
  }

  /// Wraps the argument in a `Pixar::TfWeakPtr<T>`
  /// Disfavored overload to allow for passing nil as a literal in limited type inference contexts
  @_disfavoredOverload
  static func TfWeakPtr<T: Overlay._TfWeakPtrProtocol>(_ x: T._TfWeakBaseType?) -> T {
    x?._asWeakPtrType() ?? ._nullPtr()
  }

  /// Converts a `Pixar::TfRefPtr<T>` into a `Pixar::TfWeakPtr<T>`
  static func TfWeakPtr<T: Overlay._TfRefPtrProtocol>(_ x: T) -> T._TfRefBaseType._TfWeakPtrType where T._TfRefBaseType: Overlay._TfWeakBaseProtocol {
    Overlay.TfWeakPtr(Overlay.DereferenceOrNil(x))
  }

  /// Converts a `Pixar::TfAnyWeakPtr` into a `Pixar::TfWeakPtr<T>`
  internal static func _TfWeakPtr<T: Overlay._TfWeakBaseProtocol>(_ x: Pixar.TfAnyWeakPtr, pointingTo: T.Type) -> T._TfWeakPtrType {
    T._TfWeakPtrType._fromAnyWeakPtr(x)
  }

  /// Wraps the argument in a `Pixar::TfAnyWeakPtr`
  internal static func _TfAnyWeakPtr<T: Overlay._TfWeakBaseProtocol>(_ x: T?) -> Pixar.TfAnyWeakPtr {
    Overlay._TfAnyWeakPtr(Overlay.TfWeakPtr(x))
  }

  /// Converts a `Pixar::TfRefPtr<T>` into a `Pixar::TfAnyWeakPtr`
  internal static func _TfAnyWeakPtr<T: Overlay._TfRefPtrProtocol>(_ x: T) -> Pixar.TfAnyWeakPtr where T._TfRefBaseType: Overlay._TfWeakBaseProtocol {
    Overlay._TfAnyWeakPtr(Overlay.TfWeakPtr(x))
  }

  /// Converts a `Pixar::TfWeakPtr<T>` into a `Pixar::TfAnyWeakPtr`
  internal static func _TfAnyWeakPtr<T: Overlay._TfWeakPtrProtocol>(_ x: T) -> Pixar.TfAnyWeakPtr {
    x._asAnyWeakPtr()
  }
}

public extension Overlay._TfRefPtrProtocol {
  @_documentation(visibility: internal)
  @available(*, unavailable, message: "`.pointee` is unsafe; use Overlay.Dereference(_:) instead")
  var pointee: _TfRefBaseType {
    fatalError()
  }
}

public extension Overlay._TfWeakPtrProtocol {
  @_documentation(visibility: internal)
  @available(*, unavailable, message: "`.pointee` is unsafe; use Overlay.Dereference(_:) instead")
  var pointee: _TfWeakBaseType {
    fatalError()
  }
}

public extension Overlay._TfConstRefPtrProtocol {
  @_documentation(visibility: internal)
  @available(*, unavailable, message: "`.pointee` is unsafe; use Overlay.Dereference(_:) instead")
  var pointee: _TfRefBaseType {
    fatalError()
  }
}

public extension Overlay._TfConstWeakPtrProtocol {
  @_documentation(visibility: internal)
  @available(*, unavailable, message: "`.pointee` is unsafe; use Overlay.Dereference(_:) instead")
  var pointee: _TfWeakBaseType {
    fatalError()
  }
}
