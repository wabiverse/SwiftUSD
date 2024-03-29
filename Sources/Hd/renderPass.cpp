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
#include "Hd/renderPass.h"

#include "Hd/changeTracker.h"
#include "Hd/renderIndex.h"
#include "Hd/renderPassState.h"
#include "Hd/sceneDelegate.h"
#include "Hd/tokens.h"

#include "Tf/staticTokens.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

HdRenderPass::HdRenderPass(HdRenderIndex *index,
                           HdRprimCollection const& collection)
    : _renderIndex(index)
{
    SetRprimCollection(collection);
}

HdRenderPass::~HdRenderPass()
{
    /*NOTHING*/
}

void 
HdRenderPass::SetRprimCollection(HdRprimCollection const& col)
{
    if (col == _collection) {
        return;
    }

    _collection = col; 

    // Mark the collection dirty in derived classes.
    _MarkCollectionDirty();
}

void
HdRenderPass::Execute(HdRenderPassStateSharedPtr const &renderPassState,
                      TfTokenVector const &renderTags)
{
    _Execute(renderPassState, renderTags);
}

void
HdRenderPass::Sync()
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    // Enqueue the collection to be synced during Hydra Sync.
    // XXX: This is currently necessary for Hydra's core to know the reprs to
    // sync for the dirty rprims.
    // The collection paths are ignored.
    _renderIndex->EnqueueCollectionToSync(_collection);

    // Give derived classes a chance to sync.
    _Sync();
}

PXR_NAMESPACE_CLOSE_SCOPE
