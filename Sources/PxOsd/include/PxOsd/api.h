//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_PX_OSD_API_H
#define PXR_IMAGING_PX_OSD_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define PXOSD_API
#  define PXOSD_API_TEMPLATE_CLASS(...)
#  define PXOSD_API_TEMPLATE_STRUCT(...)
#  define PXOSD_LOCAL
#else
#  if defined(PXOSD_EXPORTS)
#    define PXOSD_API ARCH_EXPORT
#    define PXOSD_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define PXOSD_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define PXOSD_API ARCH_IMPORT
#    define PXOSD_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define PXOSD_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define PXOSD_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_IMAGING_PX_OSD_API_H
