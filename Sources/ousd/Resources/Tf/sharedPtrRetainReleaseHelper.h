#ifndef PXR_BASE_TF_SHARED_PTR_RETAIN_RELEASE_HELPER_H
#define PXR_BASE_TF_SHARED_PTR_RETAIN_RELEASE_HELPER_H

#include "pxr/pxrns.h"

#include <memory>
#include <mutex>
#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

/// Bridges the non-intrusive reference counting of \c std::shared_ptr to
/// Swift's ARC for types that are not \c TfRefBase subclasses (and so can't
/// use \c Tf_RetainReleaseHelper).
///
/// \c Register records the \c shared_ptr under its raw pointer with an
/// initial count of 1 - the reference transferred to Swift. \c Retain and
/// \c Release adjust that count, and \c Release drops the stored
/// \c shared_ptr (permitting destruction of the underlying object, if this
/// was the last owner) once the count reaches 0.
template<class T> class Tf_SharedPtrRetainReleaseHelper {
 public:
  static T *Register(const std::shared_ptr<T> &ptr)
  {
    std::lock_guard<std::mutex> lock(_GetMutex());
    T *raw = ptr.get();
    _Entry &entry = _GetTable()[raw];
    entry.first = ptr;
    entry.second += 1;
    return raw;
  }

  static void Retain(T *raw)
  {
    std::lock_guard<std::mutex> lock(_GetMutex());
    auto it = _GetTable().find(raw);
    if (it != _GetTable().end()) {
      it->second.second += 1;
    }
  }

  static void Release(T *raw)
  {
    std::lock_guard<std::mutex> lock(_GetMutex());
    auto it = _GetTable().find(raw);
    if (it != _GetTable().end() && --it->second.second == 0) {
      _GetTable().erase(it);
    }
  }

 private:
  using _Entry = std::pair<std::shared_ptr<T>, int>;

  static std::unordered_map<T *, _Entry> &_GetTable()
  {
    static std::unordered_map<T *, _Entry> table;
    return table;
  }

  static std::mutex &_GetMutex()
  {
    static std::mutex mutex;
    return mutex;
  }
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TF_SHARED_PTR_RETAIN_RELEASE_HELPER_H
