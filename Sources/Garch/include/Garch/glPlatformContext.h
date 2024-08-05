//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H
#define PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H

/// \file garch/glPlatformContext.h

#include "Arch/defines.h"
#include "Garch/api.h"
#include <cstddef>
#include <functional>
#include <pxr/pxrns.h>

// Note: there may be cases in which you wish to build for GLX when you are
// not on Linux, so we have left this optional define, `WITH_GLX` which will
// override the platform detection and force the inclusion of GLX code.
#if defined(ARCH_OS_LINUX) || defined(WITH_GLX)

#  include "Garch/GarchGLX/glPlatformContextGLX.h"

#elif defined(ARCH_OS_DARWIN)

#  include "Garch/GarchDarwin/glPlatformContextDarwin.h"

#elif defined(ARCH_OS_WINDOWS)

#  include "Garch/GarchWindows/glPlatformContextWindows.h"

#else

#  error "Unknown platform"

#endif

PXR_NAMESPACE_OPEN_SCOPE

GARCH_API GarchGLPlatformContextState GarchGetNullGLPlatformContextState();

PXR_NAMESPACE_CLOSE_SCOPE

namespace std {
template<> struct hash<PXR_NS::GarchGLPlatformContextState> {
  inline size_t operator()(const PXR_NS::GarchGLPlatformContextState &x) const
  {
    return x.GetHash();
  }
};
}  // namespace std

#endif  // PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H
