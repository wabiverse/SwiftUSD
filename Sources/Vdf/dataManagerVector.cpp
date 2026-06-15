//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Vdf/dataManagerVector.h"

#include "Vdf/dataManagerAllocator.h"

#include "Tf/staticData.h"

PXR_NAMESPACE_OPEN_SCOPE

// The vector data allocator shared between all VdfDataManagerVector instances.
static
    TfStaticData<Vdf_DataManagerAllocator<Vdf_ExecutorDataVector>>
    _allocator;

Vdf_ExecutorDataVector *
Vdf_DataManagerVectorAllocate(const VdfNetwork &network)
{
    return _allocator->Allocate(network);
}

void
Vdf_DataManagerVectorDeallocateNow(Vdf_ExecutorDataVector *data)
{
    _allocator->DeallocateNow(data);
}

void 
Vdf_DataManagerVectorDeallocateLater(Vdf_ExecutorDataVector *data)
{
    _allocator->DeallocateLater(data);
}

PXR_NAMESPACE_CLOSE_SCOPE
