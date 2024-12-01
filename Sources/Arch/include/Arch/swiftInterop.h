/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ----------------------------------------------------------------
 * Portions of this file derive from an original work of Apple Inc.
 * from the swift/bridging file.
 *
 * This source file is apart of the Swift.org open source project &
 * under the terms of the Apache License version 2.0 with a Runtime
 * Library Exception modification.
 *
 * See more license information here: https://swift.org/LICENSE.txt
 *
 * See the list of Swift project authors by visiting this resource:
 * https://swift.org/CONTRIBUTORS.txt
 *
 *     Copyright (C) 2017 Apple Inc. and the Swift project authors.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ----------------------------------------------------------------- */
#ifndef __PXR_BASE_ARCH_SWIFT_INTEROP_H__
#define __PXR_BASE_ARCH_SWIFT_INTEROP_H__

/**
 * @brief
 * This file provides common utilities and annotations that are
 * useful for C++ codebases that interoperate with Swift.
 */

// clang-format off

#ifdef __APPLE__
# if __has_include(<swift/bridging>)
#  include <swift/bridging>
# endif /* __has_include(<swift/bridging>) */
#endif /* __APPLE__ */

/** ----------
 * 
 * Carefully define the swift cxx interop macros, by first checking
 * if they have already been defined by the Swift compiler, if not,
 * then we define them ourselves.
 *                                                    ---------- */

#if defined(__has_attribute) && !defined(_CXX_INTEROP_HAS_ATTRIBUTE)
#define _CXX_INTEROP_HAS_ATTRIBUTE(x) __has_attribute(x)
#elif !defined(_CXX_INTEROP_HAS_ATTRIBUTE)
#define _CXX_INTEROP_HAS_ATTRIBUTE(x) 0
#endif

#if _CXX_INTEROP_HAS_ATTRIBUTE(swift_attr)

#if !defined(SWIFT_SELF_CONTAINED)
/// Specifies that a C++ `class` or `struct` owns and controls the lifetime of all
/// of the objects it references. Such type should not reference any objects whose
/// lifetime is controlled externally. This annotation allows Swift to import methods
/// that return a `class` or `struct` type that is annotated with this macro.
#define SWIFT_SELF_CONTAINED __attribute__((swift_attr("import_owned")))
#endif /* SWIFT_SELF_CONTAINED */

#if !defined(SWIFT_RETURNS_INDEPENDENT_VALUE)
/// Specifies that a C++ method returns a value that is presumed to contain
/// objects whose lifetime is not dependent on `this` or other parameters passed
/// to the method.
#define SWIFT_RETURNS_INDEPENDENT_VALUE __attribute__((swift_attr("import_unsafe")))
#endif /* SWIFT_RETURNS_INDEPENDENT_VALUE */

#if !defined(_CXX_INTEROP_STRINGIFY)
#define _CXX_INTEROP_STRINGIFY(_x) #_x
#endif /* _CXX_INTEROP_STRINGIFY */

#if !defined(SWIFT_SHARED_REFERENCE)
/// Specifies that a C++ `class` or `struct` is reference-counted using
/// the given `retain` and `release` functions. This annotation lets Swift import
/// such a type as reference counted type in Swift, taking advantage of Swift's
/// automatic reference counting.
///
/// This example shows how to use this macro to let Swift know that
/// a non-copyable reference counted C++ class can be imported as a reference counted type in Swift:
///  ```c++
///    class SWIFT_SHARED_REFERENCE(retainSharedObject, releaseSharedObject)
///    SharedObject : NonCopyable, IntrusiveReferenceCounted<SharedObject> {
///    public:
///      static SharedObject* create();
///      void doSomething();
///    };
///
///    void retainSharedObject(SharedObject *);
///    void releaseSharedObject(SharedObject *);
///  ```
///
///  Then, the Swift programmer would be able to use it in the following manner:
///
///  ```swift
///    let object = SharedObject.create()
///    object.doSomething()
///    // The Swift compiler will release object here.
///  ```
#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))
#endif /* SWIFT_SHARED_REFERENCE */

#if !defined(SWIFT_IMMORTAL_REFERENCE)
/// Specifies that a C++ `class` or `struct` is a reference type whose lifetime
/// is presumed to be immortal, i.e. the reference to such object is presumed to
/// always be valid. This annotation lets Swift import such a type as a reference
/// type in Swift.
////
/// This example shows how to use this macro to let Swift know that
/// a non-copyable singleton C++ class can be imported as a reference type in Swift:
///  ```c++
///    class SWIFT_IMMORTAL_REFERENCE
///    LoggerSingleton : NonCopyable {
///    public:
///      static LoggerSingleton &getInstance();
///      void log(int x);
///    };
///  ```
///
///  Then, the Swift programmer would be able to use it in the following manner:
///
///  ```swift
///    let logger = LoggerSingleton.getInstance()
///    logger.log(123)
///  ```
#define SWIFT_IMMORTAL_REFERENCE                                                \
  __attribute__((swift_attr("import_reference")))                         \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:immortal))))    \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:immortal))))
#endif /* SWIFT_IMMORTAL_REFERENCE */

#if !defined(SWIFT_UNSAFE_REFERENCE)
/// Specifies that a C++ `class` or `struct` is a reference type whose lifetime
/// is not managed automatically. The programmer must validate that any reference
/// to such object is valid themselves. This annotation lets Swift import such a type as a reference type in Swift.
#define SWIFT_UNSAFE_REFERENCE                                                  \
  __attribute__((swift_attr("import_reference")))                         \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:immortal))))    \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:immortal))))
#endif /* SWIFT_UNSAFE_REFERENCE */

#if !defined(SWIFT_NAME)
/// Specifies a name that will be used in Swift for this declaration instead of its original name.
#define SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#endif /* SWIFT_NAME */

#if !defined(SWIFT_CONFORMS_TO_PROTOCOL)
/// Specifies that a specific C++ `class` or `struct` conforms to a
/// a specific Swift protocol.
///
/// This example shows how to use this macro to conform a class template to a Swift protocol:
///  ```
///    template<class T>
///    class SWIFT_CONFORMS_TO_PROTOCOL(SwiftModule.ProtocolName)
///    CustomClass {};
///  ```
#define SWIFT_CONFORMS_TO_PROTOCOL(_moduleName_protocolName) \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(conforms_to:_moduleName_protocolName))))
#endif /* SWIFT_CONFORMS_TO_PROTOCOL */

#if !defined(SWIFT_COMPUTED_PROPERTY)
/// Specifies that a specific C++ method should be imported as a computed
/// property. If this macro is specified on a getter, a getter will be
/// synthesized. If this macro is specified on a setter, both a getter and
/// setter will be synthesized.
///
/// For example:
///  ```
///    int getX() SWIFT_COMPUTED_PROPERTY;
///  ```
/// Will be imported as `var x: CInt {...}`.
#define SWIFT_COMPUTED_PROPERTY \
  __attribute__((swift_attr("import_computed_property")))
#endif /* SWIFT_COMPUTED_PROPERTY */

#if !defined(SWIFT_MUTATING)
/// Specifies that a specific **constant** C++ member function should be imported as
/// `mutating` Swift method. This annotation should be added to constant C++ member functions
/// that mutate `mutable` fields in a C++ object, to let Swift know that this function is still mutating
/// and thus that it should become a `mutating` method in Swift.
#define SWIFT_MUTATING \
  __attribute__((swift_attr("mutating")))
#endif /* SWIFT_MUTATING */

#if !defined(SWIFT_UNCHECKED_SENDABLE)
/// Specifies that a specific c++ type such class or struct should be imported as type marked 
/// as `@unchecked Sendable` type in swift. If this annotation is used, the type is therefore allowed to
/// use safely across async contexts.
///
/// For example 
/// ```
///   class SWIFT_UNCHECKED_SENDABLE CustomUserType
///   { ... } 
/// ``` 
/// Will be imported as `struct CustomUserType: @unchecked Sendable`
#define SWIFT_UNCHECKED_SENDABLE \
  __attribute__((swift_attr("@Sendable")))
#endif /* SWIFT_UNCHECKED_SENDABLE */

#if !defined(SWIFT_NONCOPYABLE)
/// Specifies that a specific c++ type such class or struct should be imported
/// as a non-copyable Swift value type.
#define SWIFT_NONCOPYABLE \
  __attribute__((swift_attr("~Copyable")))
#endif /* SWIFT_NONCOPYABLE */

#else /* !_CXX_INTEROP_HAS_ATTRIBUTE */

// Empty defines for compilers that don't support `attribute(swift_attr)`.

#if !defined(SWIFT_SELF_CONTAINED)
#define SWIFT_SELF_CONTAINED
#endif // SWIFT_SELF_CONTAINED

#if !defined(SWIFT_RETURNS_INDEPENDENT_VALUE)
#define SWIFT_RETURNS_INDEPENDENT_VALUE
#endif // SWIFT_RETURNS_INDEPENDENT_VALUE

#if !defined(SWIFT_SHARED_REFERENCE)
#define SWIFT_SHARED_REFERENCE(_retain, _release)
#endif // SWIFT_SHARED_REFERENCE

#if !defined(SWIFT_IMMORTAL_REFERENCE)
#define SWIFT_IMMORTAL_REFERENCE
#endif // SWIFT_IMMORTAL_REFERENCE

#if !defined(SWIFT_UNSAFE_REFERENCE)
#define SWIFT_UNSAFE_REFERENCE
#endif // SWIFT_UNSAFE_REFERENCE

#if !defined(SWIFT_NAME)
#define SWIFT_NAME(_name)
#endif // SWIFT_NAME

#if !defined(SWIFT_CONFORMS_TO_PROTOCOL)
#define SWIFT_CONFORMS_TO_PROTOCOL(_moduleName_protocolName)
#endif // SWIFT_CONFORMS_TO_PROTOCOL

#if !defined(SWIFT_COMPUTED_PROPERTY)
#define SWIFT_COMPUTED_PROPERTY
#endif // SWIFT_COMPUTED_PROPERTY

#if !defined(SWIFT_MUTATING)
#define SWIFT_MUTATING
#endif // SWIFT_MUTATING

#if !defined(SWIFT_UNCHECKED_SENDABLE)
#define SWIFT_UNCHECKED_SENDABLE
#endif // SWIFT_UNCHECKED_SENDABLE

#if !defined(SWIFT_NONCOPYABLE)
#define SWIFT_NONCOPYABLE
#endif // SWIFT_NONCOPYABLE

#endif /* !_CXX_INTEROP_HAS_ATTRIBUTE */

#if defined(_CXX_INTEROP_HAS_ATTRIBUTE)
#undef _CXX_INTEROP_HAS_ATTRIBUTE
#endif /* _CXX_INTEROP_HAS_ATTRIBUTE */

// clang-format on

#endif /* __PXR_BASE_ARCH_SWIFT_INTEROP_H__ */
