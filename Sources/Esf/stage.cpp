//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Esf/stage.h"

#include "Esf/attribute.h"
#include "Esf/journal.h"
#include "Esf/object.h"
#include "Esf/prim.h"
#include "Esf/property.h"
#include "Esf/relationship.h"

PXR_NAMESPACE_OPEN_SCOPE

EsfStageInterface::~EsfStageInterface() = default;

EsfAttribute
EsfStageInterface::GetAttributeAtPath(
    const SdfPath &path,
    EsfJournal *journal) const
{
    if (journal) {
        journal->Add(path, EsfEditReason::ResyncedObject);
    }
    return _GetAttributeAtPath(path);
}

EsfObject
EsfStageInterface::GetObjectAtPath(
    const SdfPath &path,
    EsfJournal *journal) const
{
    if (journal) {
        journal->Add(path, EsfEditReason::ResyncedObject);
    }
    return _GetObjectAtPath(path);
}

EsfPrim
EsfStageInterface::GetPrimAtPath(
    const SdfPath &path,
    EsfJournal *journal) const
{
    if (journal) {
        journal->Add(path, EsfEditReason::ResyncedObject);
    }
    return _GetPrimAtPath(path);
}

EsfProperty
EsfStageInterface::GetPropertyAtPath(
    const SdfPath &path,
    EsfJournal *journal) const
{
    if (journal) {
        journal->Add(path, EsfEditReason::ResyncedObject);
    }
    return _GetPropertyAtPath(path);
}

EsfRelationship
EsfStageInterface::GetRelationshipAtPath(
    const SdfPath &path,
    EsfJournal *journal) const
{
    if (journal) {
        journal->Add(path, EsfEditReason::ResyncedObject);
    }
    return _GetRelationshipAtPath(path);
}

PXR_NAMESPACE_CLOSE_SCOPE
