//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/bufferArrayRegistry.h"
#include "Hd/bufferArray.h"

PXR_NAMESPACE_OPEN_SCOPE

HdStBufferArrayRegistry::HdStBufferArrayRegistry() : _entries() {}

HdBufferArrayRangeSharedPtr HdStBufferArrayRegistry::AllocateRange(
    HdStAggregationStrategy *strategy,
    TfToken const &role,
    HdBufferSpecVector const &bufferSpecs,
    HdBufferArrayUsageHint usageHint)
{
  HD_TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();

  if (!strategy) {
    TF_CODING_ERROR("Aggregation strategy is set to null");
    return HdBufferArrayRangeSharedPtr();
  }

  // early out for empty specs
  if (bufferSpecs.empty()) {
    return HdBufferArrayRangeSharedPtr();
  }

  // compute an aggregation Id on current aggregation strategy
  HdStAggregationStrategy::AggregationId aggrId = strategy->ComputeAggregationId(bufferSpecs,
                                                                                 usageHint);

  // We use insert to do a find and insert operation
  auto iter = _entries.find(aggrId);
  bool inserted = false;
  if (iter == _entries.end()) {
    // _Entry()'s dtor is very expensive due to std::list member, so avoid
    // constructing one unless we didn't find one.
    std::tie(iter, inserted) = _entries.emplace(aggrId, _Entry());
  }

  _Entry &entry = iter->second;

  if (inserted) {
    // We just created a new entry so make sure it has a buffer in it.
    _InsertNewBufferArray(entry, HdBufferArraySharedPtr(), strategy, role, bufferSpecs, usageHint);
  }
  else {

    // There's a potential multi-thread race condition where
    // another thread has created the entry and is still in the process of
    // adding the first buffer to it, therefore the list could be empty, so
    // wait for it
    _EntryIsNotEmpty pred(entry);
    std::unique_lock<std::mutex> lock(entry.lock);
    entry.emptyCondition.wait(lock, pred);
  }

  HdBufferArrayRangeSharedPtr range = strategy->CreateBufferArrayRange();

  // Try to find where to insert the range.
  // while no new slots can free up during allocate,
  // garbage collection may create empty slots in entries.
  // So we have to go through the list to find slots.
  // Tough as this is Multi-thread, entries maybe added to the list.
  // This doesn't invalidate the iterator, but need to be careful
  // on check end condition.

  _HdBufferArraySharedPtrList::iterator it = entry.bufferArrays.begin();
  int numIterations = 0;
  do {
    HdBufferArraySharedPtr currentArray = *it;

    if (!currentArray->TryAssignRange(range)) {
      _HdBufferArraySharedPtrList::iterator prev = it;
      ++it;

      if (it == entry.bufferArrays.end()) {
        // Reached end of buffer list, so try to insert new buffer
        // Only one thread will win and add the buffer
        // however, by the time we get back multiple buffers may have
        // been added, so rewind iterator.

        _InsertNewBufferArray(entry, currentArray, strategy, role, bufferSpecs, usageHint);
        it = prev;
        ++it;
      }
    }

    if (++numIterations > 100) {
      TF_WARN(
          "Too many iterations in attempting to assign range "
          "containing buffer %s, likely due to invalid buffer array "
          "size.",
          bufferSpecs[0].name.GetText());
      break;
    }
  } while (!range->IsAssigned());

  if (!range->IsAssigned()) {
    return HdBufferArrayRangeSharedPtr();
  }

  return range;
}

void HdStBufferArrayRegistry::ReallocateAll(HdStAggregationStrategy *strategy)
{
  for (auto &entry : _entries) {
    for (auto bufferIt = entry.second.bufferArrays.begin(), e = entry.second.bufferArrays.end();
         bufferIt != e;
         ++bufferIt)
    {

      HdBufferArraySharedPtr const &bufferArray = *bufferIt;
      if (!bufferArray->NeedsReallocation())
        continue;

      // in case of over aggregation, split the buffer

      bufferArray->RemoveUnusedRanges();

      size_t maxTotalElements = bufferArray->GetMaxNumElements();
      size_t numTotalElements = 0;

      size_t rangeCount = bufferArray->GetRangeCount();
      std::vector<HdBufferArrayRangeSharedPtr> ranges;
      ranges.reserve(rangeCount);

      for (size_t rangeIdx = 0; rangeIdx < rangeCount; ++rangeIdx) {
        HdBufferArrayRangeSharedPtr range = bufferArray->GetRange(rangeIdx).lock();

        if (!range)
          continue;  // shouldn't exist

        size_t numElements = range->GetNumElements();

        if (numElements > maxTotalElements) {
          // Issue a warning and reset number of elements in the BAR.
          TF_WARN(
              "Number of elements in the buffer array range "
              "(0x%lx) is _larger_ than the maximum number of "
              "elements in the buffer array (0x%lx). 0x%lx bytes "
              "of data will be skipped.",
              numElements,
              maxTotalElements,
              numElements - maxTotalElements);

          range->Resize(maxTotalElements);
        }

        // over aggregation check of non-uniform buffer
        if (numTotalElements + numElements > maxTotalElements) {
          // create new BufferArray with same specification
          HdBufferSpecVector bufferSpecs = strategy->GetBufferSpecs(bufferArray);
          HdBufferArrayUsageHint usageHint = bufferArray->GetUsageHint();

          HdBufferArraySharedPtr newBufferArray = strategy->CreateBufferArray(
              bufferArray->GetRole(), bufferSpecs, usageHint);
          newBufferArray->Reallocate(ranges, bufferArray);

          // bufferArrays is std::list
          entry.second.bufferArrays.insert(bufferIt, newBufferArray);

          numTotalElements = 0;
          ranges.clear();
        }

        numTotalElements += numElements;
        ranges.push_back(range);
      }

      bufferArray->Reallocate(ranges, bufferArray);
    }
  }
}

void HdStBufferArrayRegistry::GarbageCollect()
{
  _BufferArrayIndex::iterator entryIt = _entries.begin();

  while (entryIt != _entries.end()) {
    _Entry &entry = entryIt->second;

    _HdBufferArraySharedPtrList::iterator bufferIt = entry.bufferArrays.begin();

    while (bufferIt != entry.bufferArrays.end()) {
      if ((*bufferIt)->GarbageCollect()) {
        bufferIt = entry.bufferArrays.erase(bufferIt);
      }
      else {
        ++bufferIt;
      }
    }

    if (entry.bufferArrays.empty()) {
      entryIt = _entries.unsafe_erase(entryIt);
    }
    else {
      ++entryIt;
    }
  }
}

size_t HdStBufferArrayRegistry::GetResourceAllocation(HdStAggregationStrategy *strategy,
                                                      VtDictionary &result) const
{
  size_t gpuMemoryUsed = 0;
  TF_FOR_ALL(entryIt, _entries)
  {
    TF_FOR_ALL(bufferIt, entryIt->second.bufferArrays)
    {
      gpuMemoryUsed += strategy->GetResourceAllocation(*bufferIt, result);
    }
  }

  return gpuMemoryUsed;
}

void HdStBufferArrayRegistry::_InsertNewBufferArray(_Entry &entry,
                                                    const HdBufferArraySharedPtr &expectedTail,
                                                    HdStAggregationStrategy *strategy,
                                                    TfToken const &role,
                                                    HdBufferSpecVector const &bufferSpecs,
                                                    HdBufferArrayUsageHint usageHint)
{
  {
    std::lock_guard<std::mutex> lock(entry.lock);

    // Check state of list, still matches what is expected.
    // If not another thread won and inserted a new buffer.
    if (!entry.bufferArrays.empty()) {
      if (entry.bufferArrays.back() != expectedTail) {
        return;  // Lock_guard will unlock entry
      }
    }
    else {
      // This shouldn't ever happen, because where did the expected tail
      // come from if it wasn't in the list???
      TF_VERIFY(!expectedTail);
    }

    entry.bufferArrays.emplace_back(strategy->CreateBufferArray(role, bufferSpecs, usageHint));
  }  // Lock_guard will unlock

  // Notify any threads waiting on an empty list (unlock must happen first).
  entry.emptyCondition.notify_all();
}

HD_API
std::ostream &operator<<(std::ostream &out, const HdStBufferArrayRegistry &self)
{
  out << "HdStBufferArrayRegistry " << &self << " :\n";
  TF_FOR_ALL(entryIt, self._entries)
  {
    out << "  _Entry aggrId = " << entryIt->first << ": \n";

    size_t bufferNum = 0;
    TF_FOR_ALL(bufferIt, entryIt->second.bufferArrays)
    {
      out << "HdBufferArray " << bufferNum << "\n";
      bufferNum++;
    }
  }

  return out;
}

PXR_NAMESPACE_CLOSE_SCOPE
