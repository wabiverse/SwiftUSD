
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_DEBUG_CODES_H
#define PXR_IMAGING_HD_ST_DEBUG_CODES_H

#include "Hd/version.h"
#include "Tf/debug.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEBUG_CODES(HDST_DRAW,
               HDST_DRAW_BATCH,
               HDST_FORCE_DRAW_BATCH_REBUILD,
               HDST_DRAW_ITEM_GATHER,
               HDST_DRAWITEMS_CACHE,
               HDST_DISABLE_FRUSTUM_CULLING,
               HDST_DISABLE_MULTITHREADED_CULLING,
               HDST_DUMP_GLSLFX_CONFIG,
               HDST_DUMP_FAILING_SHADER_SOURCE,
               HDST_DUMP_FAILING_SHADER_SOURCEFILE,
               HDST_DUMP_SHADER_SOURCE,
               HDST_DUMP_SHADER_SOURCEFILE,
               HDST_LOG_COMPUTE_SHADER_PROGRAM_HITS,
               HDST_LOG_COMPUTE_SHADER_PROGRAM_MISSES,
               HDST_LOG_DRAWING_SHADER_PROGRAM_HITS,
               HDST_LOG_DRAWING_SHADER_PROGRAM_MISSES,
               HDST_MATERIAL_ADDED,
               HDST_MATERIAL_REMOVED);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_DEBUG_CODES_H
