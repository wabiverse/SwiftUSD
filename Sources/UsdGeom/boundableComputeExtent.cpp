//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "UsdGeom/boundable.h"
#include "UsdGeom/boundableComputeExtent.h"

#include "Js/value.h"
#include "Plug/notice.h"
#include "Plug/plugin.h"
#include "Plug/registry.h"
#include "Tf/instantiateSingleton.h"
#include "Tf/singleton.h"
#include "Tf/weakBase.h"

#include <OneTBB/tbb/queuing_rw_mutex.h>
#include <memory>
#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

namespace {

class _FunctionRegistry : public TfWeakBase {
 public:
  static _FunctionRegistry &GetInstance()
  {
    return TfSingleton<_FunctionRegistry>::GetInstance();
  }

  _FunctionRegistry() : _initialized(false)
  {
    // Calling SubscribeTo may cause functions to be registered
    // while we're still in the c'tor, so make sure to call
    // SetInstanceConstructed to allow reentrancy.
    TfSingleton<_FunctionRegistry>::SetInstanceConstructed(*this);
    TfRegistryManager::GetInstance().SubscribeTo<UsdGeomBoundable>();

    // Mark initialization as completed for waiting consumers.
    _initialized.store(true, std::memory_order_release);

    // Register for new plugins being registered so we can invalidate
    // this registry.
    TfNotice::Register(TfCreateWeakPtr(this), &_FunctionRegistry::_DidRegisterPlugins);
  }

  void RegisterComputeFunction(const TfType &schemaType, const UsdGeomComputeExtentFunction &fn)
  {
    bool didInsert = false;
    {
      _RWMutex::scoped_lock lock(_mutex, /* write = */ true);
      didInsert = _registry.emplace(schemaType, fn).second;
    }

    if (!didInsert) {
      TF_CODING_ERROR(
          "UsdGeomComputeExtentFunction already registered for "
          "prim type '%s'",
          schemaType.GetTypeName().c_str());
    }
  }

  UsdGeomComputeExtentFunction GetComputeFunction(const UsdPrim &prim)
  {
    _WaitUntilInitialized();

    // Get the actual schema type from the prim definition.
    const TfType &primSchemaType = prim.GetPrimTypeInfo().GetSchemaType();
    if (!primSchemaType) {
      TF_CODING_ERROR("Could not find prim type '%s' for prim %s",
                      prim.GetTypeName().GetText(),
                      UsdDescribe(prim).c_str());
      return nullptr;
    }

    UsdGeomComputeExtentFunction fn = nullptr;
    if (_FindFunctionForType(primSchemaType, &fn)) {
      return fn;
    }

    const std::vector<TfType> primSchemaTypeAndBases = _GetTypesThatMayHaveRegisteredFunctions(
        primSchemaType);

    auto i = primSchemaTypeAndBases.cbegin();
    for (auto e = primSchemaTypeAndBases.cend(); i != e; ++i) {
      const TfType &type = *i;
      if (_FindFunctionForType(type, &fn)) {
        break;
      }

      if (_LoadPluginForType(type)) {
        // If we loaded the plugin for this type, a new function may
        // have been registered so look again.
        if (_FindFunctionForType(type, &fn)) {
          break;
        }
      }
    }

    // fn should point to the function to use for all types in the
    // range [primSchemaTypeAndBases.begin(), i). Note it may
    // also be nullptr if no function was found; we cache this
    // as well to avoid looking it up again.
    _RWMutex::scoped_lock lock(_mutex, /* write = */ true);
    for (auto it = primSchemaTypeAndBases.cbegin(); it != i; ++it) {
      _registry.emplace(*it, fn);
    }

    return fn;
  }

 private:
  // Wait until initialization of the singleton is completed.
  void _WaitUntilInitialized()
  {
    while (ARCH_UNLIKELY(!_initialized.load(std::memory_order_acquire))) {
      std::this_thread::yield();
    }
  }

  // Return a list of TfTypes that should be examined to find a compute
  // function for the given type.
  std::vector<TfType> _GetTypesThatMayHaveRegisteredFunctions(const TfType &type) const
  {
    std::vector<TfType> result;
    type.GetAllAncestorTypes(&result);

    // Functions can only be registered on UsdGeomBoundable-derived
    // classes, so remove all other types, taking care not to alter
    // the relative order of the remaining results.
    static const TfType boundableType = TfType::Find<UsdGeomBoundable>();
    result.erase(std::remove_if(result.begin(),
                                result.end(),
                                [](const TfType &t) { return !t.IsA(boundableType); }),
                 result.end());
    return result;
  }

  // Load the plugin for the given type if it supplies a compute function.
  bool _LoadPluginForType(const TfType &type) const
  {
    PlugRegistry &plugReg = PlugRegistry::GetInstance();

    const JsValue implementsComputeExtent = plugReg.GetDataFromPluginMetaData(
        type, "implementsComputeExtent");
    if (!implementsComputeExtent.Is<bool>() || !implementsComputeExtent.Get<bool>()) {
      return false;
    }

    const PlugPluginPtr pluginForType = plugReg.GetPluginForType(type);
    if (!pluginForType) {
      TF_CODING_ERROR("Could not find plugin for '%s'", type.GetTypeName().c_str());
      return false;
    }

    return pluginForType->Load();
  }

  void _DidRegisterPlugins(const PlugNotice::DidRegisterPlugins &n)
  {
    // Erase the entries in _registry which have a null
    // ComputeExtentFunction registered, since newly-registered plugins may
    // provide a valid computeExtentFunction for these type entries.
    // Note that we retain entries which have valid ComputeExtentFunction
    // defined.
    //
    _RWMutex::scoped_lock lock(_mutex, /* write = */ true);
    _Registry::iterator itr = _registry.begin(), end = _registry.end();
    while (itr != end) {
      if (!itr->second) {
        itr = _registry.erase(itr);
        end = _registry.end();
        continue;
      }
      itr++;
    }
  }

  bool _FindFunctionForType(const TfType &type, UsdGeomComputeExtentFunction *fn) const
  {
    _RWMutex::scoped_lock lock(_mutex, /* write = */ false);
    return TfMapLookup(_registry, type, fn);
  }

 private:
  using _RWMutex = tbb::queuing_rw_mutex;
  mutable _RWMutex _mutex;

  using _Registry = std::unordered_map<TfType, UsdGeomComputeExtentFunction, TfHash>;
  _Registry _registry;

  std::atomic<bool> _initialized;
};

}  // namespace

TF_INSTANTIATE_SINGLETON(_FunctionRegistry);

static bool _ComputeExtentFromPlugins(const UsdGeomBoundable &boundable,
                                      const UsdTimeCode &time,
                                      const GfMatrix4d *transform,
                                      VtVec3fArray *extent)
{
  if (!boundable) {
    TF_CODING_ERROR("Invalid UsdGeomBoundable %s", UsdDescribe(boundable.GetPrim()).c_str());
    return false;
  }

  const UsdGeomComputeExtentFunction fn = _FunctionRegistry::GetInstance().GetComputeFunction(
      boundable.GetPrim());
  VtVec3fArray tmpExt;
  if (fn && (*fn)(boundable, time, transform, &tmpExt)) {
    if (tmpExt.size() == 2) {
      *extent = std::move(tmpExt);
      return true;
    }
    else {
      TF_CODING_ERROR(
          "Plugin compute extent function produced an extent "
          "with %zu elements instead of 2 for %s",
          tmpExt.size(),
          UsdDescribe(boundable.GetPrim()).c_str());
    }
  }
  return false;
}

bool UsdGeomBoundable::ComputeExtentFromPlugins(const UsdGeomBoundable &boundable,
                                                const UsdTimeCode &time,
                                                const GfMatrix4d &transform,
                                                VtVec3fArray *extent)
{
  return _ComputeExtentFromPlugins(boundable, time, &transform, extent);
}

bool UsdGeomBoundable::ComputeExtentFromPlugins(const UsdGeomBoundable &boundable,
                                                const UsdTimeCode &time,
                                                VtVec3fArray *extent)
{
  return _ComputeExtentFromPlugins(boundable, time, nullptr, extent);
}

void UsdGeomRegisterComputeExtentFunction(const TfType &primType,
                                          const UsdGeomComputeExtentFunction &fn)
{
  if (!primType.IsA<UsdGeomBoundable>()) {
    TF_CODING_ERROR("Prim type '%s' must derive from UsdGeomBoundable",
                    primType.GetTypeName().c_str());
    return;
  }

  if (!fn) {
    TF_CODING_ERROR("Invalid function registered for prim type '%s'",
                    primType.GetTypeName().c_str());
    return;
  }

  _FunctionRegistry::GetInstance().RegisterComputeFunction(primType, fn);
}

PXR_NAMESPACE_CLOSE_SCOPE
