//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/enum.h"
#include "pxr/pxrns.h"

#include "Tf/diagnostic.h"
#include "Tf/errorMark.h"
#include "Tf/hash.h"
#include "Tf/instantiateSingleton.h"
#include "Tf/mallocTag.h"
#include "Tf/registryManager.h"
#include "Tf/safeTypeCompare.h"
#include "Tf/stringUtils.h"
#include "Tf/type.h"

#include "Arch/demangle.h"

#include "Tf/hashmap.h"

#include <OneTBB/tbb/spin_mutex.h>

#include <iostream>
#include <set>

using std::string;
using std::type_info;
using std::vector;

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<TfEnum>();
}

// Convenience typedefs for value/name tables.
typedef TfHashMap<TfEnum, string, TfHash> _EnumToNameTableType;
typedef TfHashMap<string, TfEnum, TfHash> _NameToEnumTableType;
typedef TfHashMap<string, vector<string>, TfHash> _TypeNameToNameVectorTableType;
typedef TfHashMap<string, const type_info *, TfHash> _TypeNameToTypeTableType;

class Tf_EnumRegistry {
  Tf_EnumRegistry(const Tf_EnumRegistry &) = delete;
  Tf_EnumRegistry &operator=(Tf_EnumRegistry &) = delete;

 private:
  static Tf_EnumRegistry &_GetInstance()
  {
    return TfSingleton<Tf_EnumRegistry>::GetInstance();
  }

  Tf_EnumRegistry()
  {
    TfSingleton<Tf_EnumRegistry>::SetInstanceConstructed(*this);
    TfRegistryManager::GetInstance().SubscribeTo<TfEnum>();
  }

  ~Tf_EnumRegistry()
  {
    TfRegistryManager::GetInstance().UnsubscribeFrom<TfEnum>();
  }

  void _Remove(TfEnum val)
  {
    tbb::spin_mutex::scoped_lock lock(_tableLock);

    _typeNameToType.erase(ArchGetDemangled(val.GetType()));

    vector<string> &v = _typeNameToNameVector[val.GetType().name()];
    vector<string> original = v;
    string name = _enumToName[val];

    v.clear();
    for (size_t i = 0; i < original.size(); i++)
      if (original[i] != name)
        v.push_back(original[i]);

    _fullNameToEnum.erase(_enumToFullName[val]);
    _enumToFullName.erase(val);
    _enumToName.erase(val);
    _enumToDisplayName.erase(val);
  }

  tbb::spin_mutex _tableLock;
  _EnumToNameTableType _enumToName;
  _EnumToNameTableType _enumToFullName;
  _EnumToNameTableType _enumToDisplayName;
  _NameToEnumTableType _fullNameToEnum;
  _TypeNameToNameVectorTableType _typeNameToNameVector;
  _TypeNameToTypeTableType _typeNameToType;

  friend class TfEnum;
  friend class TfSingleton<Tf_EnumRegistry>;
};

TF_INSTANTIATE_SINGLETON(Tf_EnumRegistry);

void TfEnum::_AddName(TfEnum val, char const *valNameCstr, char const *displayNameCstr)
{
  TfAutoMallocTag2 tag("Tf", "TfEnum::_AddName");
  string typeName = ArchGetDemangled(val.GetType());

  const string valName = TfSafeString(valNameCstr);
  const string displayName = TfSafeString(displayNameCstr);

  /*
   * In case valName looks like "stuff::VALUE", strip off the leading
   * prefix.
   */
  size_t i = valName.rfind(':');
  string shortName = (i == string::npos) ? valName : valName.substr(i + 1);

  if (shortName.empty())
    return;

  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  string fullName = typeName + "::" + shortName;

  r._enumToName[val] = shortName;
  r._enumToFullName[val] = fullName;
  r._enumToDisplayName[val] = displayName.empty() ? shortName : displayName;
  r._fullNameToEnum[fullName] = val;
  r._typeNameToNameVector[val.GetType().name()].push_back(shortName);
  r._typeNameToType[typeName] = &val.GetType();

  TfRegistryManager::GetInstance().AddFunctionForUnload([&r, val]() { r._Remove(val); });
}

string TfEnum::GetName(TfEnum val)
{
  if (TfSafeTypeCompare(val.GetType(), typeid(int)))
    return TfIntToString(val.GetValueAsInt());

  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _EnumToNameTableType::iterator i = r._enumToName.find(val);
  return (i != r._enumToName.end() ? i->second : "");
}

string TfEnum::GetFullName(TfEnum val)
{
  if (TfSafeTypeCompare(val.GetType(), typeid(int)))
    return TfStringPrintf("int::%d", val.GetValueAsInt());

  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _EnumToNameTableType::iterator i = r._enumToFullName.find(val);
  return (i != r._enumToFullName.end() ? i->second : "");
}

string TfEnum::GetDisplayName(TfEnum val)
{
  if (TfSafeTypeCompare(val.GetType(), typeid(int)))
    return TfIntToString(val.GetValueAsInt());

  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _EnumToNameTableType::iterator i = r._enumToDisplayName.find(val);
  return (i != r._enumToDisplayName.end() ? i->second : "");
}

vector<string> TfEnum::GetAllNames(const type_info &ti)
{
  if (TfSafeTypeCompare(ti, typeid(int)))
    return vector<string>();

  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _TypeNameToNameVectorTableType::iterator i = r._typeNameToNameVector.find(ti.name());
  return (i != r._typeNameToNameVector.end() ? i->second : vector<string>());
}

const type_info *TfEnum::GetTypeFromName(const string &typeName)
{
  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _TypeNameToTypeTableType::iterator i = r._typeNameToType.find(typeName);
  if (i == r._typeNameToType.end())
    return NULL;
  return i->second;
}

TfEnum TfEnum::GetValueFromName(const type_info &ti, const string &name, bool *foundIt)
{
  bool found = false;
  TfEnum value = GetValueFromFullName(ArchGetDemangled(ti) + "::" + name, &found);

  // Make sure that the found enum is the correct type.
  found = found && TfSafeTypeCompare(*(value._typeInfo), ti);
  if (foundIt)
    *foundIt = found;
  return found ? value : TfEnum(-1);
}

TfEnum TfEnum::GetValueFromFullName(const string &fullname, bool *foundIt)
{
  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _NameToEnumTableType::iterator i = r._fullNameToEnum.find(fullname);
  if (i != r._fullNameToEnum.end()) {
    if (foundIt)
      *foundIt = true;
    return TfEnum(i->second);
  }
  else if (fullname.find("int::") == 0) {
    if (foundIt)
      *foundIt = true;
    return TfEnum(atoi(fullname.c_str() + 5));
  }
  else {
    if (foundIt)
      *foundIt = false;
    return TfEnum(-1);
  }
}

void TfEnum::_FatalGetValueError(std::type_info const &typeInfo) const
{
  TF_FATAL_ERROR(
      "Attempted to get a '%s' from a TfEnum holding "
      "a '%s'.",
      ArchGetDemangled(typeInfo).c_str(),
      _typeInfo->name());
}

bool TfEnum::IsKnownEnumType(const std::string &typeName)
{
  Tf_EnumRegistry &r = Tf_EnumRegistry::_GetInstance();
  tbb::spin_mutex::scoped_lock lock(r._tableLock);

  _TypeNameToTypeTableType::iterator i = r._typeNameToType.find(typeName);
  if (i == r._typeNameToType.end())
    return false;
  return true;
}

std::ostream &operator<<(std::ostream &out, const TfEnum &e)
{
  return out << TfEnum::GetFullName(e);
}

PXR_NAMESPACE_CLOSE_SCOPE
