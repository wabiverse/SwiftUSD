//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_VT_VALUE_FROM_PYTHON_H
#define PXR_BASE_VT_VALUE_FROM_PYTHON_H

/// \file vt/valueFromPython.h

#include "Vt/api.h"
#include "Vt/value.h"
#include "pxr/pxrns.h"

#include "Tf/hash.h"
#include "Tf/hashmap.h"
#include "Tf/pyUtils.h"
#include "Tf/singleton.h"

#include "Tf/pySafePython.h"

#include <vector>

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_OPEN_SCOPE

/// \class Vt_ValueFromPythonRegistry
///
class Vt_ValueFromPythonRegistry {
 public:
  static bool HasConversions()
  {
    return !_GetInstance()._lvalueExtractors.empty() && !_GetInstance()._rvalueExtractors.empty();
  }

  VT_API static VtValue Invoke(PyObject *obj);

  template<class T> static void Register(bool registerRvalue)
  {
    if (!TfPyIsInitialized()) {
      TF_FATAL_ERROR(
          "Tried to register a VtValue from python conversion "
          "but python is not initialized!");
    }
    _GetInstance()._RegisterLValue(_Extractor::MakeLValue<T>());
    if (registerRvalue)
      _GetInstance()._RegisterRValue(_Extractor::MakeRValue<T>());
  }

  Vt_ValueFromPythonRegistry(Vt_ValueFromPythonRegistry const &) = delete;
  Vt_ValueFromPythonRegistry &operator=(Vt_ValueFromPythonRegistry const &) = delete;

  Vt_ValueFromPythonRegistry(Vt_ValueFromPythonRegistry &&) = delete;
  Vt_ValueFromPythonRegistry &operator=(Vt_ValueFromPythonRegistry &&) = delete;

 private:
  Vt_ValueFromPythonRegistry() {}
  VT_API ~Vt_ValueFromPythonRegistry();

  friend class TfSingleton<Vt_ValueFromPythonRegistry>;

  class _Extractor {
   private:
    using _ExtractFunc = VtValue (*)(PyObject *);

    // _ExtractLValue will attempt to obtain an l-value T from the python
    // object it's passed.  This effectively disallows type conversions
    // (other than things like derived-to-base type conversions).
    template<class T> static VtValue _ExtractLValue(PyObject *);

    // _ExtractRValue will attempt to obtain an r-value T from the python
    // object it's passed.  This allows boost.python to invoke type
    // conversions to produce the T.
    template<class T> static VtValue _ExtractRValue(PyObject *);

   public:
    template<class T> static _Extractor MakeLValue()
    {
      return _Extractor(&_ExtractLValue<T>);
    }

    template<class T> static _Extractor MakeRValue()
    {
      return _Extractor(&_ExtractRValue<T>);
    }

    VtValue Invoke(PyObject *obj) const
    {
      return _extract(obj);
    }

   private:
    explicit _Extractor(_ExtractFunc extract) : _extract(extract) {}

    _ExtractFunc _extract;
  };

  VT_API static Vt_ValueFromPythonRegistry &_GetInstance()
  {
    return TfSingleton<Vt_ValueFromPythonRegistry>::GetInstance();
  }

  VT_API void _RegisterLValue(_Extractor const &e);
  VT_API void _RegisterRValue(_Extractor const &e);

  std::vector<_Extractor> _lvalueExtractors;
  std::vector<_Extractor> _rvalueExtractors;

  typedef TfHashMap<PyObject *, _Extractor, TfHash> _LValueExtractorCache;
  _LValueExtractorCache _lvalueExtractorCache;
};

VT_API_TEMPLATE_CLASS(TfSingleton<Vt_ValueFromPythonRegistry>);

template<class T> VtValue Vt_ValueFromPythonRegistry::_Extractor::_ExtractLValue(PyObject *obj)
{
  boost::python::extract<T &> x(obj);
  if (x.check())
    return VtValue(x());
  return VtValue();
}

template<class T> VtValue Vt_ValueFromPythonRegistry::_Extractor::_ExtractRValue(PyObject *obj)
{
  boost::python::extract<T> x(obj);
  if (x.check())
    return VtValue(x());
  return VtValue();
}

template<class T> void VtValueFromPython()
{
  Vt_ValueFromPythonRegistry::Register<T>(/* registerRvalue = */ true);
}

template<class T> void VtValueFromPythonLValue()
{
  Vt_ValueFromPythonRegistry::Register<T>(/* registerRvalue = */ false);
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#endif  // PXR_BASE_VT_VALUE_FROM_PYTHON_H
