//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Plug/notice.h"
#include "Tf/pyNoticeWrapper.h"
#include "Tf/pyResultConversions.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

TF_INSTANTIATE_NOTICE_WRAPPER(PlugNotice::Base, TfNotice);
TF_INSTANTIATE_NOTICE_WRAPPER(PlugNotice::DidRegisterPlugins, PlugNotice::Base);

}  // anonymous namespace

void wrapNotice()
{
  scope noticeScope = class_<PlugNotice>("Notice", no_init);

  TfPyNoticeWrapper<PlugNotice::Base, TfNotice>::Wrap();

  TfPyNoticeWrapper<PlugNotice::DidRegisterPlugins, PlugNotice::Base>::Wrap().def(
      "GetNewPlugins",
      make_function(&PlugNotice::DidRegisterPlugins::GetNewPlugins,
                    return_value_policy<TfPySequenceToList>()));
}
