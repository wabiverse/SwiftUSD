//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Garch/glPlatformDebugContext.h"

#include "Arch/defines.h"
#include "Garch/glApi.h"
#include "Tf/diagnostic.h"
#include "Tf/getenv.h"

PXR_NAMESPACE_OPEN_SCOPE

/* static */
bool GarchGLPlatformDebugContext::IsEnabledDebugOutput()
{
  static bool isEnabledDebugOutput = TfGetenvBool("GLF_ENABLE_DEBUG_OUTPUT", false);
  return isEnabledDebugOutput;
}

/* static */
bool GarchGLPlatformDebugContext::IsEnabledCoreProfile()
{
  static bool isEnabledCoreProfile = TfGetenvBool("GLF_ENABLE_CORE_PROFILE", false);
  return isEnabledCoreProfile;
}

PXR_NAMESPACE_CLOSE_SCOPE

////////////////////////////////////////////////////////////
#if defined(ARCH_OS_LINUX)

#  include <GL/glx.h>
#  include <GL/glxtokens.h>
#  include <X11/Xlib.h>

PXR_NAMESPACE_OPEN_SCOPE

class GarchGLPlatformDebugContextPrivate {
 public:
  GarchGLPlatformDebugContextPrivate(int majorVersion,
                                     int minorVersion,
                                     bool coreProfile,
                                     bool directRendering);
  ~GarchGLPlatformDebugContextPrivate();

  void MakeCurrent();

  Display *_dpy;
  GLXContext _ctx;
};

GarchGLPlatformDebugContextPrivate::GarchGLPlatformDebugContextPrivate(int majorVersion,
                                                                       int minorVersion,
                                                                       bool coreProfile,
                                                                       bool directRendering)
    : _dpy(NULL), _ctx(NULL)
{
  Display *shareDisplay = glXGetCurrentDisplay();
  GLXContext shareContext = glXGetCurrentContext();

  int fbConfigId = 0;
  glXQueryContext(shareDisplay, shareContext, GLX_FBCONFIG_ID, &fbConfigId);
  int screen = 0;
  glXQueryContext(shareDisplay, shareContext, GLX_SCREEN, &screen);

  int configSpec[] = {
      GLX_FBCONFIG_ID,
      fbConfigId,
      None,
  };
  GLXFBConfig *configs = NULL;
  int configCount = 0;
  configs = glXChooseFBConfig(shareDisplay, screen, configSpec, &configCount);
  if (!TF_VERIFY(configCount > 0)) {
    return;
  }

  const int profile = coreProfile ? GLX_CONTEXT_CORE_PROFILE_BIT_ARB :
                                    GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

  int attribs[] = {
      GLX_CONTEXT_MAJOR_VERSION_ARB,
      majorVersion,
      GLX_CONTEXT_MINOR_VERSION_ARB,
      minorVersion,
      GLX_CONTEXT_PROFILE_MASK_ARB,
      profile,
      GLX_CONTEXT_FLAGS_ARB,
      GLX_CONTEXT_DEBUG_BIT_ARB,
      0,
  };

  // Extension entry points must be resolved at run-time.
  PFNGLXCREATECONTEXTATTRIBSARBPROC createContextAttribs = (PFNGLXCREATECONTEXTATTRIBSARBPROC)
      glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

  // Create a GL context with the requested capabilities.
  if (createContextAttribs) {
    _ctx = (*createContextAttribs)(
        shareDisplay, configs[0], shareContext, directRendering, attribs);
  }
  else {
    TF_WARN("Unable to create GL debug context.");
    XVisualInfo *vis = glXGetVisualFromFBConfig(shareDisplay, configs[0]);
    _ctx = glXCreateContext(shareDisplay, vis, shareContext, directRendering);
  }
  if (!TF_VERIFY(_ctx)) {
    return;
  }

  _dpy = shareDisplay;
}

GarchGLPlatformDebugContextPrivate::~GarchGLPlatformDebugContextPrivate()
{
  if (_dpy && _ctx) {
    glXDestroyContext(_dpy, _ctx);
  }
}

void GarchGLPlatformDebugContextPrivate::MakeCurrent()
{
  glXMakeCurrent(glXGetCurrentDisplay(), glXGetCurrentDrawable(), _ctx);
}

void *GarchSelectCoreProfileMacVisual()
{
  return nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // ARCH_OS_LINUX

////////////////////////////////////////////////////////////

#if defined(ARCH_OS_DARWIN)

PXR_NAMESPACE_OPEN_SCOPE

// XXX: implement debug context
class GarchGLPlatformDebugContextPrivate {
 public:
  GarchGLPlatformDebugContextPrivate(int majorVersion,
                                     int minorVersion,
                                     bool coreProfile,
                                     bool directRendering)
  {
  }
  ~GarchGLPlatformDebugContextPrivate() {}

  void MakeCurrent() {}
};

void *GarchSelectCoreProfileMacVisual();  // extern obj-c

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // ARCH_OS_DARWIN

////////////////////////////////////////////////////////////

#if defined(ARCH_OS_WINDOWS)

PXR_NAMESPACE_OPEN_SCOPE

// XXX: implement debug context
class GarchGLPlatformDebugContextPrivate {
 public:
  GarchGLPlatformDebugContextPrivate(int majorVersion,
                                     int minorVersion,
                                     bool coreProfile,
                                     bool directRendering)
  {
  }
  ~GarchGLPlatformDebugContextPrivate() {}

  void MakeCurrent() {}
};

void *GarchSelectCoreProfileMacVisual()
{
  return nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // ARCH_OS_WINDOWS

////////////////////////////////////////////////////////////

PXR_NAMESPACE_OPEN_SCOPE

GarchGLPlatformDebugContext::GarchGLPlatformDebugContext(int majorVersion,
                                                         int minorVersion,
                                                         bool coreProfile,
                                                         bool directRendering)
    : _coreProfile(coreProfile)

{
  if (!GarchGLPlatformDebugContext::IsEnabledDebugOutput()) {
    return;
  }
  _private.reset(new GarchGLPlatformDebugContextPrivate(
      majorVersion, minorVersion, coreProfile, directRendering));
}

GarchGLPlatformDebugContext::~GarchGLPlatformDebugContext()
{
  // nothing
}

/* virtual */
void GarchGLPlatformDebugContext::makeCurrent()
{
  // note: if not enabled, returns without making context current.
  if (!GarchGLPlatformDebugContext::IsEnabledDebugOutput()) {
    return;
  }

  if (!TF_VERIFY(_private)) {
    return;
  }

  _private->MakeCurrent();
}

void *GarchGLPlatformDebugContext::chooseMacVisual()
{
  if (_coreProfile || GarchGLPlatformDebugContext::IsEnabledCoreProfile()) {
    return GarchSelectCoreProfileMacVisual();
  }
  else {
    return nullptr;
  }
  return nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE
