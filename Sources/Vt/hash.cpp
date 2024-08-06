//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Vt/hash.h"
#include "Arch/demangle.h"
#include "Tf/diagnostic.h"
#include "pxr/pxrns.h"

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

namespace Vt_HashDetail {

void _IssueUnimplementedHashError(std::type_info const &t)
{
  TF_CODING_ERROR(
      "Invoked VtHashValue on an object of type <%s>, which "
      "is not hashable by TfHash().  Consider "
      "providing an overload of hash_value() or TfHashAppend().",
      ArchGetDemangled(t).c_str());
}

}  // namespace Vt_HashDetail

PXR_NAMESPACE_CLOSE_SCOPE
