//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Ar/notice.h"

#include "Tf/registryManager.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<ArNotice::ResolverNotice, TfType::Bases<TfNotice>>();
  TfType::Define<ArNotice::ResolverChanged, TfType::Bases<ArNotice::ResolverNotice>>();
}

ArNotice::ResolverNotice::ResolverNotice() = default;
ArNotice::ResolverNotice::~ResolverNotice() = default;

ArNotice::ResolverChanged::ResolverChanged()
    : ResolverChanged([](const ArResolverContext &) { return true; })
{
}

ArNotice::ResolverChanged::ResolverChanged(
    const std::function<bool(const ArResolverContext &)> &affectsFn)
    : _affects(affectsFn)
{
}

ArNotice::ResolverChanged::~ResolverChanged() = default;

bool ArNotice::ResolverChanged::AffectsContext(const ArResolverContext &ctx) const
{
  return _affects(ctx);
}

PXR_NAMESPACE_CLOSE_SCOPE
