//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_BASE_TF_PATTERN_MATCHER_H
#define PXR_BASE_TF_PATTERN_MATCHER_H

/// \file tf/patternMatcher.h
/// \ingroup group_tf_String
/// A simple glob and regex matching utility.

#include "Arch/regex.h"
#include "Tf/api.h"
#include "pxr/pxrns.h"

#include <string>

PXR_NAMESPACE_OPEN_SCOPE

/// \class TfPatternMatcher
/// \ingroup group_tf_String
///
/// Class for matching regular expressions.
///
/// A matcher is good to use when you have many strings to match against one
/// pattern. This is because the matcher will only compile the regular
/// expression once.
///
class TfPatternMatcher {

 public:
  /// Construct an empty (invalid) TfPatternMatcher.
  TF_API TfPatternMatcher();

  TF_API TfPatternMatcher(TfPatternMatcher &&) noexcept = default;
  TF_API TfPatternMatcher &operator=(TfPatternMatcher &&) = default;

  /// Construct a TfPatternMatcher with a default configuration.  Note that
  /// pattern compilation will not occur until the first call to \a Match()
  /// or \a IsValid().
  TF_API
  TfPatternMatcher(const std::string &pattern, bool caseSensitive = false, bool isGlob = false);

  /// Destructor.
  TF_API ~TfPatternMatcher();

  /// If \a IsValid() returns true, this will return the reason why (if any).
  TF_API std::string GetInvalidReason() const;

  /// Returns true if the matcher has been set to be case sensitive, false
  /// otherwise.
  bool IsCaseSensitive() const
  {
    return _caseSensitive;
  }

  /// Returns true if the matcher has been set to treat patterns as glob
  /// patterns, false otherwise.
  bool IsGlobPattern() const
  {
    return _isGlob;
  }

  /// Returns the matcher's pattern string.
  TF_API const std::string &GetPattern() const
  {
    return _pattern;
  }

  /// Returns true if the matcher has a valid pattern.  Note that empty
  /// patterns are considered invalid.  This will cause a compile of
  TF_API bool IsValid() const;

  /// Returns true if \a query matches the matcher's pattern.
  ///
  /// If there is an error in matching and errorMsg is not NULL, it will be
  /// set with the error message. If the matcher is not valid, this will
  /// return false. Note that this will cause a compile of the matcher's
  /// pattern if it was not already compiled.
  ///
  /// \warning Unlike 'match' functions in other regular expression
  /// libraries, this method does not implicitly anchor the pattern. If a
  /// partial match is not acceptable, it is necessary to anchor the pattern
  /// passed to the constructor, e.g. "^mypattern$".
  ///
  TF_API bool Match(const std::string &query, std::string *errorMsg = NULL) const;

  /// Set this matcher to match case-sensitively or not.
  TF_API void SetIsCaseSensitive(bool sensitive);

  /// Set this matcher to treat its pattern as a glob pattern. Currently,
  /// this means that the pattern will be transformed by replacing all
  /// instances of '.' with '\.', '*' with '.*', and '?' with '.', in that
  /// order before being compiled as a normal regular expression.
  TF_API void SetIsGlobPattern(bool isGlob);

  /// Set the pattern that this matcher will use to match against.
  TF_API void SetPattern(const std::string &pattern);

 private:
  void _Compile() const;

  bool _caseSensitive;
  bool _isGlob;
  std::string _pattern;
  mutable bool _recompile;
  mutable ArchRegex _regex;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_BASE_TF_PATTERN_MATCHER_H
