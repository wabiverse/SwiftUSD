//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_GLF_API_H
#define PXR_IMAGING_GLF_API_H

#include "Arch/export.h"

#if defined(PXR_STATIC)
#  define GLF_API
#  define GLF_API_TEMPLATE_CLASS(...)
#  define GLF_API_TEMPLATE_STRUCT(...)
#  define GLF_LOCAL
#else
#  if defined(GLF_EXPORTS)
#    define GLF_API ARCH_EXPORT
#    define GLF_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#    define GLF_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#  else
#    define GLF_API ARCH_IMPORT
#    define GLF_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#    define GLF_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#  endif
#  define GLF_LOCAL ARCH_HIDDEN
#endif

#endif  // PXR_IMAGING_GLF_API_H
