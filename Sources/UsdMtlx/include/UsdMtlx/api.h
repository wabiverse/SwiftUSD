//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USDMTLX_API_H
#define PXR_USD_USDMTLX_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define USDMTLX_API
#  define USDMTLX_API_TEMPLATE_CLASS(...)
#  define USDMTLX_API_TEMPLATE_STRUCT(...)
#  define USDMTLX_LOCAL
#else
#  if defined(USDMTLX_EXPORTS)
#    define USDMTLX_API ARCH_EXPORT
#    define USDMTLX_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define USDMTLX_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define USDMTLX_API ARCH_IMPORT
#    define USDMTLX_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define USDMTLX_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define USDMTLX_LOCAL ARCH_HIDDEN
#endif

#endif
