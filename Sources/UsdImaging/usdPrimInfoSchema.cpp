//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* **                                                                      ** */
/* ** This file is generated by a script.                                  ** */
/* **                                                                      ** */
/* ** Do not edit it directly (unless it is within a CUSTOM CODE section)! ** */
/* ** Edit hdSchemaDefs.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#include "UsdImaging/usdPrimInfoSchema.h"

#include "Hd/retainedDataSource.h"

#include "Trace/traceImpl.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(UsdImagingUsdPrimInfoSchemaTokens,
                        USD_IMAGING_USD_PRIM_INFO_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdPathDataSourceHandle UsdImagingUsdPrimInfoSchema::GetNiPrototypePath() const
{
  return _GetTypedDataSource<HdPathDataSource>(UsdImagingUsdPrimInfoSchemaTokens->niPrototypePath);
}

HdBoolDataSourceHandle UsdImagingUsdPrimInfoSchema::GetIsNiPrototype() const
{
  return _GetTypedDataSource<HdBoolDataSource>(UsdImagingUsdPrimInfoSchemaTokens->isNiPrototype);
}

HdTokenDataSourceHandle UsdImagingUsdPrimInfoSchema::GetSpecifier() const
{
  return _GetTypedDataSource<HdTokenDataSource>(UsdImagingUsdPrimInfoSchemaTokens->specifier);
}

HdContainerDataSourceHandle UsdImagingUsdPrimInfoSchema::GetPiPropagatedPrototypes() const
{
  return _GetTypedDataSource<HdContainerDataSource>(
      UsdImagingUsdPrimInfoSchemaTokens->piPropagatedPrototypes);
}

HdBoolDataSourceHandle UsdImagingUsdPrimInfoSchema::GetIsLoaded() const
{
  return _GetTypedDataSource<HdBoolDataSource>(UsdImagingUsdPrimInfoSchemaTokens->isLoaded);
}

/*static*/
HdContainerDataSourceHandle UsdImagingUsdPrimInfoSchema::BuildRetained(
    const HdPathDataSourceHandle &niPrototypePath,
    const HdBoolDataSourceHandle &isNiPrototype,
    const HdTokenDataSourceHandle &specifier,
    const HdContainerDataSourceHandle &piPropagatedPrototypes,
    const HdBoolDataSourceHandle &isLoaded)
{
  TfToken _names[5];
  HdDataSourceBaseHandle _values[5];

  size_t _count = 0;

  if (niPrototypePath) {
    _names[_count] = UsdImagingUsdPrimInfoSchemaTokens->niPrototypePath;
    _values[_count++] = niPrototypePath;
  }

  if (isNiPrototype) {
    _names[_count] = UsdImagingUsdPrimInfoSchemaTokens->isNiPrototype;
    _values[_count++] = isNiPrototype;
  }

  if (specifier) {
    _names[_count] = UsdImagingUsdPrimInfoSchemaTokens->specifier;
    _values[_count++] = specifier;
  }

  if (piPropagatedPrototypes) {
    _names[_count] = UsdImagingUsdPrimInfoSchemaTokens->piPropagatedPrototypes;
    _values[_count++] = piPropagatedPrototypes;
  }

  if (isLoaded) {
    _names[_count] = UsdImagingUsdPrimInfoSchemaTokens->isLoaded;
    _values[_count++] = isLoaded;
  }
  return HdRetainedContainerDataSource::New(_count, _names, _values);
}

UsdImagingUsdPrimInfoSchema::Builder &UsdImagingUsdPrimInfoSchema::Builder::SetNiPrototypePath(
    const HdPathDataSourceHandle &niPrototypePath)
{
  _niPrototypePath = niPrototypePath;
  return *this;
}

UsdImagingUsdPrimInfoSchema::Builder &UsdImagingUsdPrimInfoSchema::Builder::SetIsNiPrototype(
    const HdBoolDataSourceHandle &isNiPrototype)
{
  _isNiPrototype = isNiPrototype;
  return *this;
}

UsdImagingUsdPrimInfoSchema::Builder &UsdImagingUsdPrimInfoSchema::Builder::SetSpecifier(
    const HdTokenDataSourceHandle &specifier)
{
  _specifier = specifier;
  return *this;
}

UsdImagingUsdPrimInfoSchema::Builder &UsdImagingUsdPrimInfoSchema::Builder::
    SetPiPropagatedPrototypes(const HdContainerDataSourceHandle &piPropagatedPrototypes)
{
  _piPropagatedPrototypes = piPropagatedPrototypes;
  return *this;
}

UsdImagingUsdPrimInfoSchema::Builder &UsdImagingUsdPrimInfoSchema::Builder::SetIsLoaded(
    const HdBoolDataSourceHandle &isLoaded)
{
  _isLoaded = isLoaded;
  return *this;
}

HdContainerDataSourceHandle UsdImagingUsdPrimInfoSchema::Builder::Build()
{
  return UsdImagingUsdPrimInfoSchema::BuildRetained(
      _niPrototypePath, _isNiPrototype, _specifier, _piPropagatedPrototypes, _isLoaded);
}

/*static*/
UsdImagingUsdPrimInfoSchema UsdImagingUsdPrimInfoSchema::GetFromParent(
    const HdContainerDataSourceHandle &fromParentContainer)
{
  return UsdImagingUsdPrimInfoSchema(fromParentContainer ?
                                         HdContainerDataSource::Cast(fromParentContainer->Get(
                                             UsdImagingUsdPrimInfoSchemaTokens->__usdPrimInfo)) :
                                         nullptr);
}

/*static*/
const TfToken &UsdImagingUsdPrimInfoSchema::GetSchemaToken()
{
  return UsdImagingUsdPrimInfoSchemaTokens->__usdPrimInfo;
}

/*static*/
const HdDataSourceLocator &UsdImagingUsdPrimInfoSchema::GetDefaultLocator()
{
  static const HdDataSourceLocator locator(GetSchemaToken());
  return locator;
}

/* static */
const HdDataSourceLocator &UsdImagingUsdPrimInfoSchema::GetNiPrototypePathLocator()
{
  static const HdDataSourceLocator locator = GetDefaultLocator().Append(
      UsdImagingUsdPrimInfoSchemaTokens->niPrototypePath);
  return locator;
}

/*static*/
HdTokenDataSourceHandle UsdImagingUsdPrimInfoSchema::BuildSpecifierDataSource(
    const TfToken &specifier)
{

  if (specifier == UsdImagingUsdPrimInfoSchemaTokens->def) {
    static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
        HdRetainedTypedSampledDataSource<TfToken>::New(specifier);
    return ds;
  }
  if (specifier == UsdImagingUsdPrimInfoSchemaTokens->over) {
    static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
        HdRetainedTypedSampledDataSource<TfToken>::New(specifier);
    return ds;
  }
  if (specifier == UsdImagingUsdPrimInfoSchemaTokens->class_) {
    static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
        HdRetainedTypedSampledDataSource<TfToken>::New(specifier);
    return ds;
  }
  // fallback for unknown token
  return HdRetainedTypedSampledDataSource<TfToken>::New(specifier);
}

PXR_NAMESPACE_CLOSE_SCOPE