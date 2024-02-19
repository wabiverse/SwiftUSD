#ifndef __PXR_IMAGING_GARCH_GARCH_H__
#define __PXR_IMAGING_GARCH_GARCH_H__

// garch.
#include <Garch/api.h>
#include <Garch/gl.h>
#include <Garch/glApi.h>
#include <Garch/glDebugWindow.h>
#include <Garch/glPlatformContext.h>
#include <Garch/glPlatformDebugContext.h>
#include <Garch/khrplatform.h>
#if defined(__APPLE__)
# include <Garch/GarchDarwin/glPlatformContextDarwin.h>
# include <Garch/GarchDarwin/glPlatformDebugWindowDarwin.h>
#elif defined(__linux__)
# include <Garch/GarchGLX/glPlatformContextGLX.h>
# include <Garch/GarchGLX/glPlatformDebugWindowGLX.h>
#elif defined(_WIN32)
# include <Garch/GarchWindows/glPlatformContextWindows.h>
# include <Garch/GarchWindows/glPlatformDebugWindowWindows.h>
#endif /* defined(_WIN32) */

#endif /* __PXR_IMAGING_GARCH_GARCH_H__ */
