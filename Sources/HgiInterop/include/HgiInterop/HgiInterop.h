#ifndef __PXR_IMAGING_HGI_INTEROP_HGIINTEROP_H__
#define __PXR_IMAGING_HGI_INTEROP_HGIINTEROP_H__

// hgiInterop.
#include <HgiInterop/api.h>
#include <HgiInterop/hgiInteropImpl.h>
#if PXR_METAL_SUPPORT_ENABLED
#  include "HgiInterop/metal.h"
#elif PXR_VULKAN_SUPPORT_ENABLED
#  include "HgiInterop/vulkan.h"
#else /* !PXR_METAL_SUPPORT_ENABLED && !PXR_VULKAN_SUPPORT_ENABLED */
#  include "HgiInterop/opengl.h"
#endif /* !PXR_METAL_SUPPORT_ENABLED && !PXR_VULKAN_SUPPORT_ENABLED */

#endif /* __PXR_IMAGING_HGI_INTEROP_HGIINTEROP_H__ */
