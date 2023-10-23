//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Metal/NSPrivate.hpp
//
// Copyright 2020-2023 Apple Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AppKitDefines.hpp"

#include <objc/runtime.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _APPKIT_PRIVATE_CLS(symbol) (Private::Class::s_k##symbol)
#define _APPKIT_PRIVATE_SEL(accessor) (Private::Selector::s_k##accessor)

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(APPKIT_PRIVATE_IMPLEMENTATION)

#ifdef METALCPP_SYMBOL_VISIBILITY_HIDDEN
#define _APPKIT_PRIVATE_VISIBILITY __attribute__((visibility("hidden")))
#else
#define _APPKIT_PRIVATE_VISIBILITY __attribute__((visibility("default")))
#endif // METALCPP_SYMBOL_VISIBILITY_HIDDEN

#define _APPKIT_PRIVATE_IMPORT __attribute__((weak_import))

#ifdef __OBJC__
#define _APPKIT_PRIVATE_OBJC_LOOKUP_CLASS(symbol) ((__bridge void*)objc_lookUpClass(#symbol))
#define _APPKIT_PRIVATE_OBJC_GET_PROTOCOL(symbol) ((__bridge void*)objc_getProtocol(#symbol))
#else
#define _APPKIT_PRIVATE_OBJC_LOOKUP_CLASS(symbol) objc_lookUpClass(#symbol)
#define _APPKIT_PRIVATE_OBJC_GET_PROTOCOL(symbol) objc_getProtocol(#symbol)
#endif // __OBJC__

#define _APPKIT_PRIVATE_DEF_CLS(symbol) void* s_k##symbol _APPKIT_PRIVATE_VISIBILITY = _APPKIT_PRIVATE_OBJC_LOOKUP_CLASS(symbol)
#define _APPKIT_PRIVATE_DEF_PRO(symbol) void* s_k##symbol _APPKIT_PRIVATE_VISIBILITY = _APPKIT_PRIVATE_OBJC_GET_PROTOCOL(symbol)
#define _APPKIT_PRIVATE_DEF_SEL(accessor, symbol) SEL s_k##accessor _APPKIT_PRIVATE_VISIBILITY = sel_registerName(symbol)

#include <dlfcn.h>
#define NS_DEF_FUNC( name, signature ) \
    using Fn##name = signature; \
    Fn##name name = reinterpret_cast< Fn##name >( dlsym( RTLD_DEFAULT, #name ) )

namespace NS::Private
{
    template <typename _Type>
    inline _Type const LoadSymbol(const char* pSymbol)
    {
        const _Type* pAddress = static_cast<_Type*>(dlsym(RTLD_DEFAULT, pSymbol));

        return pAddress ? *pAddress : nullptr;
    }
} // NS::Private

#if defined(__MAC_10_16) || defined(__MAC_11_0) || defined(__MAC_12_0) || defined(__MAC_13_0) || defined(__MAC_14_0) || defined(__IPHONE_14_0) || defined(__IPHONE_15_0) || defined(__IPHONE_16_0) || defined(__IPHONE_17_0) || defined(__TVOS_14_0) || defined(__TVOS_15_0) || defined(__TVOS_16_0) || defined(__TVOS_17_0)

#define _APPKIT_PRIVATE_DEF_STR(type, symbol)                  \
    _APPKIT_EXTERN type const NS##symbol _APPKIT_PRIVATE_IMPORT; \
    type const                         NS::symbol = (nullptr != &NS##symbol) ? NS##symbol : nullptr

#define _APPKIT_PRIVATE_DEF_CONST(type, symbol)              \
    _APPKIT_EXTERN type const NS##symbol _APPKIT_PRIVATE_IMPORT; \
    type const                         NS::symbol = (nullptr != &NS##symbol) ? NS##symbol : nullptr

#define _APPKIT_PRIVATE_DEF_WEAK_CONST(type, symbol) \
    _APPKIT_EXTERN type const NS##symbol;    \
    type const             NS::symbol = Private::LoadSymbol<type>("NS" #symbol)

#else

#define _APPKIT_PRIVATE_DEF_STR(type, symbol) \
    _APPKIT_EXTERN type const NS##symbol;    \
    type const             NS::symbol = Private::LoadSymbol<type>("NS" #symbol)

#define _APPKIT_PRIVATE_DEF_CONST(type, symbol) \
    _APPKIT_EXTERN type const NS##symbol;    \
    type const             NS::symbol = Private::LoadSymbol<type>("NS" #symbol)

#define _APPKIT_PRIVATE_DEF_WEAK_CONST(type, symbol) _APPKIT_PRIVATE_DEF_CONST(type, symbol)

#endif // defined(__MAC_10_16) || defined(__MAC_11_0) || defined(__MAC_12_0) || defined(__MAC_13_0) || defined(__MAC_14_0) || defined(__IPHONE_14_0) || defined(__IPHONE_15_0) || defined(__IPHONE_16_0) || defined(__IPHONE_17_0) || defined(__TVOS_14_0) || defined(__TVOS_15_0) || defined(__TVOS_16_0) || defined(__TVOS_17_0)

#else

#define _APPKIT_PRIVATE_DEF_CLS(symbol) extern void* s_k##symbol
#define _APPKIT_PRIVATE_DEF_PRO(symbol) extern void* s_k##symbol
#define _APPKIT_PRIVATE_DEF_SEL(accessor, symbol) extern SEL s_k##accessor
#define _APPKIT_PRIVATE_DEF_STR(type, symbol) extern type const NS::symbol
#define _APPKIT_PRIVATE_DEF_CONST(type, symbol) extern type const NS::symbol
#define _APPKIT_PRIVATE_DEF_WEAK_CONST(type, symbol) extern type const NS::symbol

#endif // APPKIT_PRIVATE_IMPLEMENTATION

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
  namespace Private
  {
    namespace Class
    {
      _APPKIT_PRIVATE_DEF_CLS(NSOpenGLContext);
      _APPKIT_PRIVATE_DEF_CLS(NSOpenGLPixelBuffer);
    } // Class
  } // Private
} // NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
  namespace Private
  {
    namespace Protocol
    {
      _APPKIT_PRIVATE_DEF_PRO(NSCoding);
      _APPKIT_PRIVATE_DEF_PRO(NSLocking);
    } // Protocol
  } // Private
} // NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
  namespace Private
  {
    namespace Selector
    {
      _APPKIT_PRIVATE_DEF_SEL(initWithFormat_shareContext,
          "initWithFormat:shareContext:");
      _APPKIT_PRIVATE_DEF_SEL(currentContext,
          "currentContext");
    } // Class
  } // Private
} // NS

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
