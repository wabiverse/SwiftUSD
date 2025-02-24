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

#include "pxr/base/tf/denseHashMap.h"
#include "pxr/base/tf/diagnosticLite.h"
#include "pxr/base/tf/hash.h"
#include "pxr/base/tf/regTest.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/pxr.h"

#include <cstdio>

PXR_NAMESPACE_USING_DIRECTIVE

// Test equality operator.
struct TestTf_DenseHashMapModuloEqual {
  TestTf_DenseHashMapModuloEqual(size_t mod = 1) : _mod(mod) {}

  bool operator()(const size_t &x, const size_t &y) const
  {
    return x % _mod == y % _mod;
  }

  size_t _mod;
};

static void Run()
{
  typedef TfDenseHashMap<size_t, std::string, TfHash> _Map;
  _Map _map;

  // Make sure size expectations are ok.
  // Due to empty base optimization, because both HashFn and EqualKey are
  // 0-size, should only hold a vector + pointer
  // (Note that on windows, debug mode will change sizeof vector)
  TF_AXIOM(sizeof(_Map) == sizeof(std::vector<_Map::value_type>) + sizeof(void *));

  // Insert a bunch of numbers in order.
  printf("inserting numbers to 10000\n");
  for (size_t i = 1; i <= 10000; ++i) {
    _map[i] = TfStringify(i);
    TF_AXIOM(_map.size() == i);
    TF_AXIOM(_map.find(i) != _map.end());
    TF_AXIOM(_map.count(i) == 1);
  }

  TF_AXIOM(!_map.empty());
  TF_AXIOM(_map.size() == 10000);

  printf("Exercise assignment operator and swap.\n");
  _Map newMap;

  newMap = _map;
  TF_AXIOM(newMap.size() == _map.size());
  newMap[9999999] = "full";
  TF_AXIOM(newMap.size() == _map.size() + 1);

  newMap.swap(_map);
  TF_AXIOM(newMap.size() + 1 == _map.size());
  newMap.swap(_map);
  TF_AXIOM(newMap.size() == _map.size() + 1);

  printf("checking containment\n");
  for (size_t i = 1; i <= 10000; ++i)
    TF_AXIOM(_map.count(i) == 1);

  printf("checking correct mapping\n");
  for (size_t i = 1; i <= 10000; ++i)
    TF_AXIOM(_map[i] == TfStringify(i));

  // Remove some stuff.
  printf("erasing 8000 elements\n");
  for (size_t i = 1000; i < 9000; ++i)
    TF_AXIOM(_map.erase(i) == 1);

  // Attempt to remove some stuff again.
  printf("erasing 8000 elements\n");
  for (size_t i = 1000; i < 9000; ++i)
    TF_AXIOM(_map.erase(i) == 0);

  TF_AXIOM(!_map.empty());
  TF_AXIOM(_map.size() == 2000);

  printf("checking containment\n");
  for (size_t i = 1; i <= 10000; ++i) {
    if (i < 1000 || i >= 9000)
      TF_AXIOM(_map.count(i) == 1);
    else
      TF_AXIOM(_map.count(i) == 0);
  }

  printf("testing shrink to fit\n");
  _map.shrink_to_fit();

  TF_AXIOM(!_map.empty());
  TF_AXIOM(_map.size() == 2000);

  printf("checking containment\n");
  for (size_t i = 1; i <= 10000; ++i) {
    if (i < 1000 || i >= 9000)
      TF_AXIOM(_map.count(i) == 1);
    else
      TF_AXIOM(_map.count(i) == 0);
  }

  // Put it back.
  printf("reinserting 8000 elements\n");
  for (size_t i = 1000; i < 9000; ++i)
    _map[i] = TfStringify(i);

  TF_AXIOM(!_map.empty());
  TF_AXIOM(_map.size() == 10000);

  printf("checking containment\n");
  for (size_t i = 1; i <= 10000; ++i)
    TF_AXIOM(_map.count(i) == 1);

  printf("checking correct mapping\n");
  for (size_t i = 1; i <= 10000; ++i)
    TF_AXIOM(_map[i] == TfStringify(i));

  // Remove some stuff.
  printf("erasing 8000 elements\n");
  for (size_t i = 1000; i < 9000; ++i)
    _map.erase(i);

  TF_AXIOM(!_map.empty());
  TF_AXIOM(_map.size() == 2000);

  printf("checking containment\n");
  for (size_t i = 1; i <= 10000; ++i) {
    TF_AXIOM(_map.count(i) == (i < 1000 || i >= 9000));
  }

  // iterate
  printf("iterating\n");
  size_t count = 0;
  for (_Map::iterator i = _map.begin(); i != _map.end(); ++i, ++count) {
    TF_AXIOM(TfStringify(i->first) == i->second);
    TF_AXIOM(i->first < 1000 || i->first >= 9000);
  }
  TF_AXIOM(count == 2000);

  // iterate
  printf("const iterating\n");
  count = 0;
  for (_Map::const_iterator i = _map.begin(); i != _map.end(); ++i, ++count) {
    TF_AXIOM(TfStringify(i->first) == i->second);
    TF_AXIOM(i->first < 1000 || i->first >= 9000);
  }
  TF_AXIOM(count == 2000);

  printf("remove all but the first two elements using erase(range)...\n");
  _Map::iterator i0 = _map.begin();
  size_t keys[2];
  keys[0] = i0++->first;
  keys[1] = i0++->first;
  _map.erase(i0, _map.end());
  TF_AXIOM(_map.size() == 2);
  i0 = _map.begin();
  TF_AXIOM(i0++->first == keys[0]);
  TF_AXIOM(i0++->first == keys[1]);

  printf("inserting using insert(range)\n");
  std::vector<std::pair<int, std::string>> morekeys;
  for (size_t i = 100; i < 200; i++)
    morekeys.push_back(std::make_pair(i, "hello"));
  _map.insert(morekeys.begin(), morekeys.end());
  TF_AXIOM(_map.size() == 102);
  for (size_t i = 100; i < 200; i++)
    TF_AXIOM(_map[i] == "hello");

  // copying and comparing maps.
  printf("copying and comparing...\n");
  _Map other(_map);
  TF_AXIOM(other.size() == _map.size());
  TF_AXIOM(other == _map);
  other[4711] = "different_now";
  TF_AXIOM(other.size() != _map.size());
  TF_AXIOM(other != _map);

  // clear it.
  printf("clearing\n");
  _map.clear();
  TF_AXIOM(_map.empty());
  TF_AXIOM(_map.size() == 0);

  printf("shrinking\n");
  _map.shrink_to_fit();
  TF_AXIOM(_map.empty());
  TF_AXIOM(_map.size() == 0);

  printf("exerise initialize_list ctor / assignment.\n");
  _Map init{{100, "this"}, {110, "can"}, {120, "be"}, {130, "const"}};
  TF_AXIOM(init.size() == 4);
  TF_AXIOM(init[100] == "this");
  TF_AXIOM(init[110] == "can");
  TF_AXIOM(init[120] == "be");
  TF_AXIOM(init[130] == "const");

  init = {
      {2717, "dl"},
      {2129, "eg"},
  };

  TF_AXIOM(init.size() == 2);
  TF_AXIOM(init[2717] == "dl");
  TF_AXIOM(init[2129] == "eg");

  printf("\nTesting TfDenseHashMap using an EqualKey.\n");

  typedef TfDenseHashMap<size_t, std::string, TfHash, TestTf_DenseHashMapModuloEqual, 128> _Map2;

  _Map2 _map2(TfHash(), TestTf_DenseHashMapModuloEqual(2));

  // Make sure size expectations are ok.
  TF_AXIOM(sizeof(TestTf_DenseHashMapModuloEqual) > 0);
  TF_AXIOM(sizeof(_Map2) == sizeof(std::vector<_Map2::value_type>) + sizeof(void *) +
                                sizeof(TestTf_DenseHashMapModuloEqual));

  // Insert a bunch of numbers in order.
  printf("inserting numbers to 10000\n");
  for (size_t i = 1; i <= 10000; ++i) {
    _map2[i] = TfStringify(i);
  }

  printf("expecting only two elements\n");
  TF_AXIOM(!_map2.empty());
  TF_AXIOM(_map2.size() == 2);
}

static void TestMoveOperations()
{
  using Map = TfDenseHashMap<int, std::string, TfHash>;

  printf("\nTesting TfDenseHashMap move constructor & assignment...\n");

  // Move some small (without hash index) maps

  // Move construction of empty map from empty map
  Map emptyMap1(Map{});
  TF_AXIOM(emptyMap1.empty());

  // Move assignment of empty map into empty map
  Map emptyMap2;
  emptyMap2 = Map();
  TF_AXIOM(emptyMap2.empty());

  Map smallMap1;
  smallMap1.insert({1, "one"});
  smallMap1.insert({2, "two"});

  // Move construction of small map
  Map smallMap2(std::move(smallMap1));
  TF_AXIOM(smallMap2.size() == 2);
  TF_AXIOM(smallMap2.find(1) != smallMap2.end());
  TF_AXIOM(smallMap2.find(1)->second == "one");
  TF_AXIOM(smallMap2.find(2) != smallMap2.end());
  TF_AXIOM(smallMap2.find(2)->second == "two");

  // Move assignment of small map into small map
  Map smallMap3;
  smallMap3.insert({0, "zero"});
  TF_AXIOM(smallMap3.size() == 1);
  smallMap3 = std::move(smallMap2);
  TF_AXIOM(smallMap3.size() == 2);
  TF_AXIOM(smallMap3.find(1) != smallMap3.end());
  TF_AXIOM(smallMap3.find(1)->second == "one");
  TF_AXIOM(smallMap3.find(2) != smallMap3.end());
  TF_AXIOM(smallMap3.find(2)->second == "two");

  // Move assignment of small map into empty map
  Map smallMap4;
  smallMap4 = std::move(smallMap3);
  TF_AXIOM(smallMap4.size() == 2);
  TF_AXIOM(smallMap4.find(1) != smallMap4.end());
  TF_AXIOM(smallMap4.find(1)->second == "one");
  TF_AXIOM(smallMap4.find(2) != smallMap4.end());
  TF_AXIOM(smallMap4.find(2)->second == "two");

  // Move assignment of an empty map into a small map
  Map emptyMap3;
  smallMap4 = std::move(emptyMap3);
  TF_AXIOM(smallMap4.empty());

  // Move some large (with hash index) maps

  Map largeMap1;
  for (int i = 0; i < 10000; ++i) {
    largeMap1.insert({i, TfStringify(i)});
  }
  TF_AXIOM(largeMap1.size() == 10000);

  // Move construction of large map
  Map largeMap2(std::move(largeMap1));
  TF_AXIOM(largeMap2.size() == 10000);
  TF_AXIOM(largeMap2.find(2319) != largeMap2.end());
  TF_AXIOM(largeMap2.find(2319)->second == "2319");

  // Move assignment of large map into large map
  Map largeMap3;
  for (int i = 10000; i < 20000; ++i) {
    largeMap3.insert({i, TfStringify(i)});
  }
  TF_AXIOM(largeMap3.size() == 10000);
  largeMap3 = std::move(largeMap2);
  TF_AXIOM(largeMap3.size() == 10000);
  TF_AXIOM(largeMap3.find(2319) != largeMap3.end());
  TF_AXIOM(largeMap3.find(2319)->second == "2319");

  // Move assignment of large map into empty map
  Map largeMap4;
  largeMap4 = std::move(largeMap3);
  TF_AXIOM(largeMap4.size() == 10000);
  TF_AXIOM(largeMap4.find(2319) != largeMap4.end());
  TF_AXIOM(largeMap4.find(2319)->second == "2319");

  // Move assignment of an empty map into a large map
  Map emptyMap4;
  largeMap4 = std::move(emptyMap4);
  TF_AXIOM(largeMap4.empty());

  // Move assignment of a small map into a large map
  Map smallMap5;
  smallMap5.insert({3, "three"});
  smallMap5.insert({4, "four"});
  Map largeMap5;
  for (int i = 20000; i < 30000; ++i) {
    largeMap5.insert({i, TfStringify(i)});
  }
  largeMap5 = std::move(smallMap5);
  TF_AXIOM(largeMap5.size() == 2);
  TF_AXIOM(largeMap5.find(3) != largeMap5.end());
  TF_AXIOM(largeMap5.find(3)->second == "three");
  TF_AXIOM(largeMap5.find(4) != largeMap5.end());
  TF_AXIOM(largeMap5.find(4)->second == "four");

  // Move assignment of a large map into a small map
  Map smallMap6;
  smallMap6.insert({5, "five"});
  smallMap6.insert({6, "six"});
  Map largeMap6;
  for (int i = 30000; i < 40000; ++i) {
    largeMap6.insert({i, TfStringify(i)});
  }
  smallMap6 = std::move(largeMap6);
  TF_AXIOM(smallMap6.size() == 10000);
  TF_AXIOM(smallMap6.find(35000) != smallMap6.end());
  TF_AXIOM(smallMap6.find(35000)->second == "35000");
}

static bool Test_TfDenseHashMap()
{
  Run();
  TestMoveOperations();
  return true;
}

TF_ADD_REGTEST(TfDenseHashMap);
