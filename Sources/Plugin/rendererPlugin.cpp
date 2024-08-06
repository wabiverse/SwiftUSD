//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Plugin/hdPrmanLoader/rendererPlugin.h"

#include "Arch/library.h"
#include "Hd/rendererPluginRegistry.h"
#include "Plug/plugin.h"
#include "Plug/registry.h"
#include "Tf/getenv.h"
#include "Tf/setenv.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

typedef HdRenderDelegate *(*CreateDelegateFunc)(HdRenderSettingsMap const &settingsMap);
typedef void (*DeleteDelegateFunc)(HdRenderDelegate *renderDelegate);

static const std::string k_RMANTREE("RMANTREE");
#if defined(ARCH_OS_WINDOWS)
static const std::string k_PATH("PATH");
#endif

// This holds the OS specific plugin info data
static struct HdPrmanLoader {
  static void Load();
  ~HdPrmanLoader();
#if defined(ARCH_OS_LINUX) || defined(ARCH_OS_DARWIN)
  void *libprman = nullptr;
#endif
  void *hdPrman = nullptr;
  CreateDelegateFunc createFunc = nullptr;
  DeleteDelegateFunc deleteFunc = nullptr;
  bool valid = false;
  std::string errorMsg;
} _hdPrman;

void HdPrmanLoader::Load()
{
  static bool inited = false;
  if (inited) {
    return;
  }
  inited = true;

  const std::string rmantree = TfGetenv(k_RMANTREE);
  if (rmantree.empty()) {
    _hdPrman.errorMsg = "The hdPrmanLoader backend requires $RMANTREE to be set.";
    return;
  }

#if defined(ARCH_OS_LINUX) || defined(ARCH_OS_DARWIN)
  // Open $RMANTREE/lib/libprman.so into the global namespace
  const std::string libprmanPath = TfStringCatPaths(rmantree, "lib/libprman" ARCH_LIBRARY_SUFFIX);
  _hdPrman.libprman = ArchLibraryOpen(libprmanPath, ARCH_LIBRARY_NOW | ARCH_LIBRARY_GLOBAL);
  if (!_hdPrman.libprman) {
    _hdPrman.errorMsg = TfStringPrintf("Could not load libprman: %s", ArchLibraryError().c_str());
    return;
  }

#elif defined(ARCH_OS_WINDOWS)
  // Append PATH environment with %RMANTREE%\bin and %RMANTREE%\lib
  std::string path = TfGetenv(k_PATH);
  path += ';' + TfStringCatPaths(rmantree, "bin");
  path += ';' + TfStringCatPaths(rmantree, "lib");
  TfSetenv(k_PATH, path.c_str());
#endif

  // HdPrman is assumed to be next to hdPrmanLoader (this plugin)
  PlugPluginPtr plugin = PlugRegistry::GetInstance().GetPluginWithName("hdPrman");

  if (!plugin) {
    _hdPrman.errorMsg = TfStringPrintf("Could not find hdPrman plugin registration.");
    return;
  }

  _hdPrman.hdPrman = ArchLibraryOpen(plugin->GetPath(), ARCH_LIBRARY_NOW | ARCH_LIBRARY_LOCAL);

  if (!_hdPrman.hdPrman) {
    _hdPrman.errorMsg = TfStringPrintf("Could not load versioned hdPrman backend: %s",
                                       ArchLibraryError().c_str());
    return;
  }

  _hdPrman.createFunc = reinterpret_cast<CreateDelegateFunc>(
      ArchLibraryGetSymbolAddress(_hdPrman.hdPrman, "HdPrmanLoaderCreateDelegate"));
  _hdPrman.deleteFunc = reinterpret_cast<DeleteDelegateFunc>(
      ArchLibraryGetSymbolAddress(_hdPrman.hdPrman, "HdPrmanLoaderDeleteDelegate"));

  if (!_hdPrman.createFunc || !_hdPrman.deleteFunc) {
    _hdPrman.errorMsg =
        "hdPrmanLoader factory methods could not be found "
        "in hdPrman plugin.";
    return;
  }

  _hdPrman.valid = true;
}

HdPrmanLoader::~HdPrmanLoader()
{
  if (hdPrman) {
    // Note: OSX does not support clean unloading of hdPrman.dylib symbols
    ArchLibraryClose(hdPrman);
    hdPrman = nullptr;
  }
#if defined(ARCH_OS_LINUX) || defined(ARCH_OS_DARWIN)
  if (libprman) {
    ArchLibraryClose(libprman);
    libprman = nullptr;
  }
#endif
}

// Register the hdPrman loader plugin
TF_REGISTRY_FUNCTION(TfType)
{
  HdRendererPluginRegistry::Define<HdPrmanLoaderRendererPlugin>();
}

HdPrmanLoaderRendererPlugin::HdPrmanLoaderRendererPlugin()
{
  HdPrmanLoader::Load();
}

HdPrmanLoaderRendererPlugin::~HdPrmanLoaderRendererPlugin() {}

HdRenderDelegate *HdPrmanLoaderRendererPlugin::CreateRenderDelegate()
{
  if (_hdPrman.valid) {
    HdRenderSettingsMap settingsMap;
    return _hdPrman.createFunc(settingsMap);
  }
  else {
    TF_WARN("Could not create hdPrman instance: %s", _hdPrman.errorMsg.c_str());
    return nullptr;
  }
}

HdRenderDelegate *HdPrmanLoaderRendererPlugin::CreateRenderDelegate(
    HdRenderSettingsMap const &settingsMap)
{
  if (_hdPrman.valid) {
    return _hdPrman.createFunc(settingsMap);
  }
  else {
    TF_WARN("Could not create hdPrman instance: %s", _hdPrman.errorMsg.c_str());
    return nullptr;
  }
}

void HdPrmanLoaderRendererPlugin::DeleteRenderDelegate(HdRenderDelegate *renderDelegate)
{
  if (_hdPrman.valid) {
    _hdPrman.deleteFunc(renderDelegate);
  }
}

bool HdPrmanLoaderRendererPlugin::IsSupported(bool /* gpuEnabled */) const
{
  if (!_hdPrman.valid) {
    TF_DEBUG(HD_RENDERER_PLUGIN)
        .Msg("hdPrman renderer plugin unsupported: %s\n", _hdPrman.errorMsg.c_str());
  }

  // Eventually will need to make this deal with whether RIS or XPU is used.
  return _hdPrman.valid;
}

PXR_NAMESPACE_CLOSE_SCOPE
