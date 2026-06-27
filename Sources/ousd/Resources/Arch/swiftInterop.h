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
#define SWIFT_SELF_CONTAINED __attribute__((swift_attr("import_owned")))
#endif /* SWIFT_SELF_CONTAINED */

#if !defined(SWIFT_RETURNS_INDEPENDENT_VALUE)
#define SWIFT_RETURNS_INDEPENDENT_VALUE __attribute__((swift_attr("import_unsafe")))
#endif /* SWIFT_RETURNS_INDEPENDENT_VALUE */

#if !defined(_CXX_INTEROP_STRINGIFY)
#define _CXX_INTEROP_STRINGIFY(_x) #_x
#endif /* _CXX_INTEROP_STRINGIFY */

#if !defined(_CXX_INTEROP_CONCAT_)
#define _CXX_INTEROP_CONCAT_(a,b,c,d,e,f,g,i,j,k,l,m,n,o,p,...)         \
  #a "," #b "," #c "," #d "," #e "," #f "," #g "," #i "," #j "," #k "," \
  #l "," #m "," #n "," #o "," #p
#define _CXX_INTEROP_CONCAT(...) \
  _CXX_INTEROP_CONCAT_(__VA_ARGS__,,,,,,,,,,,,,,,,,)
#endif /* _CXX_INTEROP_CONCAT_ */

#if !defined(SWIFT_SHARED_REFERENCE)
#define SWIFT_SHARED_REFERENCE(_retain, _release)                                \
  __attribute__((swift_attr("import_reference")))                          \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:_retain))))      \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:_release))))
#endif /* SWIFT_SHARED_REFERENCE */

#if !defined(SWIFT_RETURNS_RETAINED)
#define SWIFT_RETURNS_RETAINED __attribute__((swift_attr("returns_retained"))) __attribute__((cf_returns_retained))
#endif /* SWIFT_RETURNS_RETAINED */

#if !defined(SWIFT_RETURNS_UNRETAINED)
#define SWIFT_RETURNS_UNRETAINED __attribute__((swift_attr("returns_unretained"))) __attribute__((cf_returns_not_retained))
#endif /* SWIFT_RETURNS_UNRETAINED */

#if !defined(SWIFT_IMMORTAL_REFERENCE)
#define SWIFT_IMMORTAL_REFERENCE                                                \
  __attribute__((swift_attr("import_reference")))                         \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:immortal))))    \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:immortal))))
#endif /* SWIFT_IMMORTAL_REFERENCE */

#if !defined(SWIFT_UNSAFE_REFERENCE)
#define SWIFT_UNSAFE_REFERENCE                                                  \
  __attribute__((swift_attr("import_reference")))                         \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(retain:immortal))))    \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(release:immortal))))
#endif /* SWIFT_UNSAFE_REFERENCE */

#if !defined(SWIFT_NAME)
#define SWIFT_NAME(_name) __attribute__((swift_name(#_name)))
#endif /* SWIFT_NAME */

#if !defined(SWIFT_CONFORMS_TO_PROTOCOL)
#define SWIFT_CONFORMS_TO_PROTOCOL(_moduleName_protocolName) \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(conforms_to:_moduleName_protocolName))))
#endif /* SWIFT_CONFORMS_TO_PROTOCOL */

#if !defined(SWIFT_COMPUTED_PROPERTY)
#define SWIFT_COMPUTED_PROPERTY \
  __attribute__((swift_attr("import_computed_property")))
#endif /* SWIFT_COMPUTED_PROPERTY */

#if !defined(SWIFT_MUTATING)
#define SWIFT_MUTATING \
  __attribute__((swift_attr("mutating")))
#endif /* SWIFT_MUTATING */

#if !defined(SWIFT_UNCHECKED_SENDABLE)
#define SWIFT_UNCHECKED_SENDABLE \
  __attribute__((swift_attr("@Sendable")))
#endif /* SWIFT_UNCHECKED_SENDABLE */

#if !defined(SWIFT_NONCOPYABLE)
#define SWIFT_NONCOPYABLE \
  __attribute__((swift_attr("~Copyable")))
#endif /* SWIFT_NONCOPYABLE */

#if !defined(SWIFT_NONCOPYABLE_WITH_DESTROY)
#define SWIFT_NONCOPYABLE_WITH_DESTROY(_destroy) \
  __attribute__((swift_attr("~Copyable"))) \
  __attribute__((swift_attr(_CXX_INTEROP_STRINGIFY(destroy:_destroy))))
#endif /* SWIFT_NONCOPYABLE_WITH_DESTROY */

#if !defined(SWIFT_COPYABLE_IF)
#define SWIFT_COPYABLE_IF(...) \
  __attribute__((swift_attr("copyable_if:" _CXX_INTEROP_CONCAT(__VA_ARGS__))))
#endif /* SWIFT_COPYABLE_IF */

#if !defined(SWIFT_NONESCAPABLE)
#define SWIFT_NONESCAPABLE \
  __attribute__((swift_attr("~Escapable")))
#endif /* SWIFT_NONESCAPABLE */

#if !defined(SWIFT_ESCAPABLE)
#define SWIFT_ESCAPABLE \
  __attribute__((swift_attr("Escapable")))
#endif /* SWIFT_ESCAPABLE */

#if !defined(SWIFT_ESCAPABLE_IF)
#define SWIFT_ESCAPABLE_IF(...) \
  __attribute__((swift_attr("escapable_if:" _CXX_INTEROP_CONCAT(__VA_ARGS__))))
#endif /* SWIFT_ESCAPABLE_IF */

#if !defined(SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT)
#define SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT \
  __attribute__((swift_attr("returned_as_unretained_by_default")))
#endif /* SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT */

#if !defined(SWIFT_PRIVATE_FILEID)
#define SWIFT_PRIVATE_FILEID(_fileID) \
  __attribute__((swift_attr("private_fileid:" _fileID)))
#endif /* SWIFT_PRIVATE_FILEID */

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

#if !defined(SWIFT_NONCOPYABLE_WITH_DESTROY)
#define SWIFT_NONCOPYABLE_WITH_DESTROY(_destroy)
#endif // SWIFT_NONCOPYABLE_WITH_DESTROY

#if !defined(SWIFT_COPYABLE_IF)
#define SWIFT_COPYABLE_IF(...)
#endif // SWIFT_COPYABLE_IF

#if !defined(SWIFT_NONESCAPABLE)
#define SWIFT_NONESCAPABLE
#endif // SWIFT_NONESCAPABLE

#if !defined(SWIFT_ESCAPABLE)
#define SWIFT_ESCAPABLE
#endif // SWIFT_ESCAPABLE

#if !defined(SWIFT_ESCAPABLE_IF)
#define SWIFT_ESCAPABLE_IF(...)
#endif // SWIFT_ESCAPABLE_IF

#if !defined(SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT)
#define SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT
#endif // SWIFT_RETURNED_AS_UNRETAINED_BY_DEFAULT

#if !defined(SWIFT_PRIVATE_FILEID)
#define SWIFT_PRIVATE_FILEID(_fileID)
#endif // SWIFT_PRIVATE_FILEID

#if !defined(SWIFT_RETURNS_RETAINED)
#define SWIFT_RETURNS_RETAINED
#endif // SWIFT_RETURNS_RETAINED

#if !defined(SWIFT_RETURNS_UNRETAINED)
#define SWIFT_RETURNS_UNRETAINED
#endif // SWIFT_RETURNS_UNRETAINED

#endif /* !_CXX_INTEROP_HAS_ATTRIBUTE */

#if defined(_CXX_INTEROP_HAS_ATTRIBUTE)
#undef _CXX_INTEROP_HAS_ATTRIBUTE
#endif /* _CXX_INTEROP_HAS_ATTRIBUTE */

// clang-format on

#endif /* __PXR_BASE_ARCH_SWIFT_INTEROP_H__ */
