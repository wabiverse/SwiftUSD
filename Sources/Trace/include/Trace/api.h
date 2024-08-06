//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TRACE_API_H
#define PXR_BASE_TRACE_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define TRACE_API
#  define TRACE_API_TEMPLATE_CLASS(...)
#  define TRACE_API_TEMPLATE_STRUCT(...)
#  define TRACE_LOCAL
#else
#  if defined(TRACE_EXPORTS)
#    define TRACE_API ARCH_EXPORT
#    define TRACE_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define TRACE_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define TRACE_API ARCH_IMPORT
#    define TRACE_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define TRACE_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define TRACE_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_BASE_TRACE_API_H
