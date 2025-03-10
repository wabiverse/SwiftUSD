//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_GEOM_UTIL_API_H
#define PXR_IMAGING_GEOM_UTIL_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define GEOMUTIL_API
#  define GEOMUTIL_API_TEMPLATE_CLASS(...)
#  define GEOMUTIL_API_TEMPLATE_STRUCT(...)
#  define GEOMUTIL_LOCAL
#else
#  if defined(GEOMUTIL_EXPORTS)
#    define GEOMUTIL_API ARCH_EXPORT
#    define GEOMUTIL_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define GEOMUTIL_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define GEOMUTIL_API ARCH_IMPORT
#    define GEOMUTIL_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define GEOMUTIL_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define GEOMUTIL_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_IMAGING_GEOM_UTIL_API_H
