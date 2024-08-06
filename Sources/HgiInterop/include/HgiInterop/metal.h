//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGIINTEROP_HGIINTEROPMETAL_H
#define PXR_IMAGING_HGIINTEROP_HGIINTEROPMETAL_H

#if defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED

#include "Garch/glApi.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <OpenGL/OpenGL.hpp>

#include "Gf/vec4i.h"
#include "Hgi/texture.h"
#include "HgiInterop/api.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class Hgi;
class HgiMetal;
class VtValue;

/// \class HgiInteropMetal
///
/// Provides Metal/GL interop
///
class HgiInteropMetal final {
 public:
  HGIINTEROP_API
  HgiInteropMetal(Hgi *hgi);

  HGIINTEROP_API
  ~HgiInteropMetal();

  /// Copy/Present provided color (and optional depth) textures to app.
  HGIINTEROP_API
  void CompositeToInterop(HgiTextureHandle const &color,
                          HgiTextureHandle const &depth,
                          VtValue const &framebuffer,
                          GfVec4i const &compRegion);

 private:
  HgiInteropMetal() = delete;

  enum {
    ShaderContextColor,
    ShaderContextColorDepth,

    ShaderContextCount
  };

  struct ShaderContext {
    uint32_t program;
    uint32_t vao;
    uint32_t vbo;
    int32_t posAttrib;
    int32_t texAttrib;
    int32_t samplerColorLoc;
    int32_t samplerDepthLoc;
    uint32_t blitTexSizeUniform;
  };

  struct VertexAttribState {
    int32_t enabled;
    int32_t size;
    int32_t type;
    int32_t normalized;
    int32_t stride;
    int32_t bufferBinding;
    void *pointer;
  };

  void _BlitToOpenGL(VtValue const &framebuffer, GfVec4i const &compRegion, int shaderIndex);
  void _FreeTransientTextureCacheRefs();
  void _CaptureOpenGlState();
  void _RestoreOpenGlState();
  void _CreateShaderContext(int32_t vertexSource, int32_t fragmentSource, ShaderContext &shader);
  void _SetAttachmentSize(int width, int height);
  void _ValidateGLContext();

  HgiMetal *_hgiMetal;

  MTL::Device* _device;

  MTL::Texture* _mtlAliasedColorTexture;
  MTL::Texture* _mtlAliasedDepthRegularFloatTexture;

  MTL::Library* _defaultLibrary;
  MTL::Function* _computeDepthCopyProgram;
  MTL::Function* _computeColorCopyProgram;
  MTL::ComputePipelineState* _computePipelineStateColor;
  MTL::ComputePipelineState* _computePipelineStateDepth;

#if 0
  // wabi: Add these into the CXX Apple headers.
  CVPixelBufferRef _pixelBuffer;
  CVPixelBufferRef _depthBuffer;
#endif
  uint32_t _glColorTexture;
  uint32_t _glDepthTexture;

  ShaderContext _shaderProgramContext[ShaderContextCount];

  NSGL::OpenGLContext *_currentOpenGLContext;

  int32_t _restoreDrawFbo;
  int32_t _restoreVao;
  int32_t _restoreVbo;
  bool _restoreDepthTest;
  bool _restoreDepthWriteMask;
  bool _restoreStencilWriteMask;
  bool _restoreCullFace;
  int32_t _restoreFrontFace;
  int32_t _restoreDepthFunc;
  int32_t _restoreViewport[4];
  bool _restoreblendEnabled;
  int32_t _restoreColorOp;
  int32_t _restoreAlphaOp;
  int32_t _restoreColorSrcFnOp;
  int32_t _restoreAlphaSrcFnOp;
  int32_t _restoreColorDstFnOp;
  int32_t _restoreAlphaDstFnOp;
  bool _restoreAlphaToCoverage;
  int32_t _restorePolygonMode;
  int32_t _restoreActiveTexture;
  int32_t _restoreTexture[2];
  VertexAttribState _restoreVertexAttribState[2];
  int32_t _restoreProgram;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED

#endif
