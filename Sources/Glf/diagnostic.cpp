//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Diagnostic.cpp
//

#include "Garch/glApi.h"

#include "Glf/debugCodes.h"
#include "Glf/diagnostic.h"
#include "Glf/glContext.h"

#include "Tf/diagnostic.h"
#include "Tf/envSetting.h"
#include "Tf/stackTrace.h"
#include "Tf/stringUtils.h"

#include <sstream>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(GLF_ENABLE_DIAGNOSTIC_TRACE,
                      0,
                      "Enable glDebug* diagnostic tracing in Glf.");

static bool GlfTraceEnabled()
{
#if defined(GL_KHR_debug)
  static bool _v = TfGetEnvSetting(GLF_ENABLE_DIAGNOSTIC_TRACE) == 1;
  return _v;
#else
  return false;
#endif
}

void GlfPostPendingGLErrors(std::string const &where)
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

    TF_DEBUG(GLF_DEBUG_ERROR_STACKTRACE).Msg(errorMessage.str() + "\n");

    TF_RUNTIME_ERROR(errorMessage.str());
  }
  if (foundError) {
    TF_DEBUG(GLF_DEBUG_ERROR_STACKTRACE)
        .Msg(TfStringPrintf("==== GL Error Stack ====\n%s\n", TfGetStackTrace().c_str()));
  }
}

void GlfRegisterDefaultDebugOutputMessageCallback()
{
#if defined(GL_KHR_debug)
  if (glDebugMessageCallbackARB) {
    glDebugMessageCallbackARB((GLDEBUGPROCARB)GlfDefaultDebugOutputMessageCallback, 0);
    // Disable push/pop group messages; we don't want to print these.
    glDebugMessageControlARB(
        GL_DONT_CARE, GL_DEBUG_TYPE_PUSH_GROUP, GL_DONT_CARE, 0, nullptr, GL_FALSE);
    glDebugMessageControlARB(
        GL_DONT_CARE, GL_DEBUG_TYPE_POP_GROUP, GL_DONT_CARE, 0, nullptr, GL_FALSE);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
  }
#endif
}

void GlfDefaultDebugOutputMessageCallback(GLenum source,
                                          GLenum type,
                                          GLuint id,
                                          GLenum severity,
                                          GLsizei length,
                                          GLchar const *message,
                                          GLvoid const *userParam)
{
#if defined(GL_ARB_debug_output) || defined(GL_VERSION_4_3)
  if (type == GL_DEBUG_TYPE_ERROR_ARB) {
    TF_RUNTIME_ERROR(
        "GL debug output: "
        "source: %s type: %s id: %d severity: %s message: %s",
        GlfDebugEnumToString(source),
        GlfDebugEnumToString(type),
        id,
        GlfDebugEnumToString(severity),
        message);

    TF_DEBUG(GLF_DEBUG_ERROR_STACKTRACE)
        .Msg(TfStringPrintf("==== GL Error Stack ====\n%s\n", TfGetStackTrace().c_str()));
  }
  else {
    TF_WARN("GL debug output: %s", message);
  }
#endif
}

char const *GlfDebugEnumToString(GLenum debugEnum)
{
#if defined(GL_ARB_debug_output) || defined(GL_VERSION_4_3)
  switch (debugEnum) {
    case GL_DEBUG_SOURCE_API_ARB:
      return "GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
      return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
      return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
      return "GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
      return "GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER_ARB:
      return "GL_DEBUG_SOURCE_OTHER";

    case GL_DEBUG_TYPE_ERROR_ARB:
      return "GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
      return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
      return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY_ARB:
      return "GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:
      return "GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER_ARB:
      return "GL_DEBUG_TYPE_OTHER";
#  if defined(GL_VERSION_4_3)
    case GL_DEBUG_TYPE_MARKER:
      return "GL_DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP:
      return "GL_DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP:
      return "GL_DEBUG_TYPE_POP_GROUP";
#  endif

#  if defined(GL_VERSION_4_3)
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "GL_DEBUG_SEVERITY_NOTIFICATION";
#  endif
    case GL_DEBUG_SEVERITY_HIGH_ARB:
      return "GL_DEBUG_SEVERITY_HIGH";
    case GL_DEBUG_SEVERITY_MEDIUM_ARB:
      return "GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_LOW_ARB:
      return "GL_DEBUG_SEVERITY_LOW";
  }
#endif
  TF_CODING_ERROR("unknown debug enum");
  return "unknown";
}

static void _GlfPushDebugGroup(char const *message)
{
#if defined(GL_KHR_debug)
  if (GARCH_GLAPI_HAS(KHR_debug)) {
    glPushDebugGroup(GL_DEBUG_SOURCE_THIRD_PARTY, 0, -1, message);
  }
#endif
}

static void _GlfPopDebugGroup()
{
#if defined(GL_KHR_debug)
  if (GARCH_GLAPI_HAS(KHR_debug)) {
    glPopDebugGroup();
  }
#endif
}

GlfDebugGroup::GlfDebugGroup(char const *message)
{
  if (GlfTraceEnabled()) {
    _GlfPushDebugGroup(message);
  }
}

GlfDebugGroup::~GlfDebugGroup()
{
  if (GlfTraceEnabled()) {
    _GlfPopDebugGroup();
  }
}

void GlfDebugLabelBuffer(GLuint id, char const *label)
{
#if defined(GL_KHR_debug)
  if (GlfTraceEnabled()) {
    if (GARCH_GLAPI_HAS(KHR_debug)) {
      glObjectLabel(GL_BUFFER, id, -1, label);
    }
  }
#endif
}

void GlfDebugLabelShader(GLuint id, char const *label)
{
#if defined(GL_KHR_debug)
  if (GlfTraceEnabled()) {
    if (GARCH_GLAPI_HAS(KHR_debug)) {
      glObjectLabel(GL_SHADER, id, -1, label);
    }
  }
#endif
}

void GlfDebugLabelProgram(GLuint id, char const *label)
{
#if defined(GL_KHR_debug)
  if (GlfTraceEnabled()) {
    if (GARCH_GLAPI_HAS(KHR_debug)) {
      glObjectLabel(GL_PROGRAM, id, -1, label);
    }
  }
#endif
}

GlfGLQueryObject::GlfGLQueryObject() : _id(0), _target(0)
{
  GarchGLApiLoad();
  if (glGenQueries) {
    glGenQueries(1, &_id);
  }
}

GlfGLQueryObject::~GlfGLQueryObject()
{
  GlfSharedGLContextScopeHolder sharedGLContextScopeHolder;
  if (glDeleteQueries && _id) {
    glDeleteQueries(1, &_id);
  }
}

void GlfGLQueryObject::BeginSamplesPassed()
{
  Begin(GL_SAMPLES_PASSED);
}

void GlfGLQueryObject::BeginPrimitivesGenerated()
{
  Begin(GL_PRIMITIVES_GENERATED);
}
void GlfGLQueryObject::BeginTimeElapsed()
{
  Begin(GL_TIME_ELAPSED);
}

void GlfGLQueryObject::Begin(GLenum target)
{
  _target = target;
  if (glBeginQuery && _id) {
    glBeginQuery(_target, _id);
  }
}

void GlfGLQueryObject::End()
{
  if (glEndQuery && _target) {
    glEndQuery(_target);
  }
  _target = 0;
}

GLint64 GlfGLQueryObject::GetResult()
{
  GLint64 value = 0;
  if (glGetQueryObjecti64v && _id) {
    glGetQueryObjecti64v(_id, GL_QUERY_RESULT, &value);
  }
  return value;
}

GLint64 GlfGLQueryObject::GetResultNoWait()
{
  GLint64 value = 0;
  if (glGetQueryObjecti64v && _id) {
    glGetQueryObjecti64v(_id, GL_QUERY_RESULT_AVAILABLE, &value);
    if (value == GL_TRUE) {
      glGetQueryObjecti64v(_id, GL_QUERY_RESULT, &value);
    }
  }
  return value;
}

PXR_NAMESPACE_CLOSE_SCOPE
