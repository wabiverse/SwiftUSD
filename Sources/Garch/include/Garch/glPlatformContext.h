//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H
#define PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H

/// \file garch/glPlatformContext.h

#include "Arch/defines.h"
#include "Garch/api.h"
#include "pxr/pxrns.h"
#include <cstddef>
#include <functional>

#if defined(ARCH_OS_LINUX)

#  include "Garch/glPlatformContextGLX.h"

#elif defined(ARCH_OS_DARWIN)

#  include "Garch/glPlatformContextDarwin.h"

#elif defined(ARCH_OS_WINDOWS)

#  include "Garch/glPlatformContextWindows.h"

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
