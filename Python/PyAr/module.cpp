//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/pyModule.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
  TF_WRAP(AssetInfo);
  TF_WRAP(ResolvedPath);
  TF_WRAP(Timestamp);

  TF_WRAP(Resolver);
  TF_WRAP(ResolverContext);
  TF_WRAP(ResolverContextBinder);
  TF_WRAP(ResolverScopedCache);

  TF_WRAP(DefaultResolver);
  TF_WRAP(DefaultResolverContext);

  TF_WRAP(PackageUtils);
  TF_WRAP(Notice);
}
