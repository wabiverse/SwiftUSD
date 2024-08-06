//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
///
/// \file Tf/TemplateString.cpp

#include "pxr/pxrns.h"

#include "Tf/iterator.h"
#include "Tf/stringUtils.h"
#include "Tf/templateString.h"

using std::string;
using std::vector;

PXR_NAMESPACE_OPEN_SCOPE

#define _ERROR(ptr, ...) \
  if (ptr) { \
    ptr->push_back(TfStringPrintf(__VA_ARGS__)); \
  }

static const char _Sigil = '$';
static const char _OpenQuote = '{';
static const char _CloseQuote = '}';

static const char *const _IdentChars =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789_";

TfTemplateString::TfTemplateString() : _data(new _Data) {}

TfTemplateString::TfTemplateString(const string &template_) : _data(new _Data)
{
  _data->template_ = template_;
}

string TfTemplateString::Substitute(const Mapping &mapping) const
{
  _ParseTemplate();
  _EmitParseErrors();

  vector<string> evalErrors;
  string result = _Evaluate(mapping, &evalErrors);

  TF_FOR_ALL(it, evalErrors)
  TF_CODING_ERROR("%s", it->c_str());

  return result;
}

string TfTemplateString::SafeSubstitute(const Mapping &mapping) const
{
  _ParseTemplate();
  _EmitParseErrors();
  return _Evaluate(mapping);
}

void TfTemplateString::_EmitParseErrors() const
{
  tbb::spin_mutex::scoped_lock lock(_data->mutex);
  TF_FOR_ALL(it, _data->parseErrors)
  TF_CODING_ERROR("%s", it->c_str());
}

TfTemplateString::Mapping TfTemplateString::GetEmptyMapping() const
{
  Mapping mapping;
  if (IsValid()) {
    tbb::spin_mutex::scoped_lock lock(_data->mutex);
    TF_FOR_ALL(it, _data->placeholders)
    mapping.insert(make_pair(it->name, std::string()));
  }
  return mapping;
}

bool TfTemplateString::IsValid() const
{
  _ParseTemplate();
  tbb::spin_mutex::scoped_lock lock(_data->mutex);
  return _data->template_.empty() || _data->parseErrors.empty();
}

vector<string> TfTemplateString::GetParseErrors() const
{
  _ParseTemplate();
  tbb::spin_mutex::scoped_lock lock(_data->mutex);
  return _data->parseErrors;
}

// XXX NOTE: callers must hold a lock on _data->mutex before calling
// _FindNextPlaceHolder.
bool TfTemplateString::_FindNextPlaceHolder(size_t *pos, vector<string> *errors) const
{
  *pos = _data->template_.find(_Sigil, *pos);

  if (*pos == string::npos)
    return false;

  size_t nextpos = *pos + 1;
  if (nextpos >= _data->template_.length())
    return false;

  if (_data->template_[nextpos] == _Sigil) {
    // This is a $$ escape sequence.
    _data->placeholders.push_back(_PlaceHolder("$", *pos, 2));
    *pos = *pos + 2;
  }
  else if (_data->template_[nextpos] == _OpenQuote) {
    // If the character after the sigil was the open quote character, look
    // for the matching close quote character.
    size_t endpos = _data->template_.find_first_not_of(string(_IdentChars) + _OpenQuote, nextpos);

    if (endpos == string::npos) {
      _ERROR(errors,
             "Cannot find close quote for placeholder starting "
             "at pos %zu",
             *pos);
      *pos = nextpos;
    }
    else if (_data->template_[endpos] != _CloseQuote) {
      _ERROR(errors,
             "Invalid character '%c' in identifier at pos %zu",
             _data->template_[endpos],
             endpos);
      *pos = endpos;
    }
    else {
      // len includes the sigil and quote characters.
      size_t len = endpos - *pos + 1;
      string name = _data->template_.substr(nextpos + 1, len - 3);
      if (!name.empty()) {
        _data->placeholders.push_back(_PlaceHolder(name, *pos, len));
      }
      else {
        _ERROR(errors, "Empty placeholder at pos %zu", *pos);
      }
      *pos = *pos + len;
    }
  }
  else {
    // Find the next character not valid within an identifier.
    size_t endpos = _data->template_.find_first_not_of(_IdentChars, nextpos);
    size_t len = (endpos == string::npos ? _data->template_.length() : endpos) - *pos;
    string name = _data->template_.substr(nextpos, len - 1);
    if (!name.empty()) {
      _data->placeholders.push_back(_PlaceHolder(name, *pos, len));
    }
    else {
      // If we find what appears to be a place holder, but the next
      // character is not legal in a place holder, we just skip it.
    }
    *pos = *pos + len;
  }

  return true;
}

void TfTemplateString::_ParseTemplate() const
{
  tbb::spin_mutex::scoped_lock lock(_data->mutex);
  if (!_data->parsed) {
    size_t pos = 0;
    while (_FindNextPlaceHolder(&pos, &_data->parseErrors))
      ;
    _data->parsed = true;
  }
}

string TfTemplateString::_Evaluate(const Mapping &mapping, vector<string> *errors) const
{
  string result;
  size_t pos = 0;

  tbb::spin_mutex::scoped_lock lock(_data->mutex);

  TF_FOR_ALL(it, _data->placeholders)
  {
    // Add template content between the end of the last placeholder (or
    // the start of the template) and the start of the next placeholder.
    result.insert(
        result.end(), _data->template_.begin() + pos, _data->template_.begin() + it->pos);

    if (it->name[0] == _Sigil) {
      result.insert(result.end(), _Sigil);
    }
    else {
      Mapping::const_iterator mit = mapping.find(it->name);
      if (mit != mapping.end()) {
        result.insert(result.end(), mit->second.begin(), mit->second.end());
      }
      else {
        // Insert the placeholder into the result.
        result.insert(result.end(),
                      _data->template_.begin() + it->pos,
                      _data->template_.begin() + it->pos + it->len);
        _ERROR(errors, "No mapping found for placeholder '%s'", it->name.c_str());
      }
    }

    pos = it->pos + it->len;
  }

  // Add the remainder of the template string.
  result += _data->template_.substr(pos);

  return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
