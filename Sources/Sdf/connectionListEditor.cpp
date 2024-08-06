//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Sdf/connectionListEditor.h"
#include "Sdf/childrenUtils.h"
#include "Sdf/layer.h"
#include "Tf/ostreamMethods.h"
#include "pxr/pxrns.h"

#include <set>

PXR_NAMESPACE_OPEN_SCOPE

template<class ChildPolicy>
Sdf_ConnectionListEditor<ChildPolicy>::Sdf_ConnectionListEditor(
    const SdfSpecHandle &connectionOwner,
    const TfToken &connectionListField,
    const SdfPathKeyPolicy &typePolicy)
    : Parent(connectionOwner, connectionListField, typePolicy)
{
}

template<class ChildPolicy>
void Sdf_ConnectionListEditor<ChildPolicy>::_OnEditShared(
    SdfListOpType op,
    SdfSpecType specType,
    const std::vector<SdfPath> &oldItems,
    const std::vector<SdfPath> &newItems) const
{
  // XXX The following code tries to manage lifetime of the target
  // specs associated with this list, but it slightly buggy: if
  // multiple lists mention the same target -- ex. if a target is
  // added, appended, and prepended -- then this proxy for a single
  // list has no way to know if the target also exists in those
  // other lists, and so it cannot mangae lifetime on its own.

  if (op == SdfListOpTypeOrdered || op == SdfListOpTypeDeleted) {
    // These ops do not affect target spec lifetime, so there's
    // nothing to do.
    return;
  }

  const SdfPath propertyPath = GetPath();
  SdfLayerHandle layer = GetLayer();

  // A common pattern is to append at the end, so old and new often share a
  // common prefix.  Scan forward until we find a difference, then just
  // operate on any remaining tail.  The caller guarantees that both oldItems
  // and newItems are free of duplicates, so we can't ever have an item in the
  // tail that we skipped over in the common prefix, since that would be a
  // duplicate.

  std::set<value_type> oldItemSet;
  std::set<value_type> newItemSet;
  {
    std::vector<SdfPath>::const_iterator oldItemTail = oldItems.begin(),
                                         newItemTail = newItems.begin();
    auto oldEnd = oldItems.end(), newEnd = newItems.end();
    while (oldItemTail != oldEnd && newItemTail != newEnd && *oldItemTail == *newItemTail) {
      ++oldItemTail, ++newItemTail;
    }
    oldItemSet.insert(oldItemTail, oldEnd);
    newItemSet.insert(newItemTail, newEnd);
  }

  // Need to remove all children in oldItems that are not in newItems.
  std::vector<SdfPath> childrenToRemove;
  std::set_difference(oldItemSet.begin(),
                      oldItemSet.end(),
                      newItemSet.begin(),
                      newItemSet.end(),
                      std::back_inserter(childrenToRemove));
  TF_FOR_ALL(child, childrenToRemove)
  {
    if (!Sdf_ChildrenUtils<ChildPolicy>::RemoveChild(layer, propertyPath, *child)) {
      // Some data backends procedurally generate the children specs based
      // on the listops as an optimization, so if we failed to remove a
      // child here, it could be that.  If no spec is present, then we
      // consider things to be okay and do not issue an error.
      const SdfPath specPath = ChildPolicy::GetChildPath(propertyPath, *child);
      if (layer->HasSpec(specPath)) {
        TF_CODING_ERROR("Failed to remove spec at <%s>", specPath.GetText());
      }
    }
  }

  // Need to add all children in newItems that are not in oldItems.
  std::vector<SdfPath> childrenToAdd;
  std::set_difference(newItemSet.begin(),
                      newItemSet.end(),
                      oldItemSet.begin(),
                      oldItemSet.end(),
                      std::back_inserter(childrenToAdd));
  TF_FOR_ALL(child, childrenToAdd)
  {
    const SdfPath specPath = ChildPolicy::GetChildPath(propertyPath, *child);
    if (layer->HasSpec(specPath)) {
      continue;
    }

    if (!Sdf_ChildrenUtils<ChildPolicy>::CreateSpec(layer, specPath, specType)) {
      TF_CODING_ERROR("Failed to create spec at <%s>", specPath.GetText());
    }
  }
}

template<class ChildPolicy>
Sdf_ConnectionListEditor<ChildPolicy>::~Sdf_ConnectionListEditor() = default;

////////////////////////////////////////
// Sdf_AttributeConnectionListEditor
////////////////////////////////////////

Sdf_AttributeConnectionListEditor::Sdf_AttributeConnectionListEditor(
    const SdfSpecHandle &owner, const SdfPathKeyPolicy &typePolicy)
    : Parent(owner, SdfFieldKeys->ConnectionPaths, typePolicy)
{
}

Sdf_AttributeConnectionListEditor::~Sdf_AttributeConnectionListEditor() = default;

void Sdf_AttributeConnectionListEditor::_OnEdit(SdfListOpType op,
                                                const std::vector<SdfPath> &oldItems,
                                                const std::vector<SdfPath> &newItems) const
{
  return Sdf_ConnectionListEditor<Sdf_AttributeConnectionChildPolicy>::_OnEditShared(
      op, SdfSpecTypeConnection, oldItems, newItems);
}

////////////////////////////////////////
// Sdf_RelationshipTargetListEditor
////////////////////////////////////////

Sdf_RelationshipTargetListEditor::Sdf_RelationshipTargetListEditor(
    const SdfSpecHandle &owner, const SdfPathKeyPolicy &typePolicy)
    : Parent(owner, SdfFieldKeys->TargetPaths, typePolicy)
{
}

Sdf_RelationshipTargetListEditor::~Sdf_RelationshipTargetListEditor() = default;

void Sdf_RelationshipTargetListEditor::_OnEdit(SdfListOpType op,
                                               const std::vector<SdfPath> &oldItems,
                                               const std::vector<SdfPath> &newItems) const
{
  return Sdf_ConnectionListEditor<Sdf_RelationshipTargetChildPolicy>::_OnEditShared(
      op, SdfSpecTypeRelationshipTarget, oldItems, newItems);
}

PXR_NAMESPACE_CLOSE_SCOPE
