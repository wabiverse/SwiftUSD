//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Diagnostic.cpp
//

#include "Garch/glApi.h"

#include "HgiGL/diagnostic.h"

#include "Tf/debug.h"
#include "Tf/diagnostic.h"
#include "Tf/envSetting.h"
#include "Tf/registryManager.h"
#include "Tf/stackTrace.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(HGIGL_DEBUG, 0, "Enable OpenGL debugging for HgiGL");

TF_DEBUG_CODES(HGIGL_DEBUG_ERROR_STACKTRACE);

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(HGIGL_DEBUG_ERROR_STACKTRACE, "HgiGL dump stack trace on GL error");
}

bool HgiGLDebugEnabled()
{
#if defined(GL_KHR_debug)
  static bool _v = TfGetEnvSetting(HGIGL_DEBUG) == 1;
  return _v;
#else
  return false;
#endif
}

void HgiGLPostPendingGLErrors(std::string const &where)
{
  bool foundError = false;
  GLenum error;
  // Protect from doing infinite looping when glGetError
  // is called from an invalid context.
  int watchDogCount = 0;
  while ((watchDogCount++ < 256) && ((error = glGetError()) != GL_NO_ERROR)) {
    foundError = true;
    const GLubyte *errorString = gluErrorString(error);

    std::ostringstream errorMessage;
    if (!errorString) {
      errorMessage << "GL error code: 0x" << std::hex << error << std::dec;
    }
    else {
      errorMessage << "GL error: " << errorString;
    }

    if (!where.empty()) {
      errorMessage << ", reported from " << where;
    }

    TF_DEBUG(HGIGL_DEBUG_ERROR_STACKTRACE).Msg(errorMessage.str() + "\n");

    TF_RUNTIME_ERROR(errorMessage.str());
  }
  if (foundError) {
    TF_DEBUG(HGIGL_DEBUG_ERROR_STACKTRACE)
        .Msg(TfStringPrintf("==== GL Error Stack ====\n%s\n", TfGetStackTrace().c_str()));
  }
}

static void _HgiGLErrorCallback(int e, const char *m)
{
  std::string err = "GL Error code: " + std::to_string(e) + " Msg: " + m +
                    " Func: " + __ARCH_PRETTY_FUNCTION__;
  HgiGLPostPendingGLErrors(err);
}

static void _HgiGLGL4DbgCallback(GLenum src,
                                 GLenum type,
                                 GLuint id,
                                 GLenum severity,
                                 GLsizei length,
                                 const GLchar *msg,
                                 GLvoid *user)
{
  switch (id) {
    case 131218:
      return;  // 'Shader re-compiled due to GL state mismatch'
    case 131185:
      return;  // 'buffer map details'
    case 131076:
      return;  // 'vert attrb array small' (when no mesh loaded)
    default:
      break;
  }
  _HgiGLErrorCallback(id, msg);
}

void HgiGLSetupGL4Debug()
{
  if (!HgiGLDebugEnabled())
    return;

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback((GLDEBUGPROC)_HgiGLGL4DbgCallback, 0);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}

bool HgiGLMeetsMinimumRequirements()
{
  const char *glVersionStr = (const char *)glGetString(GL_VERSION);

  // GL hasn't been initialized
  if (glVersionStr == nullptr)
    return false;

  int glVersion = 0;

  const char *dot = strchr(glVersionStr, '.');
  if (TF_VERIFY((dot && dot != glVersionStr), "Can't parse GL_VERSION %s", glVersionStr)) {
    // GL_VERSION = "4.5.0 <vendor> <version>"
    //              "4.1 <vendor-os-ver> <version>"
    //              "4.1 <vendor-os-ver>"
    int major = (std::max)(0, (std::min)(9, *(dot - 1) - '0'));
    int minor = (std::max)(0, (std::min)(9, *(dot + 1) - '0'));
    glVersion = major * 100 + minor * 10;
  }

  return (glVersion >= 450);
}

void HgiGLObjectLabel(const uint32_t identifier, const uint32_t name, const std::string &label)
{
  GLint maxLength;
  glGetIntegerv(GL_MAX_LABEL_LENGTH, &maxLength);

  glObjectLabel(identifier,
                name,
                (std::min)(label.size(),
                         size_t(maxLength - 1)),  // Account for 0-terminator.
                label.c_str());
}

PXR_NAMESPACE_CLOSE_SCOPE
