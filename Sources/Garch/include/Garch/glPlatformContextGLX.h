//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_GLX_H
#define PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_GLX_H

#include "pxr/pxrns.h"

#if defined(__ANDROID__)

#include <EGL/egl.h>

PXR_NAMESPACE_OPEN_SCOPE

class GarchEGLContextState {
public:
    GarchEGLContextState();
    GarchEGLContextState(EGLDisplay, EGLSurface, EGLContext);
    bool operator==(const GarchEGLContextState& rhs) const;
    size_t GetHash() const;
    bool IsValid() const;
    void MakeCurrent();
    static void DoneCurrent();
public:
    EGLDisplay display;
    EGLSurface drawable;
    EGLContext context;
private:
    bool _defaultCtor;
};

typedef GarchEGLContextState GarchGLPlatformContextState;

PXR_NAMESPACE_CLOSE_SCOPE

#else // !defined(__ANDROID__)

#include <GL/glx.h>

PXR_NAMESPACE_OPEN_SCOPE

class GarchGLXContextState {
public:
    /// Construct with the current state.
    GarchGLXContextState();

    /// Construct with the given state.
    GarchGLXContextState(Display*, GLXDrawable, GLXContext);

    /// Compare for equality.
    bool operator==(const GarchGLXContextState& rhs) const;

    /// Returns a hash value for the state.
    size_t GetHash() const;

    /// Returns \c true if the context state is valid.
    bool IsValid() const;

    /// Make the context current.
    void MakeCurrent();

    /// Make no context current.
    static void DoneCurrent();

public:
    Display* display;
    GLXDrawable drawable;
    GLXContext context;

private:
    bool _defaultCtor;
};

typedef GarchGLXContextState GarchGLPlatformContextState;

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(__ANDROID__)

#endif  // PXR_IMAGING_GARCH_GL_PLATFORM_CONTEXT_GLX_H
