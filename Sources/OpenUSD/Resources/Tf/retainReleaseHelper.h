#ifndef retainReleaseHelper_hpp
#define retainReleaseHelper_hpp

#include "pxr/pxrns.h"
#include "Tf/refBase.h"
#include "Tf/refPtr.h"

PXR_NAMESPACE_OPEN_SCOPE

// This class exposes functions to manually manipulate the reference count of a TfRefBase.
// Never call these functions directly; they are provided for the purposes of importing TfRefBase
// with reference counting semantics into a language with automatic reference counting mechanisms.
//
// TfRefPtr<T>::_AddRefStatic/_RemoveRefStatic don't exist -- Tf_RefPtr_Counter
// is the same counter TfRefPtr<T> itself uses (minus the "unique changed"
// listener dance), and is a friend of TfRefBase, so it works for any T
// derived from TfRefBase, including TfRefBase itself.
class Tf_RetainReleaseHelper {
public:
    // Increments the reference count of the argument by 1.
    template <class T>
    inline static void retain(T* obj) {
        Tf_RefPtr_Counter::AddRef(obj);
    }

    // Decrements the reference count of the argument by 1, deleting the argument
    // if the reference count reaches 0.
    template <class T>
    inline static void release(T* obj) {
        if (Tf_RefPtr_Counter::RemoveRef(obj)) {
            // Tf_RetainReleaseHelper is a friend of TfRefBase, so this can
            // delete through a TfRefBase* even though ~TfRefBase() is
            // protected.
            Tf_RefPtrTracker_LastRef(nullptr, static_cast<const TfRefBase*>(obj), nullptr);
            delete obj;
        }
    }
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif /* retainReleaseHelper_h */
