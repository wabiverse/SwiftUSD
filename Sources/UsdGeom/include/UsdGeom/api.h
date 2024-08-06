//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_API_H
#define USDGEOM_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define USDGEOM_API
#  define USDGEOM_API_TEMPLATE_CLASS(...)
#  define USDGEOM_API_TEMPLATE_STRUCT(...)
#  define USDGEOM_LOCAL
#else
#  if defined(USDGEOM_EXPORTS)
#    define USDGEOM_API ARCH_EXPORT
#    define USDGEOM_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define USDGEOM_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define USDGEOM_API ARCH_IMPORT
#    define USDGEOM_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define USDGEOM_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define USDGEOM_LOCAL ARCH_HIDDEN
#endif

#endif
