//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_API_H
#define PXR_IMAGING_HD_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define HD_API
#  define HD_API_TEMPLATE_CLASS(...)
#  define HD_API_TEMPLATE_STRUCT(...)
#  define HD_LOCAL
#else
#  if defined(HD_EXPORTS)
#    define HD_API ARCH_EXPORT
#    define HD_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define HD_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define HD_API ARCH_IMPORT
#    define HD_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define HD_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define HD_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_IMAGING_HD_API_H
