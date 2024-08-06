//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file wrapTestPyStaticTokens.cpp

#include "pxr/pxrns.h"

#include "Tf/pyStaticTokens.h"

PXR_NAMESPACE_OPEN_SCOPE

#define TF_TEST_TOKENS (orange)((pear, "d'Anjou"))

TF_DECLARE_PUBLIC_TOKENS(tfTestStaticTokens, TF_API, TF_TEST_TOKENS);
TF_DEFINE_PUBLIC_TOKENS(tfTestStaticTokens, TF_TEST_TOKENS);

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

namespace {
struct _DummyScope {};
}  // namespace

void wrapTf_TestPyStaticTokens()
{
  TF_PY_WRAP_PUBLIC_TOKENS("_testStaticTokens", tfTestStaticTokens, TF_TEST_TOKENS);

  boost::python::class_<_DummyScope, boost::noncopyable> cls("_TestStaticTokens",
                                                             boost::python::no_init);
  boost::python::scope testScope = cls;

  TF_PY_WRAP_PUBLIC_TOKENS_IN_CURRENT_SCOPE(tfTestStaticTokens, TF_TEST_TOKENS);
}
