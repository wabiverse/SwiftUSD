//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_DIAGNOSTIC_BASE_H
#define PXR_BASE_TF_DIAGNOSTIC_BASE_H

/// \file tf/diagnosticBase.h

#include "Tf/api.h"
#include "Tf/callContext.h"
#include "Tf/enum.h"
#include "Tf/refBase.h"
#include "Tf/stringUtils.h"
#include "Tf/weakPtr.h"
#include "pxr/pxrns.h"

#include "Arch/attributes.h"
#include "Arch/function.h"
#include "Arch/inttypes.h"

#if defined(_WIN32) || defined(__ANDROID__)
# include <any/any.hpp>

namespace std
{
  using namespace linb;
}
#else // !defined(_WIN32) && !defined(__ANDROID__)
# include <any>
#endif // defined(_WIN32) || defined(__ANDROID__)

#include <cstdarg>
#include <string>

PXR_NAMESPACE_OPEN_SCOPE

typedef std::any TfDiagnosticInfo;

class TfDiagnosticMgr;

/// \class TfDiagnosticBase
/// \ingroup group_tf_TfError
///
/// Represents the base class of an object representing a diagnostic message.
///
/// This forms the base class for specific types associated with errors,
/// warnings and status messages. It associates a diagnostic code (which is an
/// enum value) with the message. It can also hold on to arbitrary information
/// associated with the message in a TfDiagnosticInfo.
///
/// See \ref page_tf_TfError in the C++ API reference for a detailed example.
/// For a description of how to post an error, warning or a status message see
/// \c TF_ERROR(), \c TF_WARN and \c TF_STATUS also in the C++ API reference.
///
class TfDiagnosticBase {
 public:
  /// Return the call context where the message was issued.
  const TfCallContext &GetContext() const
  {
    return _context;
  }

  /// Return the source file name that the diagnostic message was posted from.
  std::string GetSourceFileName() const
  {
    return _context.GetFile();
  }

  /// Return the source line number that the diagnostic message was posted
  /// from.
  size_t GetSourceLineNumber() const
  {
    return _context.GetLine();
  }

  /// Return the commentary string describing this diagnostic message.
  std::string const &GetCommentary() const
  {
    return _commentary;
  }

  /// Return the source function that the diagnostic message was posted from.
  std::string GetSourceFunction() const
  {
    return ArchGetPrettierFunctionName(_context.GetFunction(), _context.GetPrettyFunction());
  }

  /// Add to the commentary string describing this diagnostic message.
  ///
  /// Note: each string added to the commentary is separated from
  /// the previous one with a newline. This means that
  /// you the string \c s should \e not end with a newline. Thus,
  /// \code
  ///    cout << e.GetCommentary() << "\n";
  /// \endcode
  /// always prints the entire commentary string as a newline
  /// separated sequence of messages.
  void AugmentCommentary(const std::string &s)
  {
    if (_commentary.empty())
      _commentary = s;
    else {
      _commentary += "\n";
      _commentary += s;
    }
  }

  /// Return the diagnostic code posted.
  TfEnum GetDiagnosticCode() const
  {
    return _code;
  }

  /// Return the diagnostic code posted as a string.
  ///
  /// If the enum value posted with the message has been registered
  /// with \c TF_ADD_ENUM_NAME(), then \c GetDiagnosticCodeAsString() will
  /// return the symbolic name of the enum.
  ///
  /// If the enum has not been registered, then code of the form
  /// \code
  ///     TF_ERROR(PUCE).Post("is an ugly color");
  /// \endcode
  /// will still result in \c GetDiagnosticCodeAsString() returning the string
  /// "PUCE"; however, code of the form
  /// \code
  ///     MyErrorCode c = PUCE;
  ///     TF_ERROR(c).Post("is still ugly");
  /// \endcode
  /// will result in \c GetDiagnosticCodeAsString() returning the
  /// (uninformative) string "c".
  const std::string &GetDiagnosticCodeAsString() const
  {
    return _codeString;
  }

  /// Return a (possibly NULL) const pointer to the info object associated
  /// with this message.
  ///
  /// If this message was posted without supplying an \c info argument to
  /// Post(), e.g.
  /// \code
  ///    TF_ERROR(SOME_CODE).Post("something went wrong");
  /// \endcode
  ///
  /// then \c GetInfo() returns NULL.  Otherwise, when info is supplied,
  /// e.g.
  /// \code
  ///    T myInfo = ...
  ///    TF_ERROR(SOME_CODE).Post("something went wrong")->SetInfo(myInfo);
  /// \endcode
  ///
  /// then a const pointer to a copy of myInfo in the above example is
  /// returned by GetInfo<T>().  If the type T doesn't match the held type
  /// then GetInfo() returns NULL.
  template<typename T> const T *GetInfo() const
  {
    return std::any_cast<T>(&_info);
  }

  /// Set the info object associated with this diagnostic message.
  /// \see GetInfo()
  void SetInfo(TfDiagnosticInfo any)
  {
    _info = any;
  }

  /// Return true if the message was posted via \c PostQuietly().
  ///
  /// Notices sent from \c PostQuietly() are indicating that an immediate
  /// printout of the error is not desirable, because someone higher up on
  /// the stack may actually handle this error. This is rare, but it does
  /// happen on occasion.
  bool GetQuiet() const
  {
    return _quiet;
  }

  /// Return true if this diagnostic's code is a fatal code.
  TF_API
  bool IsFatal() const;

  /// Return true if this diagnostic's code is either a fatal or nonfatal
  /// coding error.
  TF_API
  bool IsCodingError() const;

  /// Construct an instance.
  TF_API
  TfDiagnosticBase(TfEnum code,
                   char const *codeString,
                   TfCallContext const &context,
                   const std::string &commentary,
                   TfDiagnosticInfo info,
                   bool quiet);

 protected:
  TfCallContext _context;

  std::string _commentary;
  TfEnum _code;
  std::string _codeString;
  TfDiagnosticInfo _info;
  size_t _serial = 0;
  bool _quiet = false;

  friend class TfDiagnosticMgr;
  friend class TfErrorTransport;
  friend class TfErrorMark;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TF_DIAGNOSTIC_BASE_H
