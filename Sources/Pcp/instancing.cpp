//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Pcp/instancing.h"
#include "pxr/pxrns.h"

#include "Tf/envSetting.h"
#include "Tf/smallVector.h"
#include "Trace/traceImpl.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(PCP_OVERRIDE_INSTANCEABLE,
                      -1,
                      "Overrides Pcp's default computation for whether a PrimIndex is "
                      "instanceable:\n"
                      " -1: (the default) computes instanceable only in USD mode\n"
                      "  0: NEVER computes instanceable (always returns false)\n"
                      "  1: always compute instanceable, whether in USD mode or not.");

// Visitor to determine if a prim index has instanceable data.
// This essentially checks if a prim index had a direct composition arc
// (e.g. a reference or class) that could be shared with other prims.
struct Pcp_FindInstanceableDataVisitor {
  Pcp_FindInstanceableDataVisitor() : hasInstanceableData(false) {}
  bool Visit(PcpNodeRef node, bool nodeIsInstanceable)
  {
    if (nodeIsInstanceable) {
      hasInstanceableData = true;
    }

    // We're just looking for instanceable data anywhere in the prim
    // index, so if we've found we can return false to cut off the
    // traversal.
    return !hasInstanceableData;
  }

  bool hasInstanceableData;
};

bool Pcp_PrimIndexIsInstanceable(const PcpPrimIndex &primIndex)
{
  TRACE_FUNCTION();

  // For now, instancing functionality is limited to USD mode,
  // unless the special env var is set for testing.
  static const int instancing(TfGetEnvSetting(PCP_OVERRIDE_INSTANCEABLE));

  if ((instancing == 0) || ((!primIndex.IsUsd() && (instancing == -1)))) {
    return false;
  }

  // Check if this prim index introduced any instanceable data.
  // This is a cheap way of determining whether this prim index
  // *could* be instanced without reading any scene description.
  //
  // Note that this means that a prim that is tagged with
  // 'instanceable = true' will not be considered an instance if it does
  // not introduce instanceable data.
  Pcp_FindInstanceableDataVisitor visitor;
  Pcp_TraverseInstanceableStrongToWeak(primIndex, &visitor);
  if (!visitor.hasInstanceableData) {
    return false;
  }

  // Compose the value of the 'instanceable' metadata to see if this
  // prim has been tagged as instanceable.
  bool isInstance = false;
  static const TfToken instanceField = SdfFieldKeys->Instanceable;
  // Stack of nodes left to visit, in strong-to-weak order.
  // Strongest open node is top of the stack.
  TfSmallVector<PcpNodeRef, 64> nodesToVisit;
  nodesToVisit.push_back(primIndex.GetRootNode());
  bool opinionFound = false;
  while (!nodesToVisit.empty()) {
    PcpNodeRef node = nodesToVisit.back();
    nodesToVisit.pop_back();
    if (node.CanContributeSpecs()) {
      const PcpLayerStackSite &site = node.GetSite();
      for (SdfLayerRefPtr const &layer : site.layerStack->GetLayers()) {
        if (layer->HasField(site.path, instanceField, &isInstance)) {
          opinionFound = true;
          break;
        }
      }
      if (opinionFound) {
        break;
      }
    }
    TF_REVERSE_FOR_ALL(childIt, Pcp_GetChildrenRange(node))
    {
      nodesToVisit.push_back(*childIt);
    }
  }
  return isInstance;
}

PXR_NAMESPACE_CLOSE_SCOPE
