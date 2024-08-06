//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_PCP_PRIM_INDEX_STACK_FRAME_H
#define PXR_USD_PCP_PRIM_INDEX_STACK_FRAME_H

#include "Pcp/arc.h"
#include "Pcp/node.h"
#include "Pcp/site.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class PcpPrimIndex;

/// \class PcpPrimIndex_StackFrame
///
/// Internal helper class for tracking recursive invocations of
/// the prim indexing algorithm.
///
class PcpPrimIndex_StackFrame {
 public:
  PcpPrimIndex_StackFrame(PcpLayerStackSite const &requestedSite,
                          PcpNodeRef const &parentNode,
                          PcpArc *arcToParent,
                          PcpPrimIndex_StackFrame *previousFrame,
                          PcpPrimIndex const *originatingIndex,
                          bool skipDuplicateNodes)
      : previousFrame(previousFrame),
        requestedSite(requestedSite),
        parentNode(parentNode),
        arcToParent(arcToParent),
        originatingIndex(originatingIndex),
        skipDuplicateNodes(skipDuplicateNodes)
  {
  }

  /// Link to the previous recursive invocation.
  PcpPrimIndex_StackFrame *previousFrame;

  /// The site of the prim index being built by this recursive
  /// call to Pcp_BuildPrimIndex.
  PcpLayerStackSite requestedSite;

  /// The node in the parent graph that will be the parent of the prim index
  /// being built by this recursive call.
  PcpNodeRef parentNode;

  /// The arc connecting the prim index being built by this recursive
  /// call to the parent node in the previous stack frame.
  PcpArc *arcToParent;

  /// The outer-most index whose computation originated this recursive chain.
  /// This is meant for debugging support.
  PcpPrimIndex const *originatingIndex;

  /// Whether the prim index being built by this recursive call should
  /// skip adding nodes if another node exists with the same site.
  bool skipDuplicateNodes;
};

/// \class PcpPrimIndex_StackFrameIterator
///
/// Iterator for walking up a node's ancestors while potentially crossing
/// stack frames.
///
class PcpPrimIndex_StackFrameIterator {
 public:
  PcpNodeRef node;
  PcpPrimIndex_StackFrame *previousFrame;

  PcpPrimIndex_StackFrameIterator(const PcpNodeRef &n, PcpPrimIndex_StackFrame *f)
      : node(n), previousFrame(f)
  {
  }

  /// Step to the next parent node.
  void Next()
  {
    if (node.GetArcType() != PcpArcTypeRoot) {
      // Step to the next parent within this graph.
      node = node.GetParentNode();
    }
    else if (previousFrame) {
      // No more parents in this graph, but there is an outer
      // prim index that this node will become part of.
      // Step to the (eventual) parent in that graph.
      node = previousFrame->parentNode;
      previousFrame = previousFrame->previousFrame;
    }
    else {
      // No more parents.
      node = PcpNodeRef();
    }
  }

  /// Step to the first parent node in the next recursive call.
  void NextFrame()
  {
    if (previousFrame) {
      node = previousFrame->parentNode;
      previousFrame = previousFrame->previousFrame;
    }
    else {
      node = PcpNodeRef();
    }
  }

  /// Get the type of arc connecting the current node with its parent.
  PcpArcType GetArcType()
  {
    if (node.GetArcType() != PcpArcTypeRoot) {
      // Use the current node's arc type.
      return node.GetArcType();
    }
    else if (previousFrame) {
      // No more parents in this graph, but there is an outer
      // prim index, so consult arcToParent.
      return previousFrame->arcToParent->type;
    }
    else {
      // No more parents; this must be the absolute final root.
      return PcpArcTypeRoot;
    }
  }
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_PCP_PRIM_INDEX_STACK_FRAME_H
