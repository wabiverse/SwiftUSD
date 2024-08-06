//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/hash.h"
#include "Arch/hash.h"
#include "Tf/enum.h"
#include "Tf/stringUtils.h"
#include "Tf/token.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

#include <cstring>

PXR_NAMESPACE_OPEN_SCOPE

void Tf_HashState::_AppendBytes(char const *bytes, size_t numBytes)
{
  _state = ArchHash64(bytes, numBytes, _state);
  _didOne = true;
}

size_t TfHashCharPtr::operator()(const char *ptr) const
{
  return TfHash()(static_cast<const void *>(ptr));
}

size_t TfHashCString::operator()(const char *ptr) const
{
  return ptr ? ArchHash(ptr, std::strlen(ptr)) : 0;
}

bool TfEqualCString::operator()(const char *lhs, const char *rhs) const
{
  return std::strcmp(lhs, rhs) == 0;
}

PXR_NAMESPACE_CLOSE_SCOPE
