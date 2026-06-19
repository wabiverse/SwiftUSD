//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_WORK_TBB_VERSION_H
#define PXR_BASE_WORK_TBB_VERSION_H

// The TBB version macro is located in different headers in legacy TBB
// (tbb/tbb_stddef.h) and oneTBB (tbb/version.h)
#if __has_include(<OneTBB/tbb/tbb_stddef.h>)
#include <OneTBB/tbb/tbb_stddef.h>
#elif __has_include(<OneTBB/tbb/version.h>)
#include <OneTBB/tbb/version.h>
#endif

#ifndef TBB_INTERFACE_VERSION_MAJOR
#error "TBB version macro TBB_INTERFACE_VERSION_MAJOR not found"
#endif

#endif //PXR_BASE_WORK_TBB_VERSION_H
