//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// Do not include pyModule.h or we'd need an implementation of WrapModule().
// #include "Tf/pyModule.h"

#include "Arch/defines.h"
#include "pxr/pxrns.h"

#include "Tf/error.h"
#include "Tf/errorMark.h"
#include "Tf/hash.h"
#include "Tf/hashset.h"
#include "Tf/mallocTag.h"
#include "Tf/pyError.h"
#include "Tf/pyModuleNotice.h"
#include "Tf/pyTracing.h"
#include "Tf/pyWrapContext.h"
#include "Tf/scriptModuleLoader.h"
#include "Tf/stopwatch.h"
#include "Tf/stringUtils.h"
#include "Tf/token.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#include <boost/python/dict.hpp>
#include <boost/python/docstring_options.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>
#include <boost/python/object/function.hpp>
#include <boost/python/raw_function.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/tuple.hpp>

#include <string>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_OPEN_SCOPE

class Tf_ModuleProcessor {
 public:
  typedef Tf_ModuleProcessor This;

  using WalkCallbackFn = bool (This::*)(char const *, object const &, object const &);

  inline bool IsBoostPythonFunc(object const &obj)
  {
    if (!_cachedBPFuncType) {
      handle<> typeStr(PyObject_Str((PyObject *)obj.ptr()->ob_type));
      if (strstr(PyUnicode_AsUTF8(typeStr.get()), "Boost.Python.function")) {
        _cachedBPFuncType = (PyObject *)obj.ptr()->ob_type;
        return true;
      }
      return false;
    }
    return (PyObject *)obj.ptr()->ob_type == _cachedBPFuncType;
  }

  inline bool IsBoostPythonClass(object const &obj)
  {
    if (!_cachedBPClassType) {
      handle<> typeStr(PyObject_Str((PyObject *)obj.ptr()->ob_type));
      if (strstr(PyUnicode_AsUTF8(typeStr.get()), "Boost.Python.class")) {
        _cachedBPClassType = (PyObject *)obj.ptr()->ob_type;
        return true;
      }
      return false;
    }
    return (PyObject *)obj.ptr()->ob_type == _cachedBPClassType;
  }

  inline bool IsProperty(object const &obj)
  {
    return PyObject_TypeCheck(obj.ptr(), &PyProperty_Type);
  }

  inline bool IsStaticMethod(object const &obj)
  {
    return PyObject_TypeCheck(obj.ptr(), &PyStaticMethod_Type);
  }

  inline bool IsClassMethod(object const &obj)
  {
    return PyObject_TypeCheck(obj.ptr(), &PyClassMethod_Type);
  }

 private:
  void _WalkModule(object const &obj,
                   WalkCallbackFn callback,
                   TfHashSet<PyObject *, TfHash> *visitedObjs)
  {
    if (PyObject_HasAttrString(obj.ptr(), "__dict__")) {
      // In python 3 dict.items() returns a proxy view object, not a list.
      // boost::python::extract<list> fails on these views, and raises:
      //
      // TypeError: Expecting an object of type list; got an object of type
      // dict_items instead
      //
      // A workaround is to use the boost::python::list constructor
      object items_view = obj.attr("__dict__").attr("items")();
      list items(items_view);
      size_t lenItems = len(items);
      for (size_t i = 0; i < lenItems; ++i) {
        object value = items[i][1];
        if (!visitedObjs->count(value.ptr())) {
          const std::string name = PyUnicode_AsUTF8(object(items[i][0]).ptr());
          bool keepGoing = (this->*callback)(name.c_str(), obj, value);
          visitedObjs->insert(value.ptr());
          if (IsBoostPythonClass(value) && keepGoing) {
            _WalkModule(value, callback, visitedObjs);
          }
        }
      }
    }
  }

 public:
  void WalkModule(object const &obj, WalkCallbackFn callback)
  {
    TfHashSet<PyObject *, TfHash> visited;
    _WalkModule(obj, callback, &visited);
  }

  class _InvokeWithErrorHandling {
   public:
    _InvokeWithErrorHandling(object const &fn, string const &funcName, string const &fileName)
        : _fn(fn), _funcName(funcName), _fileName(fileName)
    {
    }

    PyObject *operator()(PyObject *args, PyObject *kw) const
    {

      // Fabricate a python tracing event to record the python -> c++ ->
      // python transition.
      TfPyTraceInfo info;
      info.arg = NULL;
      info.funcName = _funcName.c_str();
      info.fileName = _fileName.c_str();
      info.funcLine = 0;

      // Fabricate the call tracing event.
      info.what = PyTrace_CALL;
      Tf_PyFabricateTraceEvent(info);

      // Make an error mark.
      TfErrorMark m;

      // Call the function.
      PyObject *ret = PyObject_Call(_fn.ptr(), args, kw);

      // Fabricate the return tracing event.
      info.what = PyTrace_RETURN;
      Tf_PyFabricateTraceEvent(info);

      // If the call did not complete successfully, just throw back into
      // python.
      if (ARCH_UNLIKELY(!ret)) {
        TF_VERIFY(PyErr_Occurred());
        throw_error_already_set();
      }

      // If the call completed successfully, then we need to see if any tf
      // errors occurred, and if so, convert them to python exceptions.
      if (ARCH_UNLIKELY(!m.IsClean() && TfPyConvertTfErrorsToPythonException(m))) {
        Py_DECREF(ret);
        throw_error_already_set();
      }

      // Otherwise everything was clean -- return the result.
      return ret;
    }

   private:
    object _fn;
    std::string _funcName;
    std::string _fileName;
  };

  object DecorateForErrorHandling(const char *name, object const &owner, object const &fn)
  {
    object ret = fn;
    if (ARCH_LIKELY(fn.ptr() != Py_None)) {
      // Make a new function, and bind in the tracing info, funcname and
      // filename.  The perhaps slighly unusual string operations are for
      // performance reasons.
      string *fullNamePrefix = &_newModuleName;
      string localPrefix;
      if (PyObject_HasAttrString(owner.ptr(), "__module__")) {
        char const *ownerName = PyUnicode_AsUTF8(PyObject_GetAttrString(owner.ptr(), "__name__"));
        localPrefix.append(_newModuleName);
        localPrefix.push_back('.');
        localPrefix.append(ownerName);
        fullNamePrefix = &localPrefix;
      }

      ret = boost::python::detail::make_raw_function(boost::python::objects::py_function(
          _InvokeWithErrorHandling(fn, *fullNamePrefix + "." + name, *fullNamePrefix),
          boost::mpl::vector1<PyObject *>(),
          /*min_args =*/0,
          /*max_args =*/~0));

      ret.attr("__doc__") = fn.attr("__doc__");
    }

    return ret;
  }

  inline object ReplaceFunctionOnOwner(char const *name, object owner, object fn)
  {
    object newFn = DecorateForErrorHandling(name, owner, fn);
    PyObject_DelAttrString(owner.ptr(), name);
    objects::function::add_to_namespace(owner, name, newFn);
    return newFn;
  }

  bool WrapForErrorHandlingCB(char const *name, object const &owner, object const &obj)
  {
    // Handle no-throw list stuff...
    if (!strcmp(name, "RepostErrors") || !strcmp(name, "ReportActiveMarks")) {
      // We don't wrap these with error handling because they are used to
      // manage error handling, and wrapping them with it would make them
      // misbehave.  RepostErrors() is intended to either push errors back
      // onto the error list or report them, if there are no extant error
      // marks.  If we wrapped RepostErrors with error handling, then it
      // would always have an error mark (to do the error handling) and
      // could not ever report errors correctly.  It would also simply
      // reraise the posted errors as an exception in python, defeating
      // its purpose entirely.
      return false;
    }
    else if (IsBoostPythonFunc(obj)) {
      // Replace owner's name attribute with decorated function obj.
      // Do this by using boost.python's add_to_namespace, since that sets
      // up the function name correctly.  Unfortunately to do this we need
      // to make the new function, delete the old function, and add it
      // again.  Otherwise add_to_namespace will attempt to add an
      // overload.
      ReplaceFunctionOnOwner(name, owner, obj);
      return false;
    }
    else if (IsProperty(obj)) {
      // Replace owner's name attribute with a new property, decorating the
      // get, set, and del functions.

      // XXX: In Python 3.9+ this is equivalent to
      // if (!Py_IS_TYPE(obj.ptr(), &PyProperty_Type)) {
      if (Py_TYPE(obj.ptr()) != &PyProperty_Type) {
        // XXX If the type of this object is not Python's built-in
        // property descriptor, this at least for now means that this
        // is likely a static property. For now, we just don't wrap
        // static properties with error handling.
      }
      else {
        object propType(handle<>(borrowed(&PyProperty_Type)));
        object newfget = DecorateForErrorHandling(name, owner, obj.attr("fget"));
        object newfset = DecorateForErrorHandling(name, owner, obj.attr("fset"));
        object newfdel = DecorateForErrorHandling(name, owner, obj.attr("fdel"));
        object newProp = propType(newfget, newfset, newfdel, object(obj.attr("__doc__")));
        setattr(owner, name, newProp);
      }
      return false;
    }
    else if (IsStaticMethod(obj)) {
      object underlyingFn = obj.attr("__get__")(owner);
      if (IsBoostPythonFunc(underlyingFn)) {
        // Replace owner's name attribute with a new staticmethod,
        // decorating the underlying function.
        object newFn = ReplaceFunctionOnOwner(name, owner, underlyingFn);
        setattr(owner, name, object(handle<>(PyStaticMethod_New(newFn.ptr()))));
      }
      return false;
    }
    else if (IsClassMethod(obj)) {
      object underlyingFn = obj.attr("__get__")(owner).attr("__func__");
      if (IsBoostPythonFunc(underlyingFn)) {
        // Replace owner's name attribute with a new classmethod, decorating
        // the underlying function.
        object newFn = ReplaceFunctionOnOwner(name, owner, underlyingFn);
        setattr(owner, name, object(handle<>(PyClassMethod_New(newFn.ptr()))));
      }
      return false;
    }

    return true;
  }

  void WrapForErrorHandling()
  {
    WalkModule(_module, &This::WrapForErrorHandlingCB);
  }

  bool FixModuleAttrsCB(char const *name, object const &owner, object const &obj)
  {
    if (PyObject_HasAttrString(obj.ptr(), "__module__")) {
      PyObject_SetAttrString(obj.ptr(), "__module__", _newModuleNameObj.ptr());
      if (PyErr_Occurred()) {
        /*
         * Boost python functions still screw up here.
         */
        PyErr_Clear();
      }
    }
    return true;
  }

  void FixModuleAttrs()
  {
    WalkModule(_module, &This::FixModuleAttrsCB);
  }

  Tf_ModuleProcessor(object const &module)
      : _module(module), _cachedBPFuncType(0), _cachedBPClassType(0)
  {
    auto obj = object(module.attr("__name__"));
    _oldModuleName = PyUnicode_AsUTF8(obj.ptr());
    _newModuleName = TfStringGetBeforeSuffix(_oldModuleName);
    _newModuleNameObj = object(_newModuleName);
  }

 private:
  string _oldModuleName, _newModuleName;
  object _newModuleNameObj;

  object _module;

  PyObject *_cachedBPFuncType;
  PyObject *_cachedBPClassType;
};

void Tf_PyPostProcessModule()
{
  // First fix up module names for classes, the wrap all functions with proper
  // error handling.
  scope module;
  try {
    Tf_ModuleProcessor mp(module);
    mp.FixModuleAttrs();
    mp.WrapForErrorHandling();
    if (PyErr_Occurred())
      throw_error_already_set();
  }
  catch (error_already_set const &) {
    string name = extract<string>(module.attr("__name__"));
    TF_WARN("Error occurred postprocessing module %s!", name.c_str());
    TfPyPrintError();
  }
}

TF_API
void Tf_PyInitWrapModule(void (*wrapModule)(),
                         const char *packageModule,
                         const char *packageName,
                         const char *packageTag,
                         const char *packageTag2)
{
  // Starting with Python 3.7, the GIL is initialized as part of
  // Py_Initialize(). Python 3.9 deprecated explicit GIL initialization.
#if PY_VERSION_HEX < 0x03070000
  // Ensure the python GIL is created.
  PyEval_InitThreads();
#endif

  // Tell the tracing mechanism that python is alive.
  Tf_PyTracingPythonInitialized();

  // Load module dependencies.
  TfScriptModuleLoader::GetInstance().LoadModulesForLibrary(TfToken(packageName));
  if (PyErr_Occurred()) {
    throw_error_already_set();
  }

  TfAutoMallocTag tag(packageTag2, "WrapModule", packageTag);

  // Set up the wrap context.
  Tf_PyWrapContextManager::GetInstance().PushContext(packageModule);

  // Provide a way to find the full mfb name of the package.  Can't use the
  // TfToken, because when we get here in loading Tf, TfToken has not yet been
  // wrapped.
  boost::python::scope().attr("__MFB_FULL_PACKAGE_NAME") = packageName;

  // Disable docstring auto signatures.
  boost::python::docstring_options docOpts(true /*show user-defined*/, false /*show signatures*/);

  // Do the wrapping.
  wrapModule();

  // Fix up the module attributes and wrap functions for error handling.
  Tf_PyPostProcessModule();

  // Restore wrap context.
  Tf_PyWrapContextManager::GetInstance().PopContext();

  // Notify that a module has been loaded.
  TfPyModuleWasLoaded(packageName).Send();
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
