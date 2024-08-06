//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PY_NOTICE_WRAPPER_H
#define PXR_BASE_TF_PY_NOTICE_WRAPPER_H

#include "Tf/notice.h"
#include "Tf/pyLock.h"
#include "Tf/pyObjectFinder.h"
#include "Tf/staticData.h"
#include "Tf/stringUtils.h"
#include "Tf/type.h"
#include "Tf/wrapTypeHelpers.h"
#include "pxr/pxrns.h"

#include <boost/python/bases.hpp>
#include <boost/python/class.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/handle.hpp>

#include <map>
#include <string>
#include <type_traits>

PXR_NAMESPACE_OPEN_SCOPE

struct Tf_PyNoticeObjectGenerator {
  typedef Tf_PyNoticeObjectGenerator This;
  typedef boost::python::object (*MakeObjectFunc)(TfNotice const &);

  // Register the generator for notice type T.
  template<typename T> static void Register()
  {
    // XXX this stuff should be keyed directly off TfType now
    (*_generators)[typeid(T).name()] = This::_Generate<T>;
  }

  // Produce a boost::python::object for the correct derived type of \a n.
  TF_API static boost::python::object Invoke(TfNotice const &n);

 private:
  template<typename T> static boost::python::object _Generate(TfNotice const &n)
  {
    // Python locking is left to the caller.
    return boost::python::object(static_cast<T const &>(n));
  }

  static MakeObjectFunc _Lookup(TfNotice const &n);

  TF_API static TfStaticData<std::map<std::string, MakeObjectFunc>> _generators;
};

struct TfPyNoticeWrapperBase : public TfType::PyPolymorphicBase {
  TF_API virtual ~TfPyNoticeWrapperBase();
  virtual boost::python::handle<> GetNoticePythonObject() const = 0;
};

template<class Notice> struct Tf_PyNoticeObjectFinder : public Tf_PyObjectFinderBase {
  virtual ~Tf_PyNoticeObjectFinder() {}
  virtual boost::python::object Find(void const *objPtr) const
  {
    using namespace boost::python;
    TfPyLock lock;
    Notice const *wrapper = static_cast<Notice const *>(objPtr);
    return wrapper ? object(wrapper->GetNoticePythonObject()) : object();
  }
};

template<typename NoticeType, typename BaseType>
struct TfPyNoticeWrapper : public NoticeType, public TfPyNoticeWrapperBase {
 private:
  static_assert(std::is_base_of<TfNotice, NoticeType>::value ||
                    std::is_same<TfNotice, NoticeType>::value,
                "Notice type must be derived from or equal to TfNotice.");

  static_assert(std::is_base_of<TfNotice, BaseType>::value ||
                    std::is_same<TfNotice, BaseType>::value,
                "BaseType type must be derived from or equal to TfNotice.");

  static_assert(std::is_base_of<BaseType, NoticeType>::value ||
                    (std::is_same<NoticeType, TfNotice>::value &&
                     std::is_same<BaseType, TfNotice>::value),
                "BaseType type must be a base of notice, unless both "
                "BaseType and Notice type are equal to TfNotice.");

 public:
  typedef TfPyNoticeWrapper<NoticeType, BaseType> This;

  // If Notice is really TfNotice, then this is the root of the hierarchy and
  // bases is empty, otherwise bases contains the base class.
  using Bases = std::conditional_t<std::is_same<NoticeType, TfNotice>::value,
                                   boost::python::bases<>,
                                   boost::python::bases<BaseType>>;

  typedef boost::python::class_<NoticeType, This, Bases> ClassType;

  static ClassType Wrap(std::string const &name = std::string())
  {
    std::string wrappedName = name;
    if (wrappedName.empty()) {
      // Assume they want the last bit of a qualified name.
      wrappedName = TfType::Find<NoticeType>().GetTypeName();
      if (!TfStringGetSuffix(wrappedName, ':').empty())
        wrappedName = TfStringGetSuffix(wrappedName, ':');
    }
    Tf_PyNoticeObjectGenerator::Register<NoticeType>();
    Tf_RegisterPythonObjectFinderInternal(typeid(TfPyNoticeWrapper),
                                          new Tf_PyNoticeObjectFinder<TfPyNoticeWrapper>);
    return ClassType(wrappedName.c_str(), boost::python::no_init).def(TfTypePythonClass());
  }

  // Implement the base class's virtual method.
  virtual boost::python::handle<> GetNoticePythonObject() const
  {
    TfPyLock lock;
    return boost::python::handle<>(boost::python::borrowed(_self));
  }

  // Arbitrary argument constructor (with a leading PyObject *) which
  // forwards to the base Notice class's constructor.
  template<typename... Args>
  TfPyNoticeWrapper(PyObject *self, Args... args) : NoticeType(args...), _self(self)
  {
  }

 private:
  PyObject *_self;
};

#define TF_INSTANTIATE_NOTICE_WRAPPER(T, Base) \
  TF_REGISTRY_FUNCTION(TfType) \
  { \
    TfType::Define<TfPyNoticeWrapper<T, Base>, TfType::Bases<Base>>(); \
  }

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TF_PY_NOTICE_WRAPPER_H
