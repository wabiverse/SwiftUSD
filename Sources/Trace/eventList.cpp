//
// Copyright 2018 Pixar
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

#include "Trace/eventList.h"

#include <pxr/pxrns.h>

PXR_NAMESPACE_OPEN_SCOPE

TraceEventList::TraceEventList() {
  // Make sure the list always has at least one set in it.
  _caches.emplace_back();
}

void TraceEventList::Append(TraceEventList &&other) {
  // We use splice to keep the keys in the same memory location since the
  // events reference dynamic key by pointer.
  _caches.splice(_caches.end(), std::move(other._caches));
  _events.Append(std::move(other._events));
}

PXR_NAMESPACE_CLOSE_SCOPE
