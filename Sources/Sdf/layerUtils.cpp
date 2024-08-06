//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
///
/// \file sdf/layerUtils.cpp

#include "Sdf/layerUtils.h"
#include "Sdf/assetPathResolver.h"
#include "Sdf/fileFormat.h"
#include "Sdf/layer.h"
#include "pxr/pxrns.h"

#include "Ar/packageUtils.h"
#include "Ar/resolver.h"
#include "Tf/pathUtils.h"
#include "Trace/traceImpl.h"

using std::string;

PXR_NAMESPACE_OPEN_SCOPE

namespace {

// Anchor the given relativePath to the same path as the layer
// specified by anchorLayerPath.
string _AnchorRelativePath(const string &anchorLayerPath, const string &relativePath)
{
  const string anchorPath = TfGetPathName(anchorLayerPath);
  return anchorPath.empty() ? relativePath : TfStringCatPaths(anchorPath, relativePath);
}

// Expand a (package path, packaged path) pair until the packaged path is
// a non-package layer that is the root layer of the package layer specified
// by the package path.
std::pair<string, string> _ExpandPackagePath(const std::pair<string, string> &packageRelativePath)
{
  std::pair<string, string> result = packageRelativePath;
  while (1) {
    if (result.second.empty()) {
      break;
    }

    SdfFileFormatConstPtr packagedFormat = SdfFileFormat::FindByExtension(result.second);
    if (!packagedFormat || !packagedFormat->IsPackage()) {
      break;
    }

    result.first = ArJoinPackageRelativePath(result.first, result.second);
    result.second = packagedFormat->GetPackageRootLayerPath(result.first);
  }
  return result;
}

}  // end anonymous namespace

string SdfComputeAssetPathRelativeToLayer(const SdfLayerHandle &anchor, const string &assetPath)
{
  if (!anchor) {
    TF_CODING_ERROR("Invalid anchor layer");
    return string();
  }

  if (assetPath.empty()) {
    TF_CODING_ERROR("Layer path is empty");
    return string();
  }

  TRACE_FUNCTION();

  ArResolver &resolver = ArGetResolver();

  // XXX:
  // This logic possibly wants to move into Ar so that other code
  // that doesn't use Sdf can take advantage of it.

  // Relative asset paths have special behavior when anchoring to a
  // package or packaged layer:
  //
  // - Anchored relative paths (e.g., "./foo/bar.sdf") are always anchored
  //   to the packaged layer in which they are authored. For example, if the
  //   above were authored in the following layers:
  //       "test.package[inner.sdf]" ->  "test.package[foo/bar.sdf]"
  //       "test.package[sub/inner.sdf]" -> "test.package[sub/foo/bar.sdf]"
  //       "test.package" -> "/tmp/test.package[foo/bar.sdf]"
  //
  //   The last case depends on the path of the root layer in the package.
  //   If the package root layer were "inner.sdf", anchoring would give the
  //   same result as the first case; if it were "sub/inner.sdf", it would
  //   give the same result as the second case.
  //
  // - Search relative paths (e.g., "foo/bar.sdf") are first anchored to the
  //   packaged layer in which they are authored. If that does not resolve
  //   to a valid file, the path is then anchored to the package's root
  //   layer. If that does not resolve the path is not anchored and is
  //   resolved as-is.
  //
  if (Sdf_IsPackageOrPackagedLayer(anchor) && TfIsRelativePath(assetPath)) {
    // XXX: The use of repository path or real path is the same as in
    // SdfLayer::ComputeAbsolutePath. This logic might want to move
    // somewhere common.
    const string anchorPackagePath = anchor->GetRepositoryPath().empty() ?
                                         anchor->GetRealPath() :
                                         anchor->GetRepositoryPath();

    // Split the anchoring layer's identifier, since we anchor the asset
    // path against the innermost packaged path. If the anchor layer
    // is a package, anchor against its root layer, which may be
    // nested in another package layer.
    std::pair<string, string> packagePath;
    if (anchor->GetFileFormat()->IsPackage()) {
      packagePath.first = anchorPackagePath;
      packagePath.second = anchor->GetFileFormat()->GetPackageRootLayerPath(anchor->GetRealPath());

      packagePath = _ExpandPackagePath(packagePath);
    }
    else {
      packagePath = ArSplitPackageRelativePathInner(anchorPackagePath);
    }

    const string normAssetPath = TfNormPath(assetPath);
    packagePath.second = _AnchorRelativePath(packagePath.second, normAssetPath);

    string finalLayerPath = ArJoinPackageRelativePath(packagePath);

    // If assetPath is not a search-relative path, we're done. Otherwise,
    // we need to search in the locations described above.
    const bool isSearchRelativePath = assetPath.front() != '.';
    if (!isSearchRelativePath) {
      return finalLayerPath;
    }

    // If anchoring the asset path to the anchor layer resolves to a
    // valid layer, we're done.
    if (!resolver.Resolve(finalLayerPath).empty()) {
      return finalLayerPath;
    }

    // Try anchoring the layer to the owning package's root layer
    // (which may be nested in another package layer). If this resolves
    // to a valid layer, we're done.
    SdfFileFormatConstPtr packageFormat = SdfFileFormat::FindByExtension(packagePath.first);
    if (packageFormat && packageFormat->IsPackage()) {
      packagePath.second = packageFormat->GetPackageRootLayerPath(packagePath.first);
      packagePath = _ExpandPackagePath(packagePath);

      packagePath.second = _AnchorRelativePath(packagePath.second, normAssetPath);
    }
    else {
      packagePath.second = normAssetPath;
    }

    finalLayerPath = ArJoinPackageRelativePath(packagePath);
    if (!resolver.Resolve(finalLayerPath).empty()) {
      return finalLayerPath;
    }

    // If we were unable to resolve this search-relative path within
    // the package, fall through to normal path resolution.
  }

  if (SdfLayer::IsAnonymousLayerIdentifier(assetPath)) {
    return assetPath;
  }

  if (anchor->IsAnonymous()) {
    return resolver.CreateIdentifier(assetPath);
  }

  return resolver.CreateIdentifier(assetPath, anchor->GetResolvedPath());
}

PXR_NAMESPACE_CLOSE_SCOPE
