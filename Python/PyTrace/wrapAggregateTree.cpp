//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Trace/aggregateTree.h"

#include "Tf/makePyConstructor.h"
#include "Tf/pyPtrHelpers.h"

#include <boost/python/class.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace boost::python;

void wrapAggregateTree()
{
  using This = TraceAggregateTree;
  using ThisPtr = TraceAggregateTreePtr;

  class_<This, ThisPtr>("AggregateTree", no_init)
      .def(TfPyRefAndWeakPtr())
      .def(TfMakePyConstructor(&This::New))
      .add_property("root", &This::GetRoot);
}
