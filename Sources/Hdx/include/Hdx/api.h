//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDX_API_H
#define PXR_IMAGING_HDX_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define HDX_API
#  define HDX_API_TEMPLATE_CLASS(...)
#  define HDX_API_TEMPLATE_STRUCT(...)
#  define HDX_LOCAL
#else
#  if defined(HDX_EXPORTS)
#    define HDX_API ARCH_EXPORT
#    define HDX_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define HDX_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define HDX_API ARCH_IMPORT
#    define HDX_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define HDX_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define HDX_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_IMAGING_HDX_API_H
