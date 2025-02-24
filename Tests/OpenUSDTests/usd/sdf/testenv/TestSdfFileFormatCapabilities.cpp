//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/base/tf/staticTokens.h"
#include "pxr/pxr.h"
#include "pxr/usd/sdf/layer.h"
#include "pxr/usd/sdf/textFileFormat.h"

PXR_NAMESPACE_OPEN_SCOPE

#define TEST_SDF_UNWRITABLE_FILE_FORMAT_TOKENS \
  ((Extension, "unwritable"))((VersionStr, "0.0.0"))((Target, ""))

TF_DECLARE_PUBLIC_TOKENS(TestSdfUnwritableFormat_Tokens, TEST_SDF_UNWRITABLE_FILE_FORMAT_TOKENS);

TF_DEFINE_PUBLIC_TOKENS(TestSdfUnwritableFormat_Tokens, TEST_SDF_UNWRITABLE_FILE_FORMAT_TOKENS);

class TestSdfUnwritableFormat : public SdfTextFileFormat {
 public:
  SDF_FILE_FORMAT_FACTORY_ACCESS;

  TestSdfUnwritableFormat()
      : SdfTextFileFormat(TestSdfUnwritableFormat_Tokens->Extension,
                          TestSdfUnwritableFormat_Tokens->VersionStr,
                          TestSdfUnwritableFormat_Tokens->Target)
  {
  }
};

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(TestSdfUnwritableFormat, SdfTextFileFormat);
}

#define TEST_SDF_UNREADABLE_FILE_FORMAT_TOKENS \
  ((Extension, "unreadable"))((VersionStr, "0.0.0"))((Target, "test"))

TF_DECLARE_PUBLIC_TOKENS(TestSdfUnreadableFormat_Tokens, TEST_SDF_UNREADABLE_FILE_FORMAT_TOKENS);

TF_DEFINE_PUBLIC_TOKENS(TestSdfUnreadableFormat_Tokens, TEST_SDF_UNREADABLE_FILE_FORMAT_TOKENS);

class TestSdfUnreadableFormat : public SdfTextFileFormat {
 public:
  SDF_FILE_FORMAT_FACTORY_ACCESS;

  TestSdfUnreadableFormat()
      : SdfTextFileFormat(TestSdfUnreadableFormat_Tokens->Extension,
                          TestSdfUnreadableFormat_Tokens->VersionStr,
                          TestSdfUnreadableFormat_Tokens->Target)
  {
  }
};

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(TestSdfUnreadableFormat, SdfTextFileFormat);
}

#define TEST_SDF_UNEDITABLE_FILE_FORMAT_TOKENS \
  ((Extension, "uneditable"))((VersionStr, "0.0.0"))((Target, "test"))

TF_DECLARE_PUBLIC_TOKENS(TestSdfUneditableFormat_Tokens, TEST_SDF_UNEDITABLE_FILE_FORMAT_TOKENS);

TF_DEFINE_PUBLIC_TOKENS(TestSdfUneditableFormat_Tokens, TEST_SDF_UNEDITABLE_FILE_FORMAT_TOKENS);

class TestSdfUneditableFormat : public SdfTextFileFormat {
 public:
  SDF_FILE_FORMAT_FACTORY_ACCESS;

  TestSdfUneditableFormat()
      : SdfTextFileFormat(TestSdfUneditableFormat_Tokens->Extension,
                          TestSdfUneditableFormat_Tokens->VersionStr,
                          TestSdfUneditableFormat_Tokens->Target)
  {
  }
};

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(TestSdfUneditableFormat, SdfTextFileFormat);
}

PXR_NAMESPACE_CLOSE_SCOPE
