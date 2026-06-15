//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/pyCallContext.h"
#include "Tf/callContext.h"
#include "Tf/stringUtils.h"

#include <OneTBB/tbb/spin_mutex.h>

#include <set>
#include <string>

#if PXR_PYTHON_SUPPORT_ENABLED
using namespace std;

namespace {
    struct _Cache {
        tbb::spin_mutex lock;
        set<string> data;
    };
}


PXR_NAMESPACE_OPEN_SCOPE

/*
 * TfCallContext's contain const char*'s which are assumed to be program literals.
 * That assumption fails badly when it comes to python.
 */
TfCallContext
Tf_PythonCallContext(std::string fileName,
                     std::string moduleName,
                     std::string functionName,
                     size_t line)
{
    static _Cache cache;

    string fullName;
    if (moduleName.empty()) {
        fullName = functionName;
    } else if (functionName.empty()) {
        fullName = moduleName;
    } else {
        fullName = TfStringPrintf("%s.%s", moduleName.c_str(),
                                  functionName.c_str());
    }

    if (fullName.empty()) {
        return TfCallContext{};
    }

    tbb::spin_mutex::scoped_lock lock(cache.lock);
    char const* prettyFunctionPtr = cache.data.insert(fullName).first->c_str();
    char const* fileNamePtr = cache.data.insert(fileName).first->c_str();

    return TfCallContext(fileNamePtr, prettyFunctionPtr, line, prettyFunctionPtr);
}

PXR_NAMESPACE_CLOSE_SCOPE 
#endif // PXR_PYTHON_SUPPORT_ENABLED