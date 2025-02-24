//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PY_CONTAINER_CONVERSIONS_H
#define PXR_BASE_TF_PY_CONTAINER_CONVERSIONS_H

/// \file tf/pyContainerConversions.h
/// Utilities for providing C++ <-> Python container support.

/*
 * Adapted (modified) from original at http://cctbx.sourceforge.net
 * Original file:
 * cctbx/scitbx/include/scitbx/boost_python/container_conversions.h
 * License:
 * http://cvs.sourceforge.net/viewcvs.py/cctbx/cctbx/
 *                                      LICENSE.txt?rev=1.2&view=markup
 */

#include "pxr/pxrns.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#include "Tf/diagnostic.h"
#include "Tf/iterator.h"
#include "Tf/pyUtils.h"
#include "Tf/refPtr.h"
#include "Tf/weakPtr.h"

#if __has_include(<boost/python/extract.hpp>)
#include <boost/python/extract.hpp>
#include <boost/python/list.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/tuple.hpp>
#endif // __has_include(<boost/python/extract.hpp>)

#include <deque>
#include <list>
#include <set>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

// Converts any iterable C++ container to a Python list.
template<typename ContainerType> struct TfPySequenceToPython {
  static PyObject *convert(ContainerType const &c)
  {
    boost::python::list result;
    TF_FOR_ALL(i, c)
    {
      result.append(*i);
    }
    return boost::python::incref(result.ptr());
  }
};

// Converts any iterable C++ container to a Python set.
template<typename ContainerType> struct TfPySequenceToPythonSet {
  static PyObject *convert(ContainerType const &c)
  {
    PyObject *result = PySet_New(nullptr);
    for (const auto &elem : c) {
      PySet_Add(result, boost::python::object(elem).ptr());
    }
    return result;
  }
};

template<typename ContainerType> struct TfPyMapToPythonDict {
  static PyObject *convert(ContainerType const &c)
  {
    return boost::python::incref(TfPyCopyMapToDictionary(c).ptr());
  }
};

namespace TfPyContainerConversions {

template<typename ContainerType> struct to_tuple {
  static PyObject *convert(ContainerType const &a)
  {
    boost::python::list result;
    typedef typename ContainerType::const_iterator const_iter;
    for (const_iter p = a.begin(); p != a.end(); p++) {
      result.append(boost::python::object(*p));
    }
    return boost::python::incref(boost::python::tuple(result).ptr());
  }
};

template<typename First, typename Second> struct to_tuple<std::pair<First, Second>> {
  static PyObject *convert(std::pair<First, Second> const &a)
  {
    boost::python::tuple result = boost::python::make_tuple(a.first, a.second);
    return boost::python::incref(result.ptr());
  }
};

struct default_policy {
  static bool check_convertibility_per_element()
  {
    return false;
  }

  template<typename ContainerType>
  static bool check_size(boost::type<ContainerType>, std::size_t sz)
  {
    return true;
  }

  template<typename ContainerType>
  static void assert_size(boost::type<ContainerType>, std::size_t sz)
  {
  }

  template<typename ContainerType> static void reserve(ContainerType &a, std::size_t sz) {}
};

struct fixed_size_policy {
  static bool check_convertibility_per_element()
  {
    return true;
  }

  template<typename ContainerType>
  static bool check_size(boost::type<ContainerType>, std::size_t sz)
  {
    return ContainerType::size() == sz;
  }

  template<typename ContainerType>
  static void assert_size(boost::type<ContainerType>, std::size_t sz)
  {
    if (!check_size(boost::type<ContainerType>(), sz)) {
      PyErr_SetString(PyExc_RuntimeError, "Insufficient elements for fixed-size array.");
      boost::python::throw_error_already_set();
    }
  }

  template<typename ContainerType> static void reserve(ContainerType &a, std::size_t sz)
  {
    if (sz > ContainerType::size()) {
      PyErr_SetString(PyExc_RuntimeError, "Too many elements for fixed-size array.");
      boost::python::throw_error_already_set();
    }
  }

  template<typename ContainerType, typename ValueType>
  static void set_value(ContainerType &a, std::size_t i, ValueType const &v)
  {
    reserve(a, i + 1);
    a[i] = v;
  }
};

struct variable_capacity_policy : default_policy {
  template<typename ContainerType> static void reserve(ContainerType &a, std::size_t sz)
  {
    a.reserve(sz);
  }

  template<typename ContainerType, typename ValueType>
  static void set_value(ContainerType &a, std::size_t i, ValueType const &v)
  {
    TF_AXIOM(a.size() == i);
    a.push_back(v);
  }
};

struct variable_capacity_all_items_convertible_policy : variable_capacity_policy {
  static bool check_convertibility_per_element()
  {
    return true;
  }
};

struct fixed_capacity_policy : variable_capacity_policy {
  template<typename ContainerType>
  static bool check_size(boost::type<ContainerType>, std::size_t sz)
  {
    return ContainerType::max_size() >= sz;
  }
};

struct linked_list_policy : default_policy {
  template<typename ContainerType, typename ValueType>
  static void set_value(ContainerType &a, std::size_t i, ValueType const &v)
  {
    a.push_back(v);
  }
};

struct set_policy : default_policy {
  template<typename ContainerType, typename ValueType>
  static void set_value(ContainerType &a, std::size_t i, ValueType const &v)
  {
    a.insert(v);
  }
};

template<typename ContainerType, typename ConversionPolicy> struct from_python_sequence {
  typedef typename ContainerType::value_type container_element_type;

  from_python_sequence()
  {
    boost::python::converter::registry::push_back(
        &convertible, &construct, boost::python::type_id<ContainerType>());
  }

  static void *convertible(PyObject *obj_ptr)
  {
    if (!(PyList_Check(obj_ptr) || PyTuple_Check(obj_ptr) || PySet_Check(obj_ptr) ||
          PyFrozenSet_Check(obj_ptr) || PyIter_Check(obj_ptr) || PyRange_Check(obj_ptr) ||
          (!PyBytes_Check(obj_ptr) && !PyUnicode_Check(obj_ptr) &&
           (Py_TYPE(obj_ptr) == 0 || Py_TYPE(Py_TYPE(obj_ptr)) == 0 ||
            Py_TYPE(Py_TYPE(obj_ptr))->tp_name == 0 ||
            std::strcmp(Py_TYPE(Py_TYPE(obj_ptr))->tp_name, "Boost.Python.class") != 0) &&
           PyObject_HasAttrString(obj_ptr, "__len__") &&
           PyObject_HasAttrString(obj_ptr, "__getitem__"))))
      return 0;
    boost::python::handle<> obj_iter(boost::python::allow_null(PyObject_GetIter(obj_ptr)));
    if (!obj_iter.get()) {  // must be convertible to an iterator
      PyErr_Clear();
      return 0;
    }
    if (ConversionPolicy::check_convertibility_per_element()) {
      Py_ssize_t obj_size = PyObject_Length(obj_ptr);
      if (obj_size < 0) {  // must be a measurable sequence
        PyErr_Clear();
        return 0;
      }
      if (!ConversionPolicy::check_size(boost::type<ContainerType>(), obj_size))
        return 0;
      bool is_range = PyRange_Check(obj_ptr);
      std::size_t i = 0;
      if (!all_elements_convertible(obj_iter, is_range, i))
        return 0;
      if (!is_range)
        assert(i == (std::size_t)obj_size);
    }
    return obj_ptr;
  }

  // This loop factored out by Achim Domma to avoid Visual C++
  // Internal Compiler Error.
  static bool all_elements_convertible(boost::python::handle<> &obj_iter,
                                       bool is_range,
                                       std::size_t &i)
  {
    for (;; i++) {
      boost::python::handle<> py_elem_hdl(boost::python::allow_null(PyIter_Next(obj_iter.get())));
      if (PyErr_Occurred()) {
        PyErr_Clear();
        return false;
      }
      if (!py_elem_hdl.get())
        break;  // end of iteration
      boost::python::object py_elem_obj(py_elem_hdl);
      boost::python::extract<container_element_type> elem_proxy(py_elem_obj);
      if (!elem_proxy.check())
        return false;
      if (is_range)
        break;  // in a range all elements are of the same type
    }
    return true;
  }

  static void construct(PyObject *obj_ptr,
                        boost::python::converter::rvalue_from_python_stage1_data *data)
  {
    boost::python::handle<> obj_iter(PyObject_GetIter(obj_ptr));
    void *storage = ((boost::python::converter::rvalue_from_python_storage<ContainerType> *)data)
                        ->storage.bytes;
    new (storage) ContainerType();
    data->convertible = storage;
    ContainerType &result = *((ContainerType *)storage);
    std::size_t i = 0;
    for (;; i++) {
      boost::python::handle<> py_elem_hdl(boost::python::allow_null(PyIter_Next(obj_iter.get())));
      if (PyErr_Occurred())
        boost::python::throw_error_already_set();
      if (!py_elem_hdl.get())
        break;  // end of iteration
      boost::python::object py_elem_obj(py_elem_hdl);
      boost::python::extract<container_element_type> elem_proxy(py_elem_obj);
      ConversionPolicy::set_value(result, i, elem_proxy());
    }
    ConversionPolicy::assert_size(boost::type<ContainerType>(), i);
  }
};

template<typename PairType> struct from_python_tuple_pair {
  typedef typename PairType::first_type first_type;
  typedef typename PairType::second_type second_type;

  from_python_tuple_pair()
  {
    boost::python::converter::registry::push_back(
        &convertible, &construct, boost::python::type_id<PairType>());
  }

  static void *convertible(PyObject *obj_ptr)
  {
    if (!PyTuple_Check(obj_ptr) || PyTuple_Size(obj_ptr) != 2) {
      return 0;
    }
    boost::python::extract<first_type> e1(PyTuple_GetItem(obj_ptr, 0));
    boost::python::extract<second_type> e2(PyTuple_GetItem(obj_ptr, 1));
    if (!e1.check() || !e2.check()) {
      return 0;
    }
    return obj_ptr;
  }

  static void construct(PyObject *obj_ptr,
                        boost::python::converter::rvalue_from_python_stage1_data *data)
  {
    void *storage =
        ((boost::python::converter::rvalue_from_python_storage<PairType> *)data)->storage.bytes;
    boost::python::extract<first_type> e1(PyTuple_GetItem(obj_ptr, 0));
    boost::python::extract<second_type> e2(PyTuple_GetItem(obj_ptr, 1));
    new (storage) PairType(e1(), e2());
    data->convertible = storage;
  }
};

template<typename ContainerType> struct to_tuple_mapping {
  to_tuple_mapping()
  {
    boost::python::to_python_converter<ContainerType, to_tuple<ContainerType>>();
  }
};

template<typename ContainerType, typename ConversionPolicy>
struct tuple_mapping : to_tuple_mapping<ContainerType> {
  tuple_mapping()
  {
    from_python_sequence<ContainerType, ConversionPolicy>();
  }
};

template<typename ContainerType> struct tuple_mapping_fixed_size {
  tuple_mapping_fixed_size()
  {
    tuple_mapping<ContainerType, fixed_size_policy>();
  }
};

template<typename ContainerType> struct tuple_mapping_fixed_capacity {
  tuple_mapping_fixed_capacity()
  {
    tuple_mapping<ContainerType, fixed_capacity_policy>();
  }
};

template<typename ContainerType> struct tuple_mapping_variable_capacity {
  tuple_mapping_variable_capacity()
  {
    tuple_mapping<ContainerType, variable_capacity_policy>();
  }
};

template<typename ContainerType> struct tuple_mapping_set {
  tuple_mapping_set()
  {
    tuple_mapping<ContainerType, set_policy>();
  }
};

template<typename ContainerType> struct tuple_mapping_pair {
  tuple_mapping_pair()
  {
    boost::python::to_python_converter<ContainerType, to_tuple<ContainerType>>();
    from_python_tuple_pair<ContainerType>();
  }
};

}  // namespace TfPyContainerConversions

template<class T> void TfPyRegisterStlSequencesFromPython()
{
  using namespace TfPyContainerConversions;
  from_python_sequence<std::vector<T>, variable_capacity_all_items_convertible_policy>();
  from_python_sequence<std::list<T>, variable_capacity_all_items_convertible_policy>();
  from_python_sequence<std::deque<T>, variable_capacity_all_items_convertible_policy>();
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#endif  // PXR_BASE_TF_PY_CONTAINER_CONVERSIONS_H
