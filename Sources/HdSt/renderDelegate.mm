#include "pxr/pxrns.h"
#include "Arch/defines.h"

#if defined(ARCH_OS_DARWIN)
# include "HdSt/renderDelegate.h"
# include "Hd/driver.h"
# include "HgiMetal/hgi.h"

PXR_NAMESPACE_OPEN_SCOPE

bool HdStRenderDelegate::GetHgiFromMetalDriver(HdDriver *hdDriver)
{
  if (hdDriver->name == HgiTokens->renderDriver && hdDriver->driver.IsHolding<HgiMetal *>()) {
    _hgi = hdDriver->driver.UncheckedGet<HgiMetal *>();
    return true;
  }

  return false;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(ARCH_OS_DARWIN)
