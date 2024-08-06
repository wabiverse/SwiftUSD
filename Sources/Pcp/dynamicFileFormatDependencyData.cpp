//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Pcp/dynamicFileFormatDependencyData.h"
#include "Pcp/dynamicFileFormatInterface.h"
#include "Sdf/fileFormat.h"
#include "Vt/value.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

PcpDynamicFileFormatDependencyData::PcpDynamicFileFormatDependencyData(
    const PcpDynamicFileFormatDependencyData &other)
{
  // Have to copy the contents of the unique pointer if it's non-null.
  if (other._data) {
    _data.reset(new _Data(*other._data));
  }
}

void PcpDynamicFileFormatDependencyData::AddDependencyContext(
    const PcpDynamicFileFormatInterface *dynamicFileFormat,
    VtValue &&dependencyContextData,
    TfToken::Set &&composedFieldNames,
    TfToken::Set &&composedAttributeNames)
{
  // Create the data now if it was empty before this call..
  if (!_data) {
    _data.reset(new _Data());
  }

  // Add file format and context data to the list and update the list of
  // relevant fields.
  _data->dependencyContexts.emplace_back(dynamicFileFormat, std::move(dependencyContextData));
  _data->_AddRelevantFieldNames(std::move(composedFieldNames));
  _data->_AddRelevantAttributeNames(std::move(composedAttributeNames));
}

void PcpDynamicFileFormatDependencyData::AppendDependencyData(
    PcpDynamicFileFormatDependencyData &&dependencyData)
{
  if (!dependencyData._data) {
    return;
  }
  // If we have our own data we need to append, otherwise we can just take
  // the other dependency data wholesale.
  if (_data) {
    // Take each context from the other data and add it to ours.
    for (_Data::_ContextData &contextData : dependencyData._data->dependencyContexts) {
      _data->dependencyContexts.emplace_back(std::move(contextData));
    }
    // Add the other data's relevants fields to ours as well.
    _data->_AddRelevantFieldNames(std::move(dependencyData._data->relevantFieldNames));
    _data->_AddRelevantAttributeNames(std::move(dependencyData._data->relevantAttributeNames));
  }
  else {
    Swap(dependencyData);
  }
}

bool PcpDynamicFileFormatDependencyData::CanFieldChangeAffectFileFormatArguments(
    const TfToken &fieldName, const VtValue &oldValue, const VtValue &newValue) const
{
  if (!_data) {
    return false;
  }

  // Early out if this particular field wasn't composed for this dependency.
  if (_data->relevantFieldNames.count(fieldName) == 0) {
    return false;
  }

  // Check each dependency context.
  for (const _Data::_ContextData &contextData : _data->dependencyContexts) {
    // We better not have logged a dependency for a file format that doesn't
    // support dynamic arguments.
    if (!TF_VERIFY(contextData.first)) {
      continue;
    }

    // Return true if any context's file format can be affect by this
    // field change.
    if (contextData.first->CanFieldChangeAffectFileFormatArguments(
            fieldName, oldValue, newValue, contextData.second))
    {
      return true;
    }
  }
  return false;
}

bool PcpDynamicFileFormatDependencyData::CanAttributeDefaultValueChangeAffectFileFormatArguments(
    const TfToken &attributeName, const VtValue &oldValue, const VtValue &newValue) const
{
  if (!_data) {
    return false;
  }

  // Early out if this particular field wasn't composed for this dependency.
  if (_data->relevantAttributeNames.count(attributeName) == 0) {
    return false;
  }

  // Check each dependency context.
  for (const _Data::_ContextData &contextData : _data->dependencyContexts) {
    // We better not have logged a dependency for a file format that doesn't
    // support dynamic arguments.
    if (!TF_VERIFY(contextData.first)) {
      continue;
    }

    // Return true if any context's file format can be affect by this
    // field change.
    if (contextData.first->CanAttributeDefaultValueChangeAffectFileFormatArguments(
            attributeName, oldValue, newValue, contextData.second))
    {
      return true;
    }
  }
  return false;
}

const TfToken::Set &PcpDynamicFileFormatDependencyData::GetRelevantFieldNames() const
{
  static const TfToken::Set empty;
  return _data ? _data->relevantFieldNames : empty;
}

const TfToken::Set &PcpDynamicFileFormatDependencyData::GetRelevantAttributeNames() const
{
  static const TfToken::Set empty;
  return _data ? _data->relevantAttributeNames : empty;
}

void PcpDynamicFileFormatDependencyData::_Data::_AddRelevantFieldNames(TfToken::Set &&fieldNames)
{
  // Avoid copying if our current relevant fields list is empty.
  if (relevantFieldNames.empty()) {
    relevantFieldNames.swap(fieldNames);
  }
  else {
    relevantFieldNames.insert(std::make_move_iterator(fieldNames.begin()),
                              std::make_move_iterator(fieldNames.end()));
  }
}

void PcpDynamicFileFormatDependencyData::_Data::_AddRelevantAttributeNames(
    TfToken::Set &&attributeNames)
{
  // Avoid copying if our current relevant fields list is empty.
  if (relevantAttributeNames.empty()) {
    relevantAttributeNames.swap(attributeNames);
  }
  else {
    relevantAttributeNames.insert(std::make_move_iterator(attributeNames.begin()),
                                  std::make_move_iterator(attributeNames.end()));
  }
}

PXR_NAMESPACE_CLOSE_SCOPE
