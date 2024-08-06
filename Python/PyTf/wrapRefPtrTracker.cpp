//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file wrapRefPtrTracker.cpp

#include "pxr/pxrns.h"

#include "Tf/pySingleton.h"
#include "Tf/refPtr.h"
#include "Tf/refPtrTracker.h"
#include "Tf/weakPtr.h"

#include <boost/python/class.hpp>
#include <sstream>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static std::string _ReportAllWatchedCounts(TfRefPtrTracker &tracker)
{
  std::ostringstream s;
  tracker.ReportAllWatchedCounts(s);
  return s.str();
}

static std::string _ReportAllTraces(TfRefPtrTracker &tracker)
{
  std::ostringstream s;
  tracker.ReportAllTraces(s);
  return s.str();
}

static std::string _ReportTracesForWatched(TfRefPtrTracker &tracker, uintptr_t ptr)
{
  std::ostringstream s;
  tracker.ReportTracesForWatched(s, (TfRefBase *)ptr);
  return s.str();
}

}  // anonymous namespace

void wrapRefPtrTracker()
{
  typedef TfRefPtrTracker This;
  typedef TfWeakPtr<TfRefPtrTracker> ThisPtr;

  class_<This, ThisPtr, boost::noncopyable>("RefPtrTracker", no_init)
      .def(TfPySingleton())

      .def("GetAllWatchedCountsReport", _ReportAllWatchedCounts)
      .def("GetAllTracesReport", _ReportAllTraces)
      .def("GetTracesReportForWatched", _ReportTracesForWatched);
}
