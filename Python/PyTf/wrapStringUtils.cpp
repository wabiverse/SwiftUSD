//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/stringUtils.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/extract.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/handle.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/overloads.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/type_id.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "Tf/pyResultConversions.h"

#include <string>
#include <limits>

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static int DictionaryStrcmp(string const &l, string const &r) {
    TfDictionaryLessThan lt;
    return lt(l, r) ? -1 : (lt(r, l) ? 1 : 0);
}

static unsigned long
_StringToULong(char const *str) {
    bool outOfRange = false;
    unsigned long result = TfStringToULong(str, &outOfRange);
    if (outOfRange)
        TfPyThrowValueError("Out of range.");
    return result;
}

static long
_StringToLong(char const *str) {
    bool outOfRange = false;
    long result = TfStringToLong(str, &outOfRange);
    if (outOfRange)
        TfPyThrowValueError("Out of range.");
    return result;
}

static unsigned long
_GetULongMax() {
    return std::numeric_limits<unsigned long>::max();
}

static long
_GetLongMax() {
    return std::numeric_limits<long>::max();
}

static long
_GetLongMin() {
    return std::numeric_limits<long>::min();
}

} // anonymous namespace 

void wrapStringUtils() {
    def("StringSplit", TfStringSplit, return_value_policy<TfPySequenceToList>());
    def("DictionaryStrcmp", DictionaryStrcmp);

    def("IsValidIdentifier", TfIsValidIdentifier);
    def("MakeValidIdentifier", TfMakeValidIdentifier);

    def("StringToDouble",
        (double (*)(const std::string &))TfStringToDouble);
    def("StringToLong", _StringToLong);
    def("StringToULong", _StringToULong);

    def("_GetULongMax", _GetULongMax);
    def("_GetLongMax", _GetLongMax);
    def("_GetLongMin", _GetLongMin);
}
