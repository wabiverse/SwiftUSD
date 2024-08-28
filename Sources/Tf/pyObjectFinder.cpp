//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyObjectFinder.h"
#include "Tf/pyUtils.h"
#include "Tf/staticData.h"
#include "Tf/typeInfoMap.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

using std::type_info;

using namespace boost::python;

PXR_NAMESPACE_OPEN_SCOPE

static TfStaticData<TfTypeInfoMap<Tf_PyObjectFinderBase const *>> _finders;

void Tf_RegisterPythonObjectFinderInternal(std::type_info const &type,
                                           Tf_PyObjectFinderBase const *finder)
{
  _finders->Set(type, finder);
}

object Tf_FindPythonObject(void const *objPtr, std::type_info const &type)
{
  Tf_PyObjectFinderBase const *finder = 0;
  if (Tf_PyObjectFinderBase const **x = _finders->Find(type))
    finder = *x;
  if (finder)
    return finder->Find(objPtr);
  return object();
}

Tf_PyObjectFinderBase::~Tf_PyObjectFinderBase() {}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
