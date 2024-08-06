//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_BASE_TRACE_COLLECTION_H
#define PXR_BASE_TRACE_COLLECTION_H

#include "pxr/pxrns.h"

#include "Trace/api.h"
#include "Trace/event.h"
#include "Trace/eventList.h"
#include "Trace/threads.h"

#include "Tf/mallocTag.h"

#include <map>
#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

///////////////////////////////////////////////////////////////////////////////
///
/// \class TraceCollection
///
/// This class owns lists of TraceEvent instances per thread, and allows
/// read access to them.
///
class TraceCollection {
 public:
  TF_MALLOC_TAG_NEW("Trace", "TraceCollection");

  using This = TraceCollection;

  using EventList = TraceEventList;
  using EventListPtr = std::unique_ptr<EventList>;

  /// Constructor.
  TraceCollection() = default;

  /// Move constructor.
  TraceCollection(TraceCollection &&) = default;

  /// Move assignment operator.
  TraceCollection &operator=(TraceCollection &&) = default;

  // Collections should not be copied because TraceEvents contain
  // pointers to elements in the Key cache.
  TraceCollection(const TraceCollection &) = delete;
  TraceCollection &operator=(const TraceCollection &) = delete;

  /// Appends \p events to the collection. The collection will
  /// take ownership of the data.
  TRACE_API void AddToCollection(const TraceThreadId &id, EventListPtr &&events);

  ////////////////////////////////////////////////////////////////////////
  ///
  /// \class Visitor
  ///
  /// This interface provides a way to access data a TraceCollection.
  ///
  class Visitor {
   public:
    /// Destructor
    TRACE_API virtual ~Visitor();

    /// Called at the beginning of an iteration.
    virtual void OnBeginCollection() = 0;

    /// Called at the end of an iteration.
    virtual void OnEndCollection() = 0;

    /// Called before the first event of from the thread with
    /// \p threadId is encountered.
    virtual void OnBeginThread(const TraceThreadId &threadId) = 0;

    /// Called after the last event of from the thread with
    /// \p threadId is encountered.
    virtual void OnEndThread(const TraceThreadId &threadId) = 0;

    /// Called before an event with \p categoryId is visited. If the
    /// return value is false, the event will be visited.
    virtual bool AcceptsCategory(TraceCategoryId categoryId) = 0;

    /// Called for every event \p event with \p key on thread
    /// \p threadId if AcceptsCategory returns true.
    virtual void OnEvent(const TraceThreadId &threadId,
                         const TfToken &key,
                         const TraceEvent &event) = 0;
  };

  /// Forward iterates over the events of the collection and calls the
  /// \p visitor callbacks.
  TRACE_API void Iterate(Visitor &visitor) const;

  /// Reverse iterates over the events of the collection and calls the
  /// \p visitor callbacks.
  TRACE_API void ReverseIterate(Visitor &visitor) const;

 private:
  using KeyTokenCache = std::unordered_map<TraceKey, TfToken, TraceKey::HashFunctor>;

  /// Iterate through threads, then choose either forward or reverse
  /// iteration for the events in the threads
  void _Iterate(Visitor &visitor, bool doReverse) const;

  // Iterate through events in either forward or reverse order, depending on
  // the templated arguments
  template<class I>
  void _IterateEvents(Visitor &, KeyTokenCache &, const TraceThreadId &, I, I) const;

  using EventTable = std::map<TraceThreadId, EventListPtr>;

  EventTable _eventsPerThread;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TRACE_COLLECTION_H
