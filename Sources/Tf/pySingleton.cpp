//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pySingleton.h"

#include <string>

using std::string;

PXR_NAMESPACE_OPEN_SCOPE

namespace Tf_PySingleton {

bp::object _DummyInit(bp::tuple const & /* args */, bp::dict const & /* kw */)
{
  return bp::object();
}

string _Repr(bp::object const &self, string const &prefix)
{
  string name(bp::extract<string>(self.attr("__class__").attr("__name__")));
  return prefix + name + "()";
}

}  // namespace Tf_PySingleton

Tf_PySingleton::Visitor TfPySingleton()
{
  return Tf_PySingleton::Visitor();
}

Tf_PySingleton::Visitor TfPySingleton(string const &reprPrefix)
{
  return Tf_PySingleton::Visitor(reprPrefix);
}

PXR_NAMESPACE_CLOSE_SCOPE
