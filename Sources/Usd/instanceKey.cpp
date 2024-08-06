//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/instanceKey.h"
#include "Pcp/primIndex.h"
#include "Tf/hash.h"
#include "Usd/resolver.h"
#include "pxr/pxrns.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

Usd_InstanceKey::Usd_InstanceKey() : _hash(_ComputeHash()) {}

static UsdStagePopulationMask _MakeMaskRelativeTo(SdfPath const &path,
                                                  UsdStagePopulationMask const &mask)
{
  SdfPath const &absRoot = SdfPath::AbsoluteRootPath();
  std::vector<SdfPath> maskPaths = mask.GetPaths();
  for (SdfPath &maskPath : maskPaths) {
    if (maskPath.HasPrefix(path)) {
      maskPath = maskPath.ReplacePrefix(path, absRoot);
    }
    else {
      maskPath = SdfPath();
    }
  }
  // Remove the empty paths to the end, and construct a mask with the
  // translated paths.
  return UsdStagePopulationMask(maskPaths.begin(),
                                std::remove(maskPaths.begin(), maskPaths.end(), SdfPath()));
}

static UsdStageLoadRules _MakeLoadRulesRelativeTo(SdfPath const &path,
                                                  UsdStageLoadRules const &rules)
{
  UsdStageLoadRules::Rule rootRule = rules.GetEffectiveRuleForPath(path);
  std::vector<std::pair<SdfPath, UsdStageLoadRules::Rule>> elems = rules.GetRules();

  SdfPath const &absRoot = SdfPath::AbsoluteRootPath();
  for (auto &p : elems) {
    if (p.first == path) {
      p.first = absRoot;
      p.second = rootRule;
    }
    else if (p.first.HasPrefix(path)) {
      p.first = p.first.ReplacePrefix(path, absRoot);
    }
    else {
      p.first = SdfPath();
    }
  }
  elems.erase(std::remove_if(elems.begin(),
                             elems.end(),
                             [](std::pair<SdfPath, UsdStageLoadRules::Rule> const &rule) {
                               return rule.first.IsEmpty();
                             }),
              elems.end());

  // Ensure the first element is the root rule.
  if (elems.empty() || elems.front().first != absRoot) {
    elems.emplace(elems.begin(), absRoot, rootRule);
  }
  else {
    elems.front().second = rootRule;
  }

  UsdStageLoadRules ret;
  ret.SetRules(elems);
  ret.Minimize();
  return ret;
}

Usd_InstanceKey::Usd_InstanceKey(const PcpPrimIndex &instance,
                                 const UsdStagePopulationMask *mask,
                                 const UsdStageLoadRules &loadRules)
    : _pcpInstanceKey(instance)
{
  Usd_ComputeClipSetDefinitionsForPrimIndex(instance, &_clipDefs);

  // Make the population mask "relative" to this prim index by removing the
  // index's path prefix from all paths in the mask that it prefixes.  So for
  // example, if the mask is [/World/set/prop1, /World/set/tableGroup/table,
  // /World/set/prop2], and this prim index is /World/set/tableGroup, then we
  // want the resulting mask to be [/table].  The special cases where the mask
  // includes the whole subtree or excludes the whole subtree are easy to deal
  // with.
  if (!mask) {
    _mask = UsdStagePopulationMask::All();
  }
  else {
    _mask = _MakeMaskRelativeTo(instance.GetPath(), *mask);
  }

  // Do the same with the load rules.
  _loadRules = _MakeLoadRulesRelativeTo(instance.GetPath(), loadRules);

  // Compute and cache the hash code.
  _hash = _ComputeHash();
}

bool Usd_InstanceKey::operator==(const Usd_InstanceKey &rhs) const
{
  return _hash == rhs._hash && _pcpInstanceKey == rhs._pcpInstanceKey &&
         _clipDefs == rhs._clipDefs && _mask == rhs._mask && _loadRules == rhs._loadRules;
}

size_t Usd_InstanceKey::_ComputeHash() const
{
  return TfHash::Combine(_pcpInstanceKey, _clipDefs, _mask, _loadRules);
}

std::ostream &operator<<(std::ostream &os, const Usd_InstanceKey &key)
{
  os << "_pcpInstanceKey:\n"
     << key._pcpInstanceKey.GetString() << '\n'
     << "_mask: " << key._mask << '\n'
     << "_loadRules: " << key._loadRules << '\n'
     << "_hash: " << key._hash << '\n';
  return os;
}

PXR_NAMESPACE_CLOSE_SCOPE
