//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// AppKit/NSOpenGL.hpp
//
// Copyright 2020-2023 Apple Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include "AppKitDefines.hpp"
#include "AppKitPrivate.hpp"

#include <Foundation/Foundation.hpp>

#include "NSOpenGL.hpp"

namespace NS
{
_APPKIT_ENUM(NS::UInteger, OpenGLPixelFormatAttribute)
{
  OpenGLPFAAllRenderers = 1,
  OpenGLPFATripleBuffer = 3,
  OpenGLPFADoubleBuffer = 5,
  OpenGLPFAAuxBuffers = 7,
  OpenGLPFAColorSize = 8,
  OpenGLPFAAlphaSize = 11,
  OpenGLPFADepthSize = 12,
  OpenGLPFAStencilSize = 13,
  OpenGLPFAAccumSize = 14,
  OpenGLPFAMinimumPolicy = 51,
  OpenGLPFAMaximumPolicy = 52,
  OpenGLPFASampleBuffers = 55,
  OpenGLPFASamples = 56,
  OpenGLPFAAuxDepthStencil = 57,
  OpenGLPFAColorFloat = 58,
  OpenGLPFAMultisample = 59,
  OpenGLPFASupersample = 60,
  OpenGLPFASampleAlpha = 61,
  OpenGLPFARendererID = 70,
  OpenGLPFANoRecovery = 72,
  OpenGLPFAAccelerated = 73,
  OpenGLPFAClosestPolicy = 74,
  OpenGLPFABackingStore = 76,
  OpenGLPFAScreenMask = 84,
  OpenGLPFAAllowOfflineRenderers = 96,
  OpenGLPFAAcceleratedCompute = 97,
  OpenGLPFAOpenGLProfile = 99,
  OpenGLPFAVirtualScreenCount = 128,

  OpenGLPFAStereo = 6,
  OpenGLPFAOffScreen = 53,
  OpenGLPFAFullScreen = 54,
  OpenGLPFASingleRenderer = 71,
  OpenGLPFARobust = 75,
  OpenGLPFAMPSafe = 78,
  OpenGLPFAWindow = 80,
  OpenGLPFAMultiScreen = 81,
  OpenGLPFACompliant = 83,
  OpenGLPFAPixelBuffer = 90,
  OpenGLPFARemotePixelBuffer = 91,

  OpenGLProfileVersionLegacy = 0x1000,  /* choose a Legacy/Pre-OpenGL 3.0 Implementation */
  OpenGLProfileVersion3_2Core = 0x3200, /* choose an OpenGL 3.2 Core Implementation      */
  OpenGLProfileVersion4_1Core = 0x4100, /* choose an OpenGL 4.1 Core Implementation      */
};

_APPKIT_ENUM(NS::Integer, OpenGLContextParameter) {
  OpenGLContextParameterSwapInterval = 222,
  OpenGLContextParameterSurfaceOrder = 235,
  OpenGLContextParameterSurfaceOpacity = 236,
  OpenGLContextParameterSurfaceBackingSize = 304,
  OpenGLContextParameterReclaimResources = 308,
  OpenGLContextParameterCurrentRendererID = 309,
  OpenGLContextParameterGPUVertexProcessing = 310,
  OpenGLContextParameterGPUFragmentProcessing = 311,
  OpenGLContextParameterHasDrawable = 314,
  OpenGLContextParameterMPSwapsInFlight = 315,
  OpenGLContextParameterSwapRectangle = 200,
  OpenGLContextParameterSwapRectangleEnable = 201,
  OpenGLContextParameterRasterizationEnable = 221,
  OpenGLContextParameterStateValidation = 301,
  OpenGLContextParameterSurfaceSurfaceVolatile = 306,
};

class OpenGLPixelFormat : public NS::Referencing<OpenGLPixelFormat>
{
 public:
  static class OpenGLPixelFormat* alloc();

  NS::OpenGLPixelFormat*          init(const NS::OpenGLPixelFormatAttribute* attribs);
  NS::OpenGLPixelFormat*          init(NS::Data* attribs);

  NS::Data* attributes(NS::OpenGLPixelFormatAttribute attributes);
  void      getValues(NS::Integer* vals, NS::OpenGLPixelFormatAttribute attrib, NS::Integer screen);

  NS::Integer numberOfVirtualScreens() const;
  void        setFullScreen();
  void        clearFullScreen();

  void* CGLPixelFormatObj() const;
};

class OpenGLContext : public NS::Referencing<OpenGLContext>
{
 public:
  static class OpenGLContext* alloc();

  NS::OpenGLContext*          init(const NS::OpenGLPixelFormat* format, NS::OpenGLContext* share);

  NS::OpenGLPixelFormat*      pixelFormat() const;

#if 0
  void setView(NS::View* view);
  NS::View* view() const;

  void setPixelBuffer(NS::PixelBuffer* pixelBuffer);
  NS::PixelBuffer* pixelBuffer() const;
#endif // 0

  void setOffScreen(void* baseaddr, NS::Integer width, NS::Integer height, NS::Integer rowbytes);
  
  void clearDrawable();
  void update();

  /* Flush draw buffer */
  void flushBuffer();

  /* Current context control */
  void makeCurrentContext();
  static void clearCurrentContext();
  static NS::OpenGLContext* currentContext();

  void setFullScreen();
  void clearFullScreen();

  void setValues(const NS::Integer* vals, NS::OpenGLContextParameter param);
  void getValues(NS::Integer* vals, NS::Integer count, NS::OpenGLContextParameter param);

  NS::Integer currentVirtualScreen() const;

  void* CGLContextObj() const;
};
} // namespace APPKIT