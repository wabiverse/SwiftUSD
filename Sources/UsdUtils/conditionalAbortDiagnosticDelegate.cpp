//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "UsdUtils/conditionalAbortDiagnosticDelegate.h"
#include "Arch/debugger.h"
#include "Tf/patternMatcher.h"
#include "Tf/stackTrace.h"

#include <cstdio>

PXR_NAMESPACE_OPEN_SCOPE

// Helper function to print diagnostics in same format as TfDiagnosticMgr
void _PrintDiagnostic(const TfEnum &code,
                      const TfCallContext &ctx,
                      const std::string &msg,
                      const TfDiagnosticInfo &info);

// Helper function to construct patternMatchers
std::vector<TfPatternMatcher> constructPatternFilters(const std::vector<std::string> &filters)
{
  std::vector<TfPatternMatcher> patternMatchers;
  patternMatchers.reserve(filters.size());
  for (const std::string &filter : filters) {
    patternMatchers.push_back(TfPatternMatcher(filter, true, true));
    if (!patternMatchers.back().IsValid()) {
      TF_WARN("Invalid pattern string: %s", filter.c_str());
    }
  }
  return patternMatchers;
}

UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters::
    UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters(
        const std::vector<std::string> &stringFilters,
        const std::vector<std::string> &codePathFilters)
    : _stringFilters(stringFilters), _codePathFilters(codePathFilters)
{
}

void UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters::SetStringFilters(
    const std::vector<std::string> &stringFilters)
{
  _stringFilters = stringFilters;
}

void UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters::SetCodePathFilters(
    const std::vector<std::string> &codePathFilters)
{
  _codePathFilters = codePathFilters;
}

UsdUtilsConditionalAbortDiagnosticDelegate::UsdUtilsConditionalAbortDiagnosticDelegate(
    const UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters &includeFilters,
    const UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters &excludeFilters)
    : _includePatternStringFilters(constructPatternFilters(includeFilters.GetStringFilters())),
      _includePatternCodePathFilters(constructPatternFilters(includeFilters.GetCodePathFilters())),
      _excludePatternStringFilters(constructPatternFilters(excludeFilters.GetStringFilters())),
      _excludePatternCodePathFilters(constructPatternFilters(excludeFilters.GetCodePathFilters()))
{
  TfDiagnosticMgr::GetInstance().AddDelegate(this);
}

UsdUtilsConditionalAbortDiagnosticDelegate::~UsdUtilsConditionalAbortDiagnosticDelegate()
{
  TfDiagnosticMgr::GetInstance().RemoveDelegate(this);
}

bool UsdUtilsConditionalAbortDiagnosticDelegate::_RuleMatcher(
    const TfDiagnosticBase &err,
    const std::vector<TfPatternMatcher> &stringPatternFilters,
    const std::vector<TfPatternMatcher> &codePathPatternFilters)
{
  const std::string &sourceFileName = err.GetSourceFileName();
  if (!sourceFileName.empty()) {
    for (const TfPatternMatcher &codePathPattern : codePathPatternFilters) {
      if (codePathPattern.Match(sourceFileName)) {
        return true;
      }
    }
  }
  const std::string &errorString = err.GetCommentary();
  if (!errorString.empty()) {
    for (const TfPatternMatcher &stringPattern : stringPatternFilters) {
      if (stringPattern.Match(errorString)) {
        return true;
      }
    }
  }
  return false;
}

void UsdUtilsConditionalAbortDiagnosticDelegate::IssueError(const TfError &err)
{
  // if matching in include rules and NOT in exclude rules then abort
  if (_RuleMatcher(err, _includePatternStringFilters, _includePatternCodePathFilters) &&
      !_RuleMatcher(err, _excludePatternStringFilters, _excludePatternCodePathFilters))
  {
    TfLogCrash(
        "Aborted by UsdUtilsConditionalAbortDiagnosticDelegate On "
        "Error",
        err.GetCommentary(),
        std::string(),
        err.GetContext(),
        true);
    ArchAbort(false);
  }
  else if (!err.GetQuiet()) {
    _PrintDiagnostic(
        err.GetDiagnosticCode(), err.GetContext(), err.GetCommentary(), err.GetInfo<TfError>());
  }
}

void UsdUtilsConditionalAbortDiagnosticDelegate::IssueFatalError(const TfCallContext &ctx,
                                                                 const std::string &msg)
{
  TfLogCrash("FATAL ERROR", msg, std::string() /*additionalInfo*/, ctx, true /*logToDB*/);
  ArchAbort(/*logging=*/false);
}

void UsdUtilsConditionalAbortDiagnosticDelegate::IssueStatus(const TfStatus &status)
{
  _PrintDiagnostic(status.GetDiagnosticCode(),
                   status.GetContext(),
                   status.GetCommentary(),
                   status.GetInfo<TfStatus>());
}

void UsdUtilsConditionalAbortDiagnosticDelegate::IssueWarning(const TfWarning &warning)
{
  // if matching in include rules and NOT in exclude rules then abort
  if (_RuleMatcher(warning, _includePatternStringFilters, _includePatternCodePathFilters) &&
      !_RuleMatcher(warning, _excludePatternStringFilters, _excludePatternCodePathFilters))
  {
    TfLogCrash(
        "Aborted by UsdUtilsConditionalAbortDiagnosticDelegate On "
        "Warning",
        warning.GetCommentary(),
        std::string(),
        warning.GetContext(),
        true);
    ArchAbort(false);
  }
  else if (!warning.GetQuiet()) {
    _PrintDiagnostic(warning.GetDiagnosticCode(),
                     warning.GetContext(),
                     warning.GetCommentary(),
                     warning.GetInfo<TfWarning>());
  }
}

void _PrintDiagnostic(const TfEnum &code,
                      const TfCallContext &ctx,
                      const std::string &msg,
                      const TfDiagnosticInfo &info)
{
  std::fprintf(stderr, "%s", TfDiagnosticMgr::FormatDiagnostic(code, ctx, msg, info).c_str());
}

PXR_NAMESPACE_CLOSE_SCOPE
