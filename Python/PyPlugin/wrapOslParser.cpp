//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ndr/node.h"
#include "Ndr/nodeDiscoveryResult.h"
#include "Plugin/sdrOsl/oslParser.h"
#include "Sdr/shaderNode.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

// Expose the unique_ptr returned from `Parse()` as a raw ptr. The Python side
// will be responsible for managing this object.
static SdrShaderNodePtr _Parse(SdrOslParserPlugin &self,
                               const NdrNodeDiscoveryResult &discoveryResult)
{
  return dynamic_cast<SdrShaderNodePtr>(self.Parse(discoveryResult).release());
}

// Note that this parser is only wrapped for testing purposes. In real-world
// scenarios, it should not be used directly.
void wrapOslParser()
{
  typedef SdrOslParserPlugin This;

  return_value_policy<copy_const_reference> copyRefPolicy;

  class_<This, boost::noncopyable>("OslParser")
      .def("Parse", &_Parse, return_value_policy<manage_new_object>())
      .def("GetDiscoveryTypes", &This::GetDiscoveryTypes, copyRefPolicy)
      .def("GetSourceType", &This::GetSourceType, copyRefPolicy);
}
