//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdf/declareHandles.h"
#include "Sdf/layer.h"
#include "Sdf/specType.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

bool Sdf_CanCastToType(const SdfSpec &spec, const std::type_info &destType)
{
  return Sdf_SpecType::CanCast(spec.GetSpecType(), destType);
}

bool Sdf_CanCastToTypeCheckSchema(const SdfSpec &spec, const std::type_info &destType)
{
  return Sdf_SpecType::CanCast(spec, destType);
}

template<> SdfHandleTo<SdfLayer>::Handle SdfCreateHandle(SdfLayer *p)
{
  return SdfHandleTo<SdfLayer>::Handle(p);
}

PXR_NAMESPACE_CLOSE_SCOPE
