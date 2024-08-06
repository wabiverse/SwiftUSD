//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Hd/collectionExpressionEvaluator.h"

#include "Hd/collectionPredicateLibrary.h"
#include "Hd/perfLog.h"
#include "Hd/sceneIndex.h"
#include "Hd/sceneIndexPrimView.h"

#include "Sdf/pathExpression.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

// Traverse the subtree at `rootPath` and add descendant prim paths to `result`.
void _AddAllDescendants(const HdSceneIndexBaseRefPtr &si,
                        const SdfPath &rootPath,
                        SdfPathVector *result)
{
  HdSceneIndexPrimView view(si, rootPath);
  auto it = view.begin();
  ++it;  // skip adding the rootPath iterator entry; we only care about
         // descendants.

  for (; it != view.end(); ++it) {
    const SdfPath &primPath = *it;
    result->push_back(primPath);
  }
}

}  // namespace

HdCollectionExpressionEvaluator::HdCollectionExpressionEvaluator(
    const HdSceneIndexBaseRefPtr &sceneIndex, const SdfPathExpression &expr)
    : HdCollectionExpressionEvaluator(sceneIndex, expr, HdGetCollectionPredicateLibrary())
{
}

HdCollectionExpressionEvaluator::HdCollectionExpressionEvaluator(
    const HdSceneIndexBaseRefPtr &sceneIndex,
    const SdfPathExpression &expr,
    const HdCollectionPredicateLibrary &predLib)
    : _sceneIndex(sceneIndex), _eval(SdfMakePathExpressionEval(expr, predLib))
{
}

SdfPredicateFunctionResult HdCollectionExpressionEvaluator::Match(const SdfPath &path) const
{
  if (IsEmpty()) {
    return SdfPredicateFunctionResult::MakeConstant(false);
  }

  // XXX For a prim path that isn't in the scene index, we'll get an empty
  //     prim entry. The only way to determine if a prim exists at a path is
  //     to query GetChildPrimPaths with its parent path and check if it is
  //     indeed its child.
  //     While we could choose to return MakeVarying(false) for empty prim
  //     entries, that would come at the cost of additional evaluation.
  //
  //     Consider a scene "/world/sets/room/..." where descendants of room
  //     have non-empty prim entries.
  //     The expression "//room//" matches /world/sets/room/ and all its
  //     descendants. If we were to restrict evaluation to non-empty prim
  //     entries, then we'd have to evaluate the expression on each of the
  //     children of room instead of stopping the evaluation at
  //     /world/sets/room.
  //

  // Note that _sceneIndex must be non-null due to the IsEmpty() check above.
  return _eval.Match(path, [sceneIndex = get_pointer(_sceneIndex)](SdfPath const &path) {
    return sceneIndex->GetPrim(path);
  });
}

void HdCollectionExpressionEvaluator::PopulateAllMatches(const SdfPath &rootPath,
                                                         SdfPathVector *const result) const
{
  constexpr MatchKind matchKind = MatchAll;
  PopulateMatches(rootPath, matchKind, result);
}

void HdCollectionExpressionEvaluator::PopulateMatches(const SdfPath &rootPath,
                                                      MatchKind matchKind,
                                                      SdfPathVector *const result) const
{
  if (IsEmpty() || !result) {
    return;
  }

  HD_TRACE_FUNCTION();

  // Serial traversal for now. Couple of ways to improve it:
  // - Use a work queue to farm off subtree traversals.
  // - Add support for incremental search in the evaluator to make evaluation
  //   stateful over a subtree. However, this seems tricky if using the
  //   HdSceneIndexPrim as the domain object for the evaluator since obtaining
  //   its path isn't straightforward.
  //
  const HdSceneIndexBaseRefPtr &si = GetSceneIndex();
  HdSceneIndexPrimView view(si, rootPath);

  for (auto it = view.begin(); it != view.end(); ++it) {
    const SdfPath &primPath = *it;

    const SdfPredicateFunctionResult r = Match(primPath);

    const bool matches = r.GetValue();
    const bool constantOverDescendants = r.IsConstant();

    if (matches) {
      result->push_back(primPath);

      const bool addDescendantPrims = (constantOverDescendants && matchKind == MatchAll) ||
                                      (matchKind == ShallowestMatchesAndAllDescendants);

      if (addDescendantPrims) {
        _AddAllDescendants(si, primPath, result);
      }

      const bool skipDescendantTraversal = addDescendantPrims || (matchKind == ShallowestMatches);

      if (skipDescendantTraversal) {
        it.SkipDescendants();
      }
    }
    else {
      // Result does not match at primPath ...
      if (constantOverDescendants) {
        // ... nor does it on any descendants.
        it.SkipDescendants();
      }
    }
  }
}

PXR_NAMESPACE_CLOSE_SCOPE
