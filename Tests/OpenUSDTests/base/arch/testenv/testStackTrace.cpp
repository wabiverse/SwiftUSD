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

#include "Arch/defines.h"
#include "Arch/error.h"
#include "Arch/fileSystem.h"
#include "Arch/stackTrace.h"
#include "Arch/testArchUtil.h"
#include "pxr/pxr.h"

#include <cstdlib>
#include <string>

PXR_NAMESPACE_USING_DIRECTIVE

int main(int argc, char **argv)
{
  // Verify the "is crashing" flag is initialized properly, and doesn't
  // get modified until we call the fatal process state handler below.
  ARCH_AXIOM(!ArchIsAppCrashing());

  ArchSetProgramNameForErrors("testArch ArchError");
  ArchTestCrashArgParse(argc, argv);

  ARCH_AXIOM(!ArchIsAppCrashing());

  std::string log = ArchMakeTmpFileName("statusLogTester");
  FILE *logFile;

  ARCH_AXIOM((logFile = ArchOpenFile(log.c_str(), "w")) != NULL);
  fputs("fake log\n", logFile);
  fputs("let's throw in a weird printf %1024$s specifier\n", logFile);
  fclose(logFile);

  ArchLogStackTrace("Crashing", true, log.c_str());
  ArchUnlinkFile(log.c_str());

  ARCH_AXIOM(!ArchIsAppCrashing());
  ArchLogCurrentProcessState("Test Non-Fatal");

  ARCH_AXIOM(!ArchIsAppCrashing());
  ArchLogFatalProcessState("Test Fatal");

  // Now we should be marked as crashing
  ARCH_AXIOM(ArchIsAppCrashing());

  // test crashing with and without spawning
  ArchTestCrash(ArchTestCrashMode::ReadInvalidAddresses);
  ArchTestCrash(ArchTestCrashMode::ReadInvalidAddressesWithThread);

  // test GetStackTrace
  std::vector<std::string> stackTrace = ArchGetStackTrace(20);
  bool found = false;
  for (unsigned int i = 0; i < stackTrace.size(); i++) {
    found |= (stackTrace[i].find("main", 0) != std::string::npos);
  }
#if defined(ARCH_OS_WINDOWS) && !defined(_DEBUG)
  // Release builds on windows can't get symbolic names.
  found |= !stackTrace.empty();
#endif
  ARCH_AXIOM(found);

  return 0;
}
