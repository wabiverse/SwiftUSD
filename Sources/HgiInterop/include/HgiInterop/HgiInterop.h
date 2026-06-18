#ifndef __PXR_IMAGING_HGIINTEROP_H__
#define __PXR_IMAGING_HGIINTEROP_H__

// HgiInterop
#include <HgiInterop/hgiInteropImpl.h>
#include <HgiInterop/opengl.h>
#include <HgiInterop/api.h>
#if defined(__APPLE__) && defined(__has_include) && __has_include(<AppKit/AppKit.h>)
#include <HgiInterop/metal.h>
#endif
#endif  // __PXR_IMAGING_HGIINTEROP_H__
