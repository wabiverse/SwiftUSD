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
#include "Sdf/cleanupEnabler.h"
#include "Sdf/cleanupTracker.h"
#include "Tf/instantiateStacked.h"
#include <pxr/pxrns.h>

PXR_NAMESPACE_OPEN_SCOPE

TF_INSTANTIATE_DEFINED_STACKED(SdfCleanupEnabler);

SdfCleanupEnabler::SdfCleanupEnabler() {
  // Do nothing
}

SdfCleanupEnabler::~SdfCleanupEnabler() {
  if (GetStack().size() == 1) {
    // The last CleanupEnabler is being removed from the stack, so notify
    // the CleanupTracker that it's time to clean up any specs it collected.
    Sdf_CleanupTracker::GetInstance().CleanupSpecs();
  }
}

// Static
bool SdfCleanupEnabler::IsCleanupEnabled() { return !GetStack().empty(); }

PXR_NAMESPACE_CLOSE_SCOPE
