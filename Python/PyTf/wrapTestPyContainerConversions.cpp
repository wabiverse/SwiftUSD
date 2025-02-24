//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include <locale>
#include <utility>
#include <vector>

#include "Tf/token.h"

#include <boost/python/class.hpp>

using namespace boost::python;
using std::pair;
using std::vector;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

class Tf_TestPyContainerConversions {
 public:
  static vector<double> GetVectorTimesTwo(const vector<int> &inVec)
  {
    vector<double> ret;
    for (size_t i = 0; i < inVec.size(); i++) {
      ret.push_back(inVec[i] * 2.0);
    }

    return ret;
  }

  static pair<double, double> GetPairTimesTwo(const pair<int, int> &inPair)
  {
    return pair<double, double>(inPair.first * 2.0, inPair.second * 2.0);
  }

  // This method simply returns the vector of tokens its given.
  // It's purpose is to allow testing container conversions both to and
  // from Python.
  static vector<TfToken> GetTokens(const vector<TfToken> &inTokens)
  {
    return inTokens;
  }
};

}  // anonymous namespace

void wrapTf_TestPyContainerConversions()
{
  typedef Tf_TestPyContainerConversions This;

  class_<This, boost::noncopyable>("Tf_TestPyContainerConversions")
      .def("GetVectorTimesTwo", &This::GetVectorTimesTwo)
      .staticmethod("GetVectorTimesTwo")

      .def("GetPairTimesTwo", &This::GetPairTimesTwo)
      .staticmethod("GetPairTimesTwo")

      .def("GetTokens", &This::GetTokens)
      .staticmethod("GetTokens");
}
