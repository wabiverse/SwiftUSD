//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file simpleLight.cpp

#include "Glf/simpleLight.h"

#include "Garch/glApi.h"

PXR_NAMESPACE_OPEN_SCOPE

GlfSimpleLight::GlfSimpleLight(GfVec4f const &position)
    : _ambient(0.2, 0.2, 0.2, 1.0),
      _diffuse(1.0, 1.0, 1.0, 1.0),
      _specular(1.0, 1.0, 1.0, 1.0),
      _position(position[0], position[1], position[2], 1.0),
      _spotDirection(0.0, 0.0, -1.0),
      _spotCutoff(180.0),
      _spotFalloff(0.0),
      _attenuation(1.0, 0.0, 0.0),
      _isCameraSpaceLight(false),
      _hasIntensity(true),
      _hasShadow(false),
      _shadowResolution(512),
      _shadowBias(0.0),
      _shadowBlur(0.0),
      _shadowIndexStart(0),
      _shadowIndexEnd(0),
      _transform(GfMatrix4d().SetIdentity()),
      _shadowMatrices(std::vector<GfMatrix4d>(1, GfMatrix4d().SetIdentity())),
      _isDomeLight(false),
      _id()
{
}

GlfSimpleLight::~GlfSimpleLight() = default;

GfMatrix4d const &GlfSimpleLight::GetTransform() const
{
  return _transform;
}

void GlfSimpleLight::SetTransform(GfMatrix4d const &mat)
{
  _transform = mat;
}

GfVec4f const &GlfSimpleLight::GetAmbient() const
{
  return _ambient;
}

void GlfSimpleLight::SetAmbient(GfVec4f const &ambient)
{
  _ambient = ambient;
}

GfVec4f const &GlfSimpleLight::GetDiffuse() const
{
  return _diffuse;
}

void GlfSimpleLight::SetDiffuse(GfVec4f const &diffuse)
{
  _diffuse = diffuse;
}

GfVec4f const &GlfSimpleLight::GetSpecular() const
{
  return _specular;
}

void GlfSimpleLight::SetSpecular(GfVec4f const &specular)
{
  _specular = specular;
}

GfVec4f const &GlfSimpleLight::GetPosition() const
{
  return _position;
}

void GlfSimpleLight::SetPosition(GfVec4f const &position)
{
  _position = position;
}

GfVec3f const &GlfSimpleLight::GetSpotDirection() const
{
  return _spotDirection;
}

void GlfSimpleLight::SetSpotDirection(GfVec3f const &spotDirection)
{
  _spotDirection = spotDirection;
}

float const &GlfSimpleLight::GetSpotCutoff() const
{
  return _spotCutoff;
}

void GlfSimpleLight::SetSpotCutoff(float const &spotCutoff)
{
  _spotCutoff = spotCutoff;
}

float const &GlfSimpleLight::GetSpotFalloff() const
{
  return _spotFalloff;
}

void GlfSimpleLight::SetSpotFalloff(float const &spotFalloff)
{
  _spotFalloff = spotFalloff;
}

GfVec3f const &GlfSimpleLight::GetAttenuation() const
{
  return _attenuation;
}

void GlfSimpleLight::SetAttenuation(GfVec3f const &attenuation)
{
  _attenuation = attenuation;
}

void GlfSimpleLight::SetHasIntensity(bool hasIntensity)
{
  _hasIntensity = hasIntensity;
}

bool GlfSimpleLight::HasIntensity() const
{
  return _hasIntensity;
}

bool GlfSimpleLight::HasShadow() const
{
  return _hasShadow;
}

void GlfSimpleLight::SetHasShadow(bool hasShadow)
{
  _hasShadow = hasShadow;
}

int GlfSimpleLight::GetShadowResolution() const
{
  return _shadowResolution;
}

void GlfSimpleLight::SetShadowResolution(int resolution)
{
  _shadowResolution = resolution;
}

float GlfSimpleLight::GetShadowBias() const
{
  return _shadowBias;
}

void GlfSimpleLight::SetShadowBias(float bias)
{
  _shadowBias = bias;
}

float GlfSimpleLight::GetShadowBlur() const
{
  return _shadowBlur;
}

void GlfSimpleLight::SetShadowBlur(float blur)
{
  _shadowBlur = blur;
}

int GlfSimpleLight::GetShadowIndexStart() const
{
  return _shadowIndexStart;
}

void GlfSimpleLight::SetShadowIndexStart(int shadowStart)
{
  _shadowIndexStart = shadowStart;
}

int GlfSimpleLight::GetShadowIndexEnd() const
{
  return _shadowIndexEnd;
}

void GlfSimpleLight::SetShadowIndexEnd(int shadowEnd)
{
  _shadowIndexEnd = shadowEnd;
}

std::vector<GfMatrix4d> const &GlfSimpleLight::GetShadowMatrices() const
{
  return _shadowMatrices;
}

void GlfSimpleLight::SetShadowMatrices(std::vector<GfMatrix4d> const &matrices)
{
  _shadowMatrices = matrices;
}

bool GlfSimpleLight::IsCameraSpaceLight() const
{
  return _isCameraSpaceLight;
}

void GlfSimpleLight::SetIsCameraSpaceLight(bool isCameraSpaceLight)
{
  _isCameraSpaceLight = isCameraSpaceLight;
}

SdfPath const &GlfSimpleLight::GetID() const
{
  return _id;
}

void GlfSimpleLight::SetID(SdfPath const &id)
{
  _id = id;
}

bool GlfSimpleLight::IsDomeLight() const
{
  return _isDomeLight;
}

void GlfSimpleLight::SetIsDomeLight(bool isDomeLight)
{
  _isDomeLight = isDomeLight;
}

const SdfAssetPath &GlfSimpleLight::GetDomeLightTextureFile() const
{
  return _domeLightTextureFile;
}

void GlfSimpleLight::SetDomeLightTextureFile(const SdfAssetPath &path)
{
  _domeLightTextureFile = path;
}

TfToken const &GlfSimpleLight::GetPostSurfaceIdentifier() const
{
  return _postSurfaceIdentifier;
}

std::string const &GlfSimpleLight::GetPostSurfaceShaderSource() const
{
  return _postSurfaceShaderSource;
}

VtUCharArray const &GlfSimpleLight::GetPostSurfaceShaderParams() const
{
  return _postSurfaceShaderParams;
}

void GlfSimpleLight::SetPostSurfaceParams(TfToken const &identifier,
                                          std::string const &shaderSource,
                                          VtUCharArray const &shaderParams)
{
  _postSurfaceIdentifier = identifier;
  _postSurfaceShaderSource = shaderSource;
  _postSurfaceShaderParams = shaderParams;
}

// -------------------------------------------------------------------------- //
// VtValue requirements
// -------------------------------------------------------------------------- //

bool GlfSimpleLight::operator==(const GlfSimpleLight &other) const
{
  return _ambient == other._ambient && _diffuse == other._diffuse &&
         _specular == other._specular && _position == other._position &&
         _spotDirection == other._spotDirection && _spotCutoff == other._spotCutoff &&
         _spotFalloff == other._spotFalloff && _attenuation == other._attenuation &&
         _hasIntensity == other._hasIntensity && _hasShadow == other._hasShadow &&
         _shadowResolution == other._shadowResolution && _shadowBias == other._shadowBias &&
         _shadowBlur == other._shadowBlur && _shadowIndexStart == other._shadowIndexStart &&
         _shadowIndexEnd == other._shadowIndexEnd && _transform == other._transform &&
         _shadowMatrices == other._shadowMatrices &&
         _isCameraSpaceLight == other._isCameraSpaceLight && _isDomeLight == other._isDomeLight &&
         _domeLightTextureFile == other._domeLightTextureFile &&
         _postSurfaceIdentifier == other._postSurfaceIdentifier &&
         _postSurfaceShaderSource == other._postSurfaceShaderSource &&
         _postSurfaceShaderParams == other._postSurfaceShaderParams && _id == other._id;
}

bool GlfSimpleLight::operator!=(const GlfSimpleLight &other) const
{
  return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const GlfSimpleLight &v)
{
  out << v._ambient << v._diffuse << v._specular << v._position << v._spotDirection
      << v._spotCutoff << v._spotFalloff << v._attenuation << v._hasIntensity << v._hasShadow
      << v._shadowResolution << v._shadowBias << v._shadowBlur << v._shadowIndexStart
      << v._shadowIndexEnd << v._transform << v._isCameraSpaceLight << v._isDomeLight
      << v._domeLightTextureFile << v._postSurfaceIdentifier << v._postSurfaceShaderSource
      << v._postSurfaceShaderParams << v._id;
  for (auto const &m : v._shadowMatrices) {
    out << m;
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const GlfSimpleLightVector &pv)
{
  return out;
}

GlfSimpleLightCollector::GlfSimpleLightCollector()
  : _lights()
{}

void GlfSimpleLightCollector::clear()
{
  _lights.clear();
}

// static
GlfSimpleLight GlfSimpleLightCollector::createLight(const GfVec4f &position)
{
  GlfSimpleLight simpleLight;
  simpleLight.SetPosition(position);
  return simpleLight;
}

void GlfSimpleLightCollector::addLight(GlfSimpleLight const &light)
{
  _lights.push_back(light);
}

void GlfSimpleLightCollector::addLight(GlfSimpleLight &&light)
{
  _lights.push_back(std::move(light));
}

GlfSimpleLightVector GlfSimpleLightCollector::getLights() const
{
  return _lights;
}

PXR_NAMESPACE_CLOSE_SCOPE
