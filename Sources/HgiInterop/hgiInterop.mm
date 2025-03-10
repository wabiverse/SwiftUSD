//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

// annoyingly, swift gets confused if cpp and objc are in the same
// directory, and treats objc includes as cpp includes, which causes
// a great deal of problems when trying to include for example Metal,
// so we duplicate this file and compile only the mm one for all apple
// platforms.
#if defined(__APPLE__)
#  include "Hgi/hgiImpl.h"
#  include "Hgi/tokens.h"
#  include "HgiInterop/hgiInteropImpl.h"

#  if defined(PXR_GL_SUPPORT_ENABLED)
#    include "HgiInterop/opengl.h"
#    include "HgiGL/hgi.h"
#  endif

#  if defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
#    include "HgiInterop/vulkan.h"
#    include "HgiVulkan/hgi.h"
#  endif

#  if defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED
#    include "HgiMetal/hgi.h"
#    if defined(ARCH_OS_OSX)
#      include "HgiInterop/metal.h"
#    endif  // defined(ARCH_OS_OSX)
#  endif    // defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED

PXR_NAMESPACE_OPEN_SCOPE

struct HgiInteropImpl {
#  if defined(PXR_GL_SUPPORT_ENABLED)
  std::unique_ptr<HgiInteropOpenGL> _openGLToOpenGL;
#  endif  // defined(PXR_GL_SUPPORT_ENABLED)
#  if defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
  std::unique_ptr<HgiInteropVulkan> _vulkanToOpenGL;
#  endif  // defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
#  if defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED
#    if !defined(ARCH_OS_IPHONE)
  std::unique_ptr<HgiInteropMetal> _metalToOpenGL;
#    endif  // !defined(ARCH_OS_IPHONE)
#  endif    // defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED
};

HgiInterop::HgiInterop() : _hgiInteropImpl(std::make_unique<HgiInteropImpl>()) {}

HgiInterop::~HgiInterop() = default;

void HgiInterop::TransferToApp(Hgi *srcHgi,
                               HgiTextureHandle const &srcColor,
                               HgiTextureHandle const &srcDepth,
                               TfToken const &dstApi,
                               VtValue const &dstFramebuffer,
                               GfVec4i const &dstRegion)
{
  TfToken const &srcApi = srcHgi->GetAPIName();

  if (dstApi != HgiTokens->OpenGL) {
    TF_CODING_ERROR("Unsupported destination Hgi backend: %s", dstApi.GetText());
    return;
  }

#  if defined(PXR_GL_SUPPORT_ENABLED) && !defined(ARCH_OS_IPHONE)
  if (srcApi == HgiTokens->OpenGL) {
    // Transfer OpenGL textures to OpenGL application
    if (!_hgiInteropImpl->_openGLToOpenGL) {
      _hgiInteropImpl->_openGLToOpenGL = std::make_unique<HgiInteropOpenGL>();
    }
    return _hgiInteropImpl->_openGLToOpenGL->CompositeToInterop(
        srcColor, srcDepth, dstFramebuffer, dstRegion);
  }
#  endif

#  if defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
  if (srcApi == HgiTokens->Vulkan) {
    // Transfer Vulkan textures to OpenGL application
    // XXX: It's possible that if we use the same HgiInterop with a
    // different Hgi instance passed to this function, HgiInteropVulkan
    // will have the wrong Hgi instance since we wouldn't recreate it here.
    // We should fix this.
    if (!_hgiInteropImpl->_vulkanToOpenGL) {
      _hgiInteropImpl->_vulkanToOpenGL = std::make_unique<HgiInteropVulkan>(srcHgi);
    }
    return _hgiInteropImpl->_vulkanToOpenGL->CompositeToInterop(
        srcColor, srcDepth, dstFramebuffer, dstRegion);
  }
#  endif

#  if (defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED) && !defined(ARCH_OS_IPHONE)
  if (srcApi == HgiTokens->Metal) {
    // Transfer Metal textures to OpenGL application
    // XXX: It's possible that if we use the same HgiInterop with a
    // different Hgi instance passed to this function, HgiInteropMetal
    // will have the wrong Hgi instance since we wouldn't recreate it here.
    // We should fix this.
    if (!_hgiInteropImpl->_metalToOpenGL) {
      _hgiInteropImpl->_metalToOpenGL = std::make_unique<HgiInteropMetal>(srcHgi);
    }
    return _hgiInteropImpl->_metalToOpenGL->CompositeToInterop(
        srcColor, srcDepth, dstFramebuffer, dstRegion);
  }
#  endif

  TF_CODING_ERROR("Unsupported source Hgi backend: %s", srcApi.GetText());
}

// static.
Hgi* HgiInterop::GetHgiFromDriver(VtValue const &hdDriver)
{
  /* keep sorted, in order of preferred hgi per platform.
   * which is metal above all else on darwin, followed by
   * vulkan over opengl on windows and linux, and finally
   * we fallback to the base hgi class, in the case that
   * none of the specific platform hgis were passed in. */

#if  defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED
  if (hdDriver.IsHolding<HgiMetal *>()) {
    return hdDriver.UncheckedGet<HgiMetal *>();
  }
#endif //  defined(PXR_METAL_SUPPORT_ENABLED) && PXR_METAL_SUPPORT_ENABLED
#if defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
  if (hdDriver.IsHolding<HgiVulkan *>()) {
    return hdDriver.UncheckedGet<HgiVulkan *>();
  }
#endif // defined(PXR_VULKAN_SUPPORT_ENABLED) && PXR_VULKAN_SUPPORT_ENABLED
#if defined(PXR_GL_SUPPORT_ENABLED)
  if (hdDriver.IsHolding<HgiGL *>()) {
    return hdDriver.UncheckedGet<HgiGL *>();
  }
#endif // defined(PXR_GL_SUPPORT_ENABLED)
  if (hdDriver.IsHolding<Hgi *>()) {
    return hdDriver.UncheckedGet<Hgi *>();
  }

  return nullptr;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // defined(__APPLE__)
