//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ar/packageUtils.h"
#include "Tf/pyResultConversions.h"
#include "pxr/pxrns.h"

#include <boost/python/def.hpp>
#include <boost/python/return_value_policy.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapPackageUtils()
{
  def("IsPackageRelativePath", &ArIsPackageRelativePath, arg("path"));

  def("JoinPackageRelativePath",
      (std::string(*)(const std::vector<std::string> &)) & ArJoinPackageRelativePath,
      arg("paths"));

  def("JoinPackageRelativePath",
      (std::string(*)(const std::pair<std::string, std::string> &)) & ArJoinPackageRelativePath,
      arg("paths"));

  def("JoinPackageRelativePath",
      (std::string(*)(const std::string &, const std::string &)) & ArJoinPackageRelativePath,
      (arg("packagePath"), arg("packagedPath")));

  def("SplitPackageRelativePathOuter", &ArSplitPackageRelativePathOuter, arg("path"));

  def("SplitPackageRelativePathInner", &ArSplitPackageRelativePathInner, arg("path"));
}
