//
// Copyright 2016 Pixar
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

#include "pxr/base/tf/getenv.h"
#include "Arch/env.h"
#include "pxr/base/tf/regTest.h"
#include "pxr/pxr.h"

PXR_NAMESPACE_USING_DIRECTIVE

static bool Test_TfGetenv()
{
  bool status = true;
  std::string testVar = "GetEnvTestsuiteTestVar";
  ArchSetEnv(testVar.c_str(), "testing", true);
  status &= (TfGetenv(testVar, "bogusValue") == "testing");
  ArchRemoveEnv(testVar.c_str());
  status &= (TfGetenv(testVar, "bogusValue") == "bogusValue");

  ArchSetEnv(testVar.c_str(), "42", true);
  status &= (TfGetenvInt(testVar, 99) == 42);
  ArchRemoveEnv(testVar.c_str());
  status &= (TfGetenvInt(testVar, 99) == 99);

  ArchSetEnv(testVar.c_str(), "true", true);
  status &= (TfGetenvBool(testVar, false) == true);
  ArchRemoveEnv(testVar.c_str());
  status &= (TfGetenvBool(testVar, false) == false);

  ArchSetEnv(testVar.c_str(), "TRUE", true);
  status &= (TfGetenvBool(testVar, false) == true);
  ArchRemoveEnv(testVar.c_str());
  status &= (TfGetenvBool(testVar, false) == false);

  ArchSetEnv(testVar.c_str(), "yes", true);
  status &= (TfGetenvBool(testVar, false) == true);

  ArchSetEnv(testVar.c_str(), "YES", true);
  status &= (TfGetenvBool(testVar, false) == true);

  ArchSetEnv(testVar.c_str(), "1", true);
  status &= (TfGetenvBool(testVar, false) == true);

  ArchSetEnv(testVar.c_str(), "ON", true);
  status &= (TfGetenvBool(testVar, false) == true);

  ArchSetEnv(testVar.c_str(), "on", true);
  status &= (TfGetenvBool(testVar, false) == true);

  ArchSetEnv(testVar.c_str(), "false", true);
  status &= (TfGetenvBool(testVar, false) == false);

  ArchSetEnv(testVar.c_str(), "false", true);
  status &= (TfGetenvBool(testVar, true) == false);

  ArchSetEnv(testVar.c_str(), "someothercrap", true);
  status &= (TfGetenvBool(testVar, false) == false);

  ArchSetEnv(testVar.c_str(), "someothercrap", true);
  status &= (TfGetenvBool(testVar, true) == false);

  return status;
}

TF_ADD_REGTEST(TfGetenv);
