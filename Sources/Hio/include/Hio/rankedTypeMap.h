//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HIO_RANKED_TYPE_MAP_H
#define PXR_IMAGING_HIO_RANKED_TYPE_MAP_H

/// \file hio/rankedTypeMap.h

#include "Plug/plugin.h"
#include "Plug/registry.h"
#include "Tf/debug.h"
#include "Tf/hashmap.h"
#include "Tf/stringUtils.h"
#include "Tf/token.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HioRankedTypeMap
///
/// Holds a token-to-type map with support for precedence per type.
///
class HioRankedTypeMap {
 public:
  typedef TfToken key_type;
  typedef TfType mapped_type;
  typedef int Precedence;

  /// Add key/value pairs from plugins.  If \p includeList isn't empty then
  /// it's a comma separated list of types and only those types are added.
  /// \p keyMetadataName has the metadata key with the single key or a
  /// list of keys to map to the type.  All types derived from \p baseType
  /// are considered.
  template<class DEBUG_TYPE>
  void Add(const mapped_type &baseType,
           const std::string &keyMetadataName,
           DEBUG_TYPE debugType,
           const std::string &includeList = std::string());

  /// Add a key/value pair if it's not in the map or the given precedence
  /// is larger than the current precedence.  This does nothing if the
  /// value is the unknown type.
  void Add(const key_type &key, const mapped_type &type, Precedence precedence)
  {
    if (type) {
      auto i = _typeMap.find(key);
      if (i == _typeMap.end() || i->second.precedence < precedence) {
        _typeMap[key] = {type, precedence};
      }
    }
  }

  /// Returns the highest precedence type for the given key or the unknown
  /// type if the key was not added.
  mapped_type Find(const key_type &key) const
  {
    auto i = _typeMap.find(key);
    return i == _typeMap.end() ? mapped_type() : i->second.type;
  }

 private:
  struct _Mapped {
    TfType type;
    Precedence precedence;
  };
  typedef TfToken::HashFunctor _Hash;
  typedef TfHashMap<key_type, _Mapped, _Hash> _TypeMap;

  _TypeMap _typeMap;
};

template<class DEBUG_TYPE>
void HioRankedTypeMap::Add(const mapped_type &baseType,
                           const std::string &keyMetadataName,
                           DEBUG_TYPE debugType,
                           const std::string &includeList)
{
  // Statically load all plugin information, note that Plug does not crack
  // open the libraries, it only reads metadata from text files.
  PlugRegistry &plugReg = PlugRegistry::GetInstance();
  std::set<TfType> types;
  PlugRegistry::GetAllDerivedTypes(baseType, &types);

  const std::vector<std::string> restrictions = TfStringSplit(includeList, ",");

  for (auto type : types) {
    // Get the plugin.
    PlugPluginPtr plugin = plugReg.GetPluginForType(type);
    if (!plugin) {
      TF_DEBUG(debugType).Msg(
          "[PluginDiscover] Plugin could not be loaded "
          "for TfType '%s'\n",
          type.GetTypeName().c_str());
      continue;
    }

    // Check the includeList.
    if (!restrictions.empty()) {
      bool goodPlugin = false;
      for (const auto &restriction : restrictions) {
        if (type.GetTypeName() == restriction) {
          goodPlugin = true;
        }
      }
      if (!goodPlugin) {
        TF_DEBUG(debugType).Msg("[PluginDiscover] Skipping restricted plugin: '%s'\n",
                                type.GetTypeName().c_str());
        continue;
      }
    }

    JsObject const &metadata = plugin->GetMetadataForType(type);

    JsObject::const_iterator keyIt = metadata.find(keyMetadataName);
    if (keyIt == metadata.end()) {
      TF_RUNTIME_ERROR(
          "[PluginDiscover] '%s' metadata "
          "was not present for plugin '%s'\n",
          keyMetadataName.c_str(),
          type.GetTypeName().c_str());
      continue;
    }

    // Default precedence is 1. Plugins at equal precedence will be
    // registered in order of discovery.
    int precedence = 1;

    JsObject::const_iterator precedenceIt = metadata.find("precedence");
    if (precedenceIt != metadata.end()) {
      if (!precedenceIt->second.Is<int>()) {
        TF_RUNTIME_ERROR(
            "[PluginDiscover] 'precedence' metadata "
            "can not be read for plugin '%s'\n",
            type.GetTypeName().c_str());
      }
      else {
        precedence = precedenceIt->second.Get<int>();
      }
    }

    TF_DEBUG(debugType).Msg("[PluginDiscover] Plugin discovered '%s'\n",
                            type.GetTypeName().c_str());

    typedef std::string Name;
    if (keyIt->second.Is<Name>()) {
      // single name
      Name const &name = keyIt->second.Get<Name>();
      Add(TfToken(name), type, precedence);
    }
    else if (keyIt->second.IsArrayOf<Name>()) {
      // list of names
      for (const auto &name : keyIt->second.GetArrayOf<Name>()) {
        Add(TfToken(name), type, precedence);
      }
    }
  }
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif
