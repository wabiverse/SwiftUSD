//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Vdf/vectorImpl_Boxed.h"

#include "Vdf/vectorImpl_Contiguous.h"
#include "Vdf/vectorImpl_Empty.h"
#include "Vdf/vectorImpl_Single.h"

PXR_NAMESPACE_OPEN_SCOPE

#define VDF_INSTANTIATE_VECTOR_IMPL_BOXED(type) \
    template class Vdf_VectorImplBoxed<type>;
VDF_FOR_EACH_COMMON_TYPE(VDF_INSTANTIATE_VECTOR_IMPL_BOXED)
#undef VDF_INSTANTIATE_VECTOR_IMPL_BOXED

PXR_NAMESPACE_CLOSE_SCOPE
