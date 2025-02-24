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
#include "pxr/base/tf/mallocTag.h"
#include "Arch/defines.h"
#include "Arch/mallocHook.h"
#include "pxr/base/tf/diagnosticLite.h"
#include "pxr/base/tf/regTest.h"
#include "pxr/pxr.h"

#include <mutex>
#include <thread>
#include <vector>

PXR_NAMESPACE_USING_DIRECTIVE

// The TfMallocTag code depends upon the Linux memory allocator, ptmalloc3.
// Turning this test off for any other platforms for now.
#if defined(ARCH_OS_LINUX)

using std::string;
using std::vector;

static vector<void *> _requests;
std::mutex _mutex;
int _total = 0;
int _maxTotal = 0;

static void MyMalloc(size_t n)
{
  void *ptr = malloc(n);
  std::lock_guard<std::mutex> lock(_mutex);
  _requests.push_back(ptr);
  _total += n;
  if (_total > _maxTotal) {
    _maxTotal = _total;
  }
}

static void FreeAll()
{
  for (size_t i = 0; i < _requests.size(); i++)
    free(::_requests[i]);
  _requests.clear();
  _total = 0;
}

static void FreeTaskNoTag()
{
  MyMalloc(100000);
}

static void FreeTaskWithTag()
{
  TfAutoMallocTag noname("freeTaskWithTag");
  MyMalloc(100000);
}

static void RegularTask(bool tag, int n)
{
  if (tag) {
    TfAutoMallocTag noname("threadTag");
    MyMalloc(n);
  }
  else {
    MyMalloc(n);
  }
}

static int GetBytesForCallSite(const char *name, bool skipRepeated = true)
{
  TfMallocTag::CallTree ct;
  TfMallocTag::GetCallTree(&ct, skipRepeated);

  for (size_t i = 0; i < ct.callSites.size(); i++)
    if (ct.callSites[i].name == name)
      return ct.callSites[i].nBytes;

  return -1;
}

static bool CloseEnough(int64_t a1, int64_t a2)
{
  /*
   * Account for various small allocations during this test that can get
   * billed to various sites.  We use fairly large allocations so we can drown
   * out the small stuff.
   */
  if (a1 < 2048 && a2 < 2048)
    return true;

  if (a1 >= (.95 * a2) && a1 <= (1.05 * a2)) {
    return true;
  }
  else {
    fprintf(stderr, "%zd not close to %zd\n", a1, a2);
    return false;
  }
}

static bool MemCheck()
{
  int64_t m = _total, current = TfMallocTag::GetTotalBytes();
  bool ok = CloseEnough(m, current);

  printf(
      "Expected about %zd, actual is %zd: %s\n", m, current, ok ? "[close enough]" : "[not good]");

  bool maxOk = CloseEnough(::_maxTotal, TfMallocTag::GetMaxTotalBytes());
  printf("Expected max of about %zd, actual is %zd: %s\n",
         m,
         current,
         maxOk ? "[close enough]" : "[not good]");

  return ok && maxOk;
}

static void TestFreeThread()
{
  TfAutoMallocTag noname("site3");

  std::thread t(FreeTaskNoTag);
  t.join();

  printf("bytesForSite[site3] = %d\n", GetBytesForCallSite("site3"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site3"), 0));
  FreeAll();
}

static void TestFreeThreadWithTag()
{
  TfAutoMallocTag noname("site4");

  std::thread t(FreeTaskWithTag);
  t.join();

  printf("bytesForSite[freeTaskWithTag] = %d\n", GetBytesForCallSite("freeTaskWithTag"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("freeTaskWithTag"), 100000));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site4"), 0));
  FreeAll();

  printf("bytesForSite[freeTaskWithTag] = %d\n", GetBytesForCallSite("freeTaskWithTag"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("freeTaskWithTag"), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site4"), 0));
}

static void TestRegularTask()
{
  // XXX: Picking up tags from the thread that spawned another thread has
  // never worked, since we don't have a way to "copy" this thread's tag stack
  // to the thread we create.  We would have to add a new feature for that, so
  // disabling this test for now.
  {
    TfAutoMallocTag noname("name");
    std::thread t(RegularTask, false, 100000);
    t.join();
  }

  printf("bytesForSite[%s] = %d\n", "name", GetBytesForCallSite("name"));
  // TF_AXIOM(CloseEnough(GetBytesForCallSite("name"), 100000));
  FreeAll();

  printf("bytesForSite[%s] = %d\n", "name", GetBytesForCallSite("name"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("name"), 0));
}

static void TestRegularTaskWithTag()
{
  // XXX: Picking up tags from the thread that spawned another thread has
  // never worked, since we don't have a way to "copy" this thread's tag stack
  // to the thread we create.  We would have to add a new feature for that, so
  // disabling this test for now.
  {
    TfAutoMallocTag noname("site2");
    std::thread t(RegularTask, true, 100000);
    t.join();
  }

  printf("bytesForSite[%s] = %d\n", "threadTag", GetBytesForCallSite("threadTag"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("threadTag"), 100000));
  // TF_AXIOM(CloseEnough(GetBytesForCallSite("site2"), 0));
  FreeAll();

  printf("bytesForSite[%s] = %d\n", "threadTag", GetBytesForCallSite("threadTag"));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("threadTag"), 0));
}

static void TestRepeated()
{
  TfAutoMallocTag noname1("site1");
  MyMalloc(100000);
  TfAutoMallocTag noname2("site2");
  MyMalloc(200000);
  TfAutoMallocTag noname3("site1");
  MyMalloc(100000);
  TfAutoMallocTag noname4("site3");
  MyMalloc(100000);

  TF_AXIOM(CloseEnough(GetBytesForCallSite("site2", false), 200000));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site2", true), 300000));

  TF_AXIOM(CloseEnough(GetBytesForCallSite("site1", true), 100000));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site1", false), 200000));

  TF_AXIOM(CloseEnough(GetBytesForCallSite("site3", true), 100000));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("site3", false), 100000));

  FreeAll();
}

static void TestMultiTags()
{
  TfAutoMallocTag tags1("multi1", "multi2", "multi3", "multi4");
  MyMalloc(100000);
  TfAutoMallocTag tags2("multi5", "multi6");
  MyMalloc(100000);

  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi1", false), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi2", false), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi3", false), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi4", false), 100000));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi5", false), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("multi6", false), 100000));

  FreeAll();
}

static bool Test_TfMallocTag()
{
  _requests.reserve(1024);
  TF_AXIOM(TfMallocTag::GetTotalBytes() == 0);
  TF_AXIOM(MemCheck());

  // this won't show up in the accounting
  void *mem1 = malloc(100000);

  string errMsg;
  if (!TfMallocTag::Initialize(&errMsg)) {
    fprintf(stderr, "Unable to initialize malloc tags: %s\n", errMsg.c_str());
    fprintf(stderr, "Skipping test\n");
    return true;
  }

  TfAutoMallocTag topTag("myRoot");

  // and this free shouldn't either...
  free(mem1);
  printf("total: %zd\n", TfMallocTag::GetTotalBytes());
  TF_AXIOM(TfMallocTag::GetTotalBytes() == 0);

  MyMalloc(300000);
  TF_AXIOM(MemCheck());

  FreeAll();
  TF_AXIOM(MemCheck());

  TfMallocTag::Push(string("manualTag"));
  MyMalloc(100000);
  TF_AXIOM(CloseEnough(GetBytesForCallSite("manualTag"), 100000));
  TfMallocTag::Push("manualTag2");
  MyMalloc(100000);
  TF_AXIOM(CloseEnough(GetBytesForCallSite("manualTag"), 100000));
  TfMallocTag::Pop();
  TfMallocTag::Pop();
  TF_AXIOM(CloseEnough(GetBytesForCallSite("manualTag"), 100000));
  FreeAll();
  TF_AXIOM(CloseEnough(GetBytesForCallSite("manualTag"), 0));
  TF_AXIOM(CloseEnough(GetBytesForCallSite("manualTag2"), 0));

  FreeAll();
  TF_AXIOM(MemCheck());

  TestRegularTask();
  TF_AXIOM(MemCheck());

  TestRegularTaskWithTag();
  TF_AXIOM(MemCheck());

  TestFreeThread();
  TF_AXIOM(MemCheck());

  TestFreeThreadWithTag();
  TF_AXIOM(MemCheck());

  FreeAll();
  TF_AXIOM(MemCheck());

  TestRepeated();
  TF_AXIOM(MemCheck());

  TestMultiTags();
  TF_AXIOM(MemCheck());

  return true;
}

TF_ADD_REGTEST(TfMallocTag);

#endif
