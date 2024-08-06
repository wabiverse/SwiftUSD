//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file texture.cpp
#include "Glf/texture.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"

#include <climits>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<GlfTexture>();
}

TF_DEFINE_PUBLIC_TOKENS(GlfTextureTokens, GLF_TEXTURE_TOKENS);

static size_t _TextureMemoryAllocated = 0;
static size_t _TextureContentsID = 0;

static size_t _GetNewContentsID()
{
  return ++_TextureContentsID;
}

GlfTexture::GlfTexture()
    : _memoryUsed(0),
      _memoryRequested(INT_MAX),
      _contentsID(_GetNewContentsID()),
      _originLocation(HioImage::OriginUpperLeft)
{
}

GlfTexture::GlfTexture(HioImage::ImageOriginLocation originLocation)
    : _memoryUsed(0),
      _memoryRequested(INT_MAX),
      _contentsID(_GetNewContentsID()),
      _originLocation(originLocation)
{
}

GlfTexture::~GlfTexture()
{
  _TextureMemoryAllocated -= _memoryUsed;
}

size_t GlfTexture::GetMemoryRequested() const
{
  return _memoryRequested;
}

void GlfTexture::SetMemoryRequested(size_t targetMemory)
{
  if (_memoryRequested != targetMemory) {
    _memoryRequested = targetMemory;
    _OnMemoryRequestedDirty();
  }
}

void GlfTexture::_OnMemoryRequestedDirty()
{
  // do nothing in base class
}

size_t GlfTexture::GetMemoryUsed() const
{
  return _memoryUsed;
}

void GlfTexture::_SetMemoryUsed(size_t s)
{
  _TextureMemoryAllocated += s - _memoryUsed;

  _memoryUsed = s;
}

bool GlfTexture::IsMinFilterSupported(GLenum filter)
{
  return true;
}

bool GlfTexture::IsMagFilterSupported(GLenum filter)
{
  return true;
}

size_t GlfTexture::GetTextureMemoryAllocated()
{
  return _TextureMemoryAllocated;
}

size_t GlfTexture::GetContentsID() const
{
  return _contentsID;
}

void GlfTexture::_UpdateContentsID()
{
  _contentsID = _GetNewContentsID();
}

HioImage::ImageOriginLocation GlfTexture::GetOriginLocation() const
{
  return _originLocation;
}

bool GlfTexture::IsOriginLowerLeft() const
{
  return _originLocation == HioImage::OriginLowerLeft;
}

PXR_NAMESPACE_CLOSE_SCOPE
