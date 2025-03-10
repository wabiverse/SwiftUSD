//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Arch/defines.h"

#if defined(__APPLE__)
#  include "pxr/pxrns.h"
#  include "Garch/GarchDarwin/glPlatformContextDarwin.h"
#  import <Foundation/Foundation.h>
#  if defined(PXR_GL_SUPPORT_ENABLED)
#    if defined(ARCH_OS_OSX)
#      import <AppKit/NSOpenGL.h>
typedef NSOpenGLContext NSGLContext;
#    elif defined(ARCH_OS_IPHONE)
#      import <UIKit/UIKit.h>
typedef EAGLContext NSGLContext;
#    endif // defined(ARCH_OS_IPHONE)
#  else // !defined(PXR_GL_SUPPORT_ENABLED)
typedef void* NSGLContext;
#  endif // defined(PXR_GL_SUPPORT_ENABLED)

PXR_NAMESPACE_OPEN_SCOPE

class GarchNSGLContextState::Detail
{
public:
    Detail() {
#if defined(PXR_GL_SUPPORT_ENABLED)
        context = [NSGLContext currentContext];
#else
        context = nil;
#endif
    }
    Detail(NullState) {
        context = nil;
    }
    ~Detail() {
        context = nil; // garbage collect
    }
    NSGLContext * context;
};

/// Construct with the current state.
GarchNSGLContextState::GarchNSGLContextState()
  : _detail(std::make_shared<GarchNSGLContextState::Detail>())
{
}

GarchNSGLContextState::GarchNSGLContextState(NullState)
  : _detail(std::make_shared<GarchNSGLContextState::Detail>(
                NullState::nullstate))
{
}

/// Construct with the given state.
//GarchNSGLContextState(const GarchNSGLContextState& copy);

/// Compare for equality.
bool
GarchNSGLContextState::operator==(const GarchNSGLContextState& rhs) const
{
    return rhs._detail->context == _detail->context;
}

/// Returns a hash value for the state.
size_t
GarchNSGLContextState::GetHash() const
{
    return static_cast<size_t>(reinterpret_cast<uintptr_t>(_detail->context));
}

/// Returns \c true if the context state is valid.
bool
GarchNSGLContextState::IsValid() const
{
    return _detail->context != nil;
}

/// Make the context current.
void
GarchNSGLContextState::MakeCurrent()
{
#if defined(PXR_GL_SUPPORT_ENABLED)
#  if defined(ARCH_OS_IPHONE)
    [EAGLContext setCurrentContext:_detail->context];
#  else // !defined(ARCH_OS_IPHONE)
    [_detail->context makeCurrentContext];
#  endif // defined(ARCH_OS_IPHONE)
#endif // defined(PXR_GL_SUPPORT_ENABLED)
}

/// Make no context current.
void
GarchNSGLContextState::DoneCurrent()
{
#if defined(PXR_GL_SUPPORT_ENABLED)
#  if defined(ARCH_OS_IPHONE)
    [EAGLContext setCurrentContext:nil];
#  else // !defined(ARCH_OS_IPHONE)
    [NSGLContext clearCurrentContext];
#  endif // defined(ARCH_OS_IPHONE)
#endif
}

GarchGLPlatformContextState
GarchGetNullGLPlatformContextState()
{
    return GarchNSGLContextState(GarchNSGLContextState::NullState::nullstate);
}

void *
GarchSelectCoreProfileMacVisual()
{
#if defined(ARCH_OS_OSX)
    NSOpenGLPixelFormatAttribute attribs[10];
    int c = 0;

    attribs[c++] = NSOpenGLPFAOpenGLProfile;
    attribs[c++] = NSOpenGLProfileVersion3_2Core;
    attribs[c++] = NSOpenGLPFADoubleBuffer;
    attribs[c++] = 0;

    return (__bridge void*)[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
#else // !defined(ARCH_OS_OSX)
    return NULL;
#endif // defined(ARCH_OS_OSX)
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif /* defined(__APPLE__) */
