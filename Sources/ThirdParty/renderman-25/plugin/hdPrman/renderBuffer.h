//
// Copyright 2019 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_RENDER_BUFFER_H
#define EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_RENDER_BUFFER_H

#include "Hd/renderBuffer.h"
#include <pxr/pxrns.h>

PXR_NAMESPACE_OPEN_SCOPE

class HdPrmanRenderBuffer : public HdRenderBuffer {
 public:
  HdPrmanRenderBuffer(SdfPath const &id);
  ~HdPrmanRenderBuffer() override;

  bool Allocate(GfVec3i const &dimensions, HdFormat format, bool multiSampled) override;

  unsigned int GetWidth() const override
  {
    return _width;
  }
  unsigned int GetHeight() const override
  {
    return _height;
  }
  unsigned int GetDepth() const override
  {
    return 1;
  }
  HdFormat GetFormat() const override
  {
    return _format;
  }

  // HdPrman doesn't handle sampling decisions at the hydra level.
  bool IsMultiSampled() const override
  {
    return false;
  }

  void *Map() override
  {
    _mappers++;
    return _buffer.data();
  }
  void Unmap() override
  {
    _mappers--;
  }
  bool IsMapped() const override
  {
    return _mappers.load() != 0;
  }

  bool IsConverged() const override
  {
    return _converged.load();
  }
  void SetConverged(bool cv)
  {
    _converged.store(cv);
  }

  void Resolve() override {}

  // ---------------------------------------------------------------------- //
  /// \name I/O helpers
  // ---------------------------------------------------------------------- //

  // format is the input format.
  void Blit(HdFormat format, int width, int height, uint8_t const *data);

 private:
  static size_t _GetBufferSize(GfVec2i const &dims, HdFormat format);

  void _Deallocate() override;

  unsigned int _width;
  unsigned int _height;
  HdFormat _format;

  std::vector<uint8_t> _buffer;
  std::atomic<int> _mappers;
  std::atomic<bool> _converged;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // EXT_RMANPKG_25_0_PLUGIN_RENDERMAN_PLUGIN_HD_PRMAN_RENDER_BUFFER_H
