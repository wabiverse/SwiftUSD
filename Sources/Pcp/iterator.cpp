//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Pcp/iterator.h"
#include "Pcp/arc.h"
#include "Pcp/primIndex.h"
#include "Pcp/primIndex_Graph.h"
#include "Pcp/propertyIndex.h"
#include "Pcp/types.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

////////////////////////////////////////////////////////////

PcpPrimIterator::PcpPrimIterator() = default;

PcpPrimIterator::PcpPrimIterator(const PcpPrimIndex *primIndex, size_t pos)
    : _primIndex(primIndex), _pos(pos)
{
  // Do nothing
}

void PcpPrimIterator::increment()
{
  if (!_primIndex) {
    TF_CODING_ERROR("Cannot increment invalid iterator");
    return;
  }

  ++_pos;
}

void PcpPrimIterator::decrement()
{
  if (!_primIndex) {
    TF_CODING_ERROR("Cannot decrement invalid iterator");
    return;
  }

  --_pos;
}

void PcpPrimIterator::advance(difference_type n)
{
  if (!_primIndex) {
    TF_CODING_ERROR("Cannot advance invalid iterator");
    return;
  }

  _pos += n;
}

PcpPrimIterator::difference_type PcpPrimIterator::distance_to(const PcpPrimIterator &other) const
{
  if (!_primIndex || !other._primIndex) {
    TF_CODING_ERROR("Invalid iterator");
    return 0;
  }

  if (_primIndex != other._primIndex) {
    TF_CODING_ERROR(
        "Cannot compute distance for iterators "
        "from different prim indexes.");
    return 0;
  }

  return (difference_type)(other._pos) - _pos;
}

bool PcpPrimIterator::equal(const PcpPrimIterator &other) const
{
  return _primIndex == other._primIndex && _pos == other._pos;
}

PcpPrimIterator::reference PcpPrimIterator::dereference() const
{
  return _primIndex->_graph->GetSdSite(_primIndex->_primStack[_pos]);
}

PcpNodeRef PcpPrimIterator::GetNode() const
{
  return _primIndex->_graph->GetNode(_primIndex->_primStack[_pos]);
}

Pcp_SdSiteRef PcpPrimIterator::_GetSiteRef() const
{
  return _primIndex->_graph->GetSiteRef(_primIndex->_primStack[_pos]);
}

////////////////////////////////////////////////////////////

PcpPropertyIterator::PcpPropertyIterator() = default;

PcpPropertyIterator::PcpPropertyIterator(const PcpPropertyIndex &index, size_t pos)
    : _propertyIndex(&index), _pos(pos)
{
}

void PcpPropertyIterator::increment()
{
  if (!_propertyIndex) {
    TF_CODING_ERROR("Cannot increment invalid iterator");
    return;
  }

  ++_pos;
}

void PcpPropertyIterator::decrement()
{
  if (!_propertyIndex) {
    TF_CODING_ERROR("Cannot decrement invalid iterator");
    return;
  }

  --_pos;
}

void PcpPropertyIterator::advance(difference_type n)
{
  if (!_propertyIndex) {
    TF_CODING_ERROR("Cannot advance invalid iterator");
    return;
  }

  _pos += n;
}

PcpPropertyIterator::difference_type PcpPropertyIterator::distance_to(
    const PcpPropertyIterator &other) const
{
  if (!_propertyIndex || !other._propertyIndex) {
    TF_CODING_ERROR("Invalid iterator");
    return 0;
  }

  if (_propertyIndex != other._propertyIndex) {
    TF_CODING_ERROR(
        "Cannot compute distance for iterators "
        "from different property indexes");
    return 0;
  }

  return (difference_type)(other._pos) - _pos;
}

bool PcpPropertyIterator::equal(const PcpPropertyIterator &other) const
{
  return _propertyIndex == other._propertyIndex && _pos == other._pos;
}

PcpPropertyIterator::reference PcpPropertyIterator::dereference() const
{
  return _propertyIndex->_propertyStack[_pos].propertySpec;
}

PcpNodeRef PcpPropertyIterator::GetNode() const
{
  return _propertyIndex->_propertyStack[_pos].originatingNode;
}

bool PcpPropertyIterator::IsLocal() const
{
  return _pos < _propertyIndex->GetNumLocalSpecs();
}

PXR_NAMESPACE_CLOSE_SCOPE
