//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/textureBinder.h"
#include "Gf/matrix4f.h"
#include "Hd/vtBufferSource.h"
#include "HdSt/ptexTextureObject.h"
#include "HdSt/resourceBinder.h"
#include "HdSt/samplerObject.h"
#include "HdSt/textureHandle.h"
#include "HdSt/textureObject.h"
#include "HdSt/udimTextureObject.h"

PXR_NAMESPACE_OPEN_SCOPE

static const HdTupleType _bindlessHandleTupleType{HdTypeUInt32Vec2, 1};

static TfToken _Concat(const TfToken &a, const TfToken &b)
{
  return TfToken(a.GetString() + b.GetString());
}

void HdSt_TextureBinder::GetBufferSpecs(const NamedTextureHandleVector &textures,
                                        HdBufferSpecVector *const specs,
                                        bool doublesSupported)
{
  const bool useBindlessHandles = textures.empty() ? false :
                                                     textures[0].handle->UseBindlessHandles();

  for (const NamedTextureHandle &texture : textures) {
    switch (texture.type) {
      case HdStTextureType::Uv:
        if (useBindlessHandles) {
          specs->emplace_back(texture.name, _bindlessHandleTupleType);
        }
        specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->valid),
                            HdTupleType{HdTypeBool, 1});
        break;
      case HdStTextureType::Field:
        if (useBindlessHandles) {
          specs->emplace_back(texture.name, _bindlessHandleTupleType);
        }
        specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->valid),
                            HdTupleType{HdTypeBool, 1});
        specs->emplace_back(
            _Concat(texture.name, HdSt_ResourceBindingSuffixTokens->samplingTransform),
            HdTupleType{(doublesSupported ? HdTypeDoubleMat4 : HdTypeFloatMat4), 1});
        break;
      case HdStTextureType::Ptex:
        if (useBindlessHandles) {
          specs->emplace_back(texture.name, _bindlessHandleTupleType);
          specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->layout),
                              _bindlessHandleTupleType);
        }
        specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->valid),
                            HdTupleType{HdTypeBool, 1});
        break;
      case HdStTextureType::Udim:
        if (useBindlessHandles) {
          specs->emplace_back(texture.name, _bindlessHandleTupleType);
          specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->layout),
                              _bindlessHandleTupleType);
        }
        specs->emplace_back(_Concat(texture.name, HdSt_ResourceBindingSuffixTokens->valid),
                            HdTupleType{HdTypeBool, 1});
        break;
    }
  }
}

namespace {

// A bindless GL sampler buffer.
// This identifies a texture as a 64-bit handle, passed to GLSL as "uvec2".
// See https://www.khronos.org/opengl/wiki/Bindless_Texture
class HdSt_BindlessSamplerBufferSource : public HdBufferSource {
 public:
  HdSt_BindlessSamplerBufferSource(TfToken const &name, const uint64_t value)
      : HdBufferSource(), _name(name), _value(value)
  {
  }

  ~HdSt_BindlessSamplerBufferSource() override = default;

  TfToken const &GetName() const override
  {
    return _name;
  }
  void const *GetData() const override
  {
    return &_value;
  }
  HdTupleType GetTupleType() const override
  {
    return _bindlessHandleTupleType;
  }
  size_t GetNumElements() const override
  {
    return 1;
  }
  void GetBufferSpecs(HdBufferSpecVector *specs) const override
  {
    specs->emplace_back(_name, GetTupleType());
  }
  bool Resolve() override
  {
    if (!_TryLock())
      return false;
    _SetResolved();
    return true;
  }

 protected:
  bool _CheckValid() const override
  {
    return true;
  }

 private:
  const TfToken _name;
  const uint64_t _value;
};

class _ComputeBufferSourcesFunctor {
 public:
  static void Compute(TfToken const &name,
                      HdStUvTextureObject const &texture,
                      HdStUvSamplerObject const &sampler,
                      HdBufferSourceSharedPtrVector *const sources,
                      bool useBindlessHandles,
                      bool doublesSupported)
  {
    if (useBindlessHandles) {
      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          name,
          HdSt_ResourceBinder::GetSamplerBindlessHandle(sampler.GetSampler(),
                                                        texture.GetTexture())));
    }

    sources->push_back(std::make_shared<HdVtBufferSource>(
        _Concat(name, HdSt_ResourceBindingSuffixTokens->valid), VtValue(texture.IsValid())));
  }

  static void Compute(TfToken const &name,
                      HdStFieldTextureObject const &texture,
                      HdStFieldSamplerObject const &sampler,
                      HdBufferSourceSharedPtrVector *const sources,
                      bool useBindlessHandles,
                      bool doublesSupported)
  {
    if (useBindlessHandles) {
      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          name,
          HdSt_ResourceBinder::GetSamplerBindlessHandle(sampler.GetSampler(),
                                                        texture.GetTexture())));
    }
    sources->push_back(std::make_shared<HdVtBufferSource>(
        _Concat(name, HdSt_ResourceBindingSuffixTokens->valid), VtValue(texture.IsValid())));
    sources->push_back(std::make_shared<HdVtBufferSource>(
        _Concat(name, HdSt_ResourceBindingSuffixTokens->samplingTransform),
        VtValue(texture.GetSamplingTransform()),
        1,
        doublesSupported));
  }

  static void Compute(TfToken const &name,
                      HdStPtexTextureObject const &texture,
                      HdStPtexSamplerObject const &sampler,
                      HdBufferSourceSharedPtrVector *const sources,
                      bool useBindlessHandles,
                      bool doublesSupported)
  {
    if (useBindlessHandles) {
      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          name,
          HdSt_ResourceBinder::GetSamplerBindlessHandle(sampler.GetTexelsSampler(),
                                                        texture.GetTexelTexture())));

      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          _Concat(name, HdSt_ResourceBindingSuffixTokens->layout),
          HdSt_ResourceBinder::GetTextureBindlessHandle(texture.GetLayoutTexture())));
    }
    sources->push_back(std::make_shared<HdVtBufferSource>(
        _Concat(name, HdSt_ResourceBindingSuffixTokens->valid), VtValue(texture.IsValid())));
  }

  static void Compute(TfToken const &name,
                      HdStUdimTextureObject const &texture,
                      HdStUdimSamplerObject const &sampler,
                      HdBufferSourceSharedPtrVector *const sources,
                      bool useBindlessHandles,
                      bool doublesSupported)
  {
    if (useBindlessHandles) {
      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          name,
          HdSt_ResourceBinder::GetSamplerBindlessHandle(sampler.GetTexelsSampler(),
                                                        texture.GetTexelTexture())));

      sources->push_back(std::make_shared<HdSt_BindlessSamplerBufferSource>(
          _Concat(name, HdSt_ResourceBindingSuffixTokens->layout),
          HdSt_ResourceBinder::GetTextureBindlessHandle(texture.GetLayoutTexture())));
    }
    sources->push_back(std::make_shared<HdVtBufferSource>(
        _Concat(name, HdSt_ResourceBindingSuffixTokens->valid), VtValue(texture.IsValid())));
  }
};

class _BindFunctor {
 public:
  static void Compute(TfToken const &name,
                      HdStUvTextureObject const &texture,
                      HdStUvSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      const bool bind)
  {
    binder.BindTexture(name, sampler.GetSampler(), texture.GetTexture(), bind);
  }

  static void Compute(TfToken const &name,
                      HdStFieldTextureObject const &texture,
                      HdStFieldSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      const bool bind)
  {
    binder.BindTexture(name, sampler.GetSampler(), texture.GetTexture(), bind);
  }

  static void Compute(TfToken const &name,
                      HdStPtexTextureObject const &texture,
                      HdStPtexSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      const bool bind)
  {
    binder.BindTextureWithLayout(name,
                                 sampler.GetTexelsSampler(),
                                 texture.GetTexelTexture(),
                                 sampler.GetLayoutSampler(),
                                 texture.GetLayoutTexture(),
                                 bind);
  }

  static void Compute(TfToken const &name,
                      HdStUdimTextureObject const &texture,
                      HdStUdimSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      const bool bind)
  {
    binder.BindTextureWithLayout(name,
                                 sampler.GetTexelsSampler(),
                                 texture.GetTexelTexture(),
                                 sampler.GetLayoutSampler(),
                                 texture.GetLayoutTexture(),
                                 bind);
  }
};

class _BindingDescsFunctor {
 public:
  static void Compute(TfToken const &name,
                      HdStUvTextureObject const &texture,
                      HdStUvSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      HgiResourceBindingsDesc *bindingsDesc)
  {
    binder.GetTextureBindingDesc(bindingsDesc, name, sampler.GetSampler(), texture.GetTexture());
  }

  static void Compute(TfToken const &name,
                      HdStFieldTextureObject const &texture,
                      HdStFieldSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      HgiResourceBindingsDesc *bindingsDesc)
  {
    binder.GetTextureBindingDesc(bindingsDesc, name, sampler.GetSampler(), texture.GetTexture());
  }

  static void Compute(TfToken const &name,
                      HdStPtexTextureObject const &texture,
                      HdStPtexSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      HgiResourceBindingsDesc *bindingsDesc)
  {
    binder.GetTextureWithLayoutBindingDesc(bindingsDesc,
                                           name,
                                           sampler.GetTexelsSampler(),
                                           texture.GetTexelTexture(),
                                           sampler.GetLayoutSampler(),
                                           texture.GetLayoutTexture());
  }

  static void Compute(TfToken const &name,
                      HdStUdimTextureObject const &texture,
                      HdStUdimSamplerObject const &sampler,
                      HdSt_ResourceBinder const &binder,
                      HgiResourceBindingsDesc *bindingsDesc)
  {
    binder.GetTextureWithLayoutBindingDesc(bindingsDesc,
                                           name,
                                           sampler.GetTexelsSampler(),
                                           texture.GetTexelTexture(),
                                           sampler.GetLayoutSampler(),
                                           texture.GetLayoutTexture());
  }
};

template<HdStTextureType textureType, class Functor, typename... Args>
void _CastAndCompute(HdStShaderCode::NamedTextureHandle const &namedTextureHandle, Args &&...args)
{
  // e.g. HdStUvTextureObject
  using TextureObject = HdStTypedTextureObject<textureType>;
  // e.g. HdStUvSamplerObject
  using SamplerObject = HdStTypedSamplerObject<textureType>;

  if (!namedTextureHandle.handle) {
    TF_CODING_ERROR("Invalid texture handle in texture binder.");
    return;
  }

  const TextureObject *const typedTexture = dynamic_cast<TextureObject *>(
      namedTextureHandle.handle->GetTextureObject().get());
  if (!typedTexture) {
    TF_CODING_ERROR("Bad texture object");
    return;
  }

  const SamplerObject *const typedSampler = dynamic_cast<SamplerObject *>(
      namedTextureHandle.handle->GetSamplerObject().get());
  if (!typedSampler) {
    TF_CODING_ERROR("Bad sampler object");
    return;
  }

  Functor::Compute(
      namedTextureHandle.name, *typedTexture, *typedSampler, std::forward<Args>(args)...);
}

template<class Functor, typename... Args>
void _Dispatch(HdStShaderCode::NamedTextureHandle const &namedTextureHandle, Args &&...args)
{
  switch (namedTextureHandle.type) {
    case HdStTextureType::Uv:
      _CastAndCompute<HdStTextureType::Uv, Functor>(namedTextureHandle,
                                                    std::forward<Args>(args)...);
      break;
    case HdStTextureType::Field:
      _CastAndCompute<HdStTextureType::Field, Functor>(namedTextureHandle,
                                                       std::forward<Args>(args)...);
      break;
    case HdStTextureType::Ptex:
      _CastAndCompute<HdStTextureType::Ptex, Functor>(namedTextureHandle,
                                                      std::forward<Args>(args)...);
      break;
    case HdStTextureType::Udim:
      _CastAndCompute<HdStTextureType::Udim, Functor>(namedTextureHandle,
                                                      std::forward<Args>(args)...);
      break;
  }
}

template<class Functor, typename... Args>
void _Dispatch(HdStShaderCode::NamedTextureHandleVector const &textures, Args &&...args)
{
  for (const HdStShaderCode::NamedTextureHandle &texture : textures) {
    _Dispatch<Functor>(texture, std::forward<Args>(args)...);
  }
}

}  // end anonymous namespace

void HdSt_TextureBinder::ComputeBufferSources(const NamedTextureHandleVector &textures,
                                              HdBufferSourceSharedPtrVector *const sources,
                                              bool doublesSupported)
{
  const bool useBindlessHandles = textures.empty() ? false :
                                                     textures[0].handle->UseBindlessHandles();

  _Dispatch<_ComputeBufferSourcesFunctor>(textures, sources, useBindlessHandles, doublesSupported);
}

void HdSt_TextureBinder::BindResources(HdSt_ResourceBinder const &binder,
                                       const NamedTextureHandleVector &textures)
{
  _Dispatch<_BindFunctor>(textures, binder, /* bind = */ true);
}

void HdSt_TextureBinder::UnbindResources(HdSt_ResourceBinder const &binder,
                                         const NamedTextureHandleVector &textures)
{
  _Dispatch<_BindFunctor>(textures, binder, /* bind = */ false);
}

void HdSt_TextureBinder::GetBindingDescs(HdSt_ResourceBinder const &binder,
                                         HgiResourceBindingsDesc *bindingsDesc,
                                         const NamedTextureHandleVector &textures)
{
  _Dispatch<_BindingDescsFunctor>(textures, binder, bindingsDesc);
}

PXR_NAMESPACE_CLOSE_SCOPE
