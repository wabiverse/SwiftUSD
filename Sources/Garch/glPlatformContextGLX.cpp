//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file glPlatformContext.cpp
#if defined(__ANDROID__)

#include "Garch/glPlatformContext.h"
#include "Tf/hash.h"

PXR_NAMESPACE_OPEN_SCOPE

//
// GarchGLXContextState (EGL-backed on Android)
//

GarchGLXContextState::GarchGLXContextState()
    : display(eglGetCurrentDisplay()),
      drawable(eglGetCurrentSurface(EGL_DRAW)),
      context(eglGetCurrentContext()),
      _defaultCtor(true)
{
  // Do nothing
}

GarchGLXContextState::GarchGLXContextState(EGLDisplay display_,
                                           EGLSurface drawable_,
                                           EGLContext context_)
    : display(display_), drawable(drawable_), context(context_), _defaultCtor(false)
{
  // Do nothing
}

bool GarchGLXContextState::operator==(const GarchGLXContextState &rhs) const
{
  return display == rhs.display && drawable == rhs.drawable && context == rhs.context;
}

size_t GarchGLXContextState::GetHash() const
{
  return TfHash::Combine(display, drawable, context);
}

bool GarchGLXContextState::IsValid() const
{
  return display != EGL_NO_DISPLAY &&
         drawable != EGL_NO_SURFACE &&
         context  != EGL_NO_CONTEXT;
}

void GarchGLXContextState::MakeCurrent()
{
  if (IsValid()) {
    eglMakeCurrent(display, drawable, drawable, context);
  }
  else if (_defaultCtor) {
    DoneCurrent();
  }
}

void GarchGLXContextState::DoneCurrent()
{
  EGLDisplay dpy = eglGetCurrentDisplay();
  if (dpy != EGL_NO_DISPLAY) {
    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  }
}

GarchGLPlatformContextState GarchGetNullGLPlatformContextState()
{
  return GarchGLXContextState(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

PXR_NAMESPACE_CLOSE_SCOPE

#elif defined(__linux__)

#include "Garch/glPlatformContext.h"
#include "Tf/hash.h"

PXR_NAMESPACE_OPEN_SCOPE

//
// GarchGLXContextState
//

GarchGLXContextState::GarchGLXContextState()
    : display(glXGetCurrentDisplay()),
      drawable(glXGetCurrentDrawable()),
      context(glXGetCurrentContext()),
      _defaultCtor(true)
{
  // Do nothing
}

GarchGLXContextState::GarchGLXContextState(Display *display_,
                                           GLXDrawable drawable_,
                                           GLXContext context_)
    : display(display_), drawable(drawable_), context(context_), _defaultCtor(false)
{
  // Do nothing
}

bool GarchGLXContextState::operator==(const GarchGLXContextState &rhs) const
{
  return display == rhs.display && drawable == rhs.drawable && context == rhs.context;
}

size_t GarchGLXContextState::GetHash() const
{
  return TfHash::Combine(display, drawable, context);
}

bool GarchGLXContextState::IsValid() const
{
  return display && drawable && context;
}

void GarchGLXContextState::MakeCurrent()
{
  if (IsValid()) {
    glXMakeCurrent(display, drawable, context);
  }
  else if (_defaultCtor) {
    DoneCurrent();
  }
}

void GarchGLXContextState::DoneCurrent()
{
  if (Display *display = glXGetCurrentDisplay()) {
    glXMakeCurrent(display, None, NULL);
  }
}

GarchGLPlatformContextState GarchGetNullGLPlatformContextState()
{
  return GarchGLXContextState(NULL, None, NULL);
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(__ANDROID__) || defined(__linux__)
