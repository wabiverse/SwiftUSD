//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Pcp/pathTranslation.h"
#include "Pcp/mapFunction.h"
#include "Pcp/node.h"
#include "Sdf/path.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static SdfPath
TranslatePathFromNodeToRoot(const PcpNodeRef& sourceNode,
                            const SdfPath& pathInNodeNamespace)
{
    return PcpTranslatePathFromNodeToRoot(sourceNode, pathInNodeNamespace);
}

static SdfPath
TranslatePathFromRootToNode(const PcpNodeRef& destNode,
                            const SdfPath& pathInRootNamespace)
{
    return PcpTranslatePathFromRootToNode(destNode, pathInRootNamespace);
}

} // anonymous namespace 

void wrapPathTranslation()
{
    def("TranslatePathFromNodeToRoot", TranslatePathFromNodeToRoot,
        arg("sourceNode"), arg("pathInNodeNamespace"));

    def("TranslatePathFromRootToNode", TranslatePathFromRootToNode,
        arg("destNode"), arg("pathInRootNamespace"));
}
