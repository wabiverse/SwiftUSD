//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Vdf/grapherOptions.h"

#include "Vdf/node.h"

#include "Tf/iterator.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

///////////////////////////////////////////////////////////////////////////////

VdfGrapherOptions::VdfGrapherOptions() :
    _drawMasks(false),
    _drawAffectsMasks(false),
    _pageWidth(8.5),
    _pageHeight(11.0),
    _uniqueIds(true),
    _displayStyle(DisplayStyleFull),
    _printSingleOutputs(false),
    _omitUnconnectedSpecs(false),
    _drawColorizedConnectionsOnly(false)
{
}

bool
VdfGrapherOptions::DebugNameFilter(
    const std::vector<std::string> &nameList,
    bool includeIfInNameList,
    const VdfNode &node )
{
    TF_FOR_ALL(i, nameList)
        if (TfStringContains(node.GetDebugName(), *i))
            return includeIfInNameList;

    return !includeIfInNameList;
}

PXR_NAMESPACE_CLOSE_SCOPE
