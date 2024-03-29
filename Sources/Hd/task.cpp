//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "Hd/task.h"
#include "Hd/perfLog.h"

#include "Tf/stl.h"

PXR_NAMESPACE_OPEN_SCOPE


// -------------------------------------------------------------------------- //
// HdTask Definitions 
// -------------------------------------------------------------------------- //

HdTask::HdTask(SdfPath const& id)
 : _id(id)
{
}

HdTask::~HdTask()
{
}

const TfTokenVector &
HdTask::GetRenderTags() const
{
    static TfTokenVector EMPTY_SET;

    return EMPTY_SET;
}

/// Returns the minimal set of dirty bits to place in the
/// change tracker for use in the first sync of this prim.
/// Typically this would be all dirty bits.
HdDirtyBits
HdTask::GetInitialDirtyBitsMask() const
{
    return HdChangeTracker::DirtyParams     |
           HdChangeTracker::DirtyCollection |
           HdChangeTracker::DirtyRenderTags;
}

bool
HdTask::_HasTaskContextData(
    HdTaskContext const* ctx,
    TfToken const& id)
{
    HdTaskContext::const_iterator valueIt = ctx->find(id);
    return (valueIt != ctx->cend());
}

TfTokenVector HdTask::_GetTaskRenderTags(HdSceneDelegate* delegate)
{
    return delegate->GetTaskRenderTags(GetId());
}

PXR_NAMESPACE_CLOSE_SCOPE

