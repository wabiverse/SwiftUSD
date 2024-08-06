//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_DEBUG_CODES_H
#define PXR_IMAGING_HD_DEBUG_CODES_H

#include "Hd/version.h"
#include "Tf/debug.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEBUG_CODES(HD_BPRIM_ADDED,
               HD_BPRIM_REMOVED,
               HD_BUFFER_ARRAY_INFO,
               HD_BUFFER_ARRAY_RANGE_CLEANED,
               HD_CACHE_HITS,
               HD_CACHE_MISSES,
               HD_COUNTER_CHANGED,
               HD_DIRTY_ALL_COLLECTIONS,
               HD_DIRTY_LIST,
               HD_DISABLE_MULTITHREADED_RPRIM_SYNC,
               HD_DRAWITEMS_CULLED,
               HD_ENGINE_PHASE_INFO,
               HD_EXT_COMPUTATION_ADDED,
               HD_EXT_COMPUTATION_REMOVED,
               HD_EXT_COMPUTATION_UPDATED,
               HD_EXT_COMPUTATION_EXECUTION,
               HD_FREEZE_CULL_FRUSTUM,
               HD_INSTANCER_ADDED,
               HD_INSTANCER_CLEANED,
               HD_INSTANCER_REMOVED,
               HD_INSTANCER_UPDATED,
               HD_RENDER_SETTINGS,
               HD_RENDERER_PLUGIN,
               HD_RPRIM_ADDED,
               HD_RPRIM_CLEANED,
               HD_RPRIM_REMOVED,
               HD_RPRIM_UPDATED,
               HD_SAFE_MODE,
               HD_SELECTION_UPDATE,
               HD_SHARED_EXT_COMPUTATION_DATA,
               HD_SPRIM_ADDED,
               HD_SPRIM_REMOVED,
               HD_SYNC_ALL,
               HD_TASK_ADDED,
               HD_TASK_REMOVED,
               HD_VARYING_STATE);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_DEBUG_CODES_H
