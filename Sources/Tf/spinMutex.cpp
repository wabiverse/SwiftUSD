//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Arch/threads.h"
#include "Tf/spinMutex.h"

#include <thread>

PXR_NAMESPACE_OPEN_SCOPE

static constexpr int SpinsBeforeBackoff = 32;

template<class Fn> static void WaitWithBackoff(Fn &&fn)
{
  // Hope for the best...
  if (ARCH_LIKELY(fn())) {
    return;
  }
  // Otherwise spin for a bit...
  for (int i = 0; i != SpinsBeforeBackoff; ++i) {
    ARCH_SPIN_PAUSE();
    if (fn()) {
      return;
    }
  }
  // Keep checking but yield our thread...
  do {
    std::this_thread::yield();
  } while (!fn());
}

void TfSpinMutex::_AcquireContended()
{
  WaitWithBackoff(
      [this]() { return _lockState.exchange(true, std::memory_order_acquire) == false; });
}

PXR_NAMESPACE_CLOSE_SCOPE
