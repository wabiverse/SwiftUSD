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

#include "Hd/tetMeshTopologySchema.h"

#include "Hd/retainedDataSource.h"
#include "Hd/tetMeshSchema.h"

#include "Trace/traceImpl.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdTetMeshTopologySchemaTokens, HD_TET_MESH_TOPOLOGY_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdVec4iArrayDataSourceHandle HdTetMeshTopologySchema::GetTetVertexIndices() const
{
  return _GetTypedDataSource<HdVec4iArrayDataSource>(
      HdTetMeshTopologySchemaTokens->tetVertexIndices);
}

HdVec3iArrayDataSourceHandle HdTetMeshTopologySchema::GetSurfaceFaceVertexIndices() const
{
  return _GetTypedDataSource<HdVec3iArrayDataSource>(
      HdTetMeshTopologySchemaTokens->surfaceFaceVertexIndices);
}

HdTokenDataSourceHandle HdTetMeshTopologySchema::GetOrientation() const
{
  return _GetTypedDataSource<HdTokenDataSource>(HdTetMeshTopologySchemaTokens->orientation);
}

/*static*/
HdContainerDataSourceHandle HdTetMeshTopologySchema::BuildRetained(
    const HdVec4iArrayDataSourceHandle &tetVertexIndices,
    const HdVec3iArrayDataSourceHandle &surfaceFaceVertexIndices,
    const HdTokenDataSourceHandle &orientation)
{
  TfToken _names[3];
  HdDataSourceBaseHandle _values[3];

  size_t _count = 0;

  if (tetVertexIndices) {
    _names[_count] = HdTetMeshTopologySchemaTokens->tetVertexIndices;
    _values[_count++] = tetVertexIndices;
  }

  if (surfaceFaceVertexIndices) {
    _names[_count] = HdTetMeshTopologySchemaTokens->surfaceFaceVertexIndices;
    _values[_count++] = surfaceFaceVertexIndices;
  }

  if (orientation) {
    _names[_count] = HdTetMeshTopologySchemaTokens->orientation;
    _values[_count++] = orientation;
  }
  return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdTetMeshTopologySchema::Builder &HdTetMeshTopologySchema::Builder::SetTetVertexIndices(
    const HdVec4iArrayDataSourceHandle &tetVertexIndices)
{
  _tetVertexIndices = tetVertexIndices;
  return *this;
}

HdTetMeshTopologySchema::Builder &HdTetMeshTopologySchema::Builder::SetSurfaceFaceVertexIndices(
    const HdVec3iArrayDataSourceHandle &surfaceFaceVertexIndices)
{
  _surfaceFaceVertexIndices = surfaceFaceVertexIndices;
  return *this;
}

HdTetMeshTopologySchema::Builder &HdTetMeshTopologySchema::Builder::SetOrientation(
    const HdTokenDataSourceHandle &orientation)
{
  _orientation = orientation;
  return *this;
}

HdContainerDataSourceHandle HdTetMeshTopologySchema::Builder::Build()
{
  return HdTetMeshTopologySchema::BuildRetained(
      _tetVertexIndices, _surfaceFaceVertexIndices, _orientation);
}

/*static*/
HdTetMeshTopologySchema HdTetMeshTopologySchema::GetFromParent(
    const HdContainerDataSourceHandle &fromParentContainer)
{
  return HdTetMeshTopologySchema(fromParentContainer ?
                                     HdContainerDataSource::Cast(fromParentContainer->Get(
                                         HdTetMeshTopologySchemaTokens->topology)) :
                                     nullptr);
}

/*static*/
const TfToken &HdTetMeshTopologySchema::GetSchemaToken()
{
  return HdTetMeshTopologySchemaTokens->topology;
}

/*static*/
const HdDataSourceLocator &HdTetMeshTopologySchema::GetDefaultLocator()
{
  static const HdDataSourceLocator locator = HdTetMeshSchema::GetDefaultLocator().Append(
      GetSchemaToken());
  return locator;
}

/* static */
const HdDataSourceLocator &HdTetMeshTopologySchema::GetTetVertexIndicesLocator()
{
  static const HdDataSourceLocator locator = GetDefaultLocator().Append(
      HdTetMeshTopologySchemaTokens->tetVertexIndices);
  return locator;
}

/* static */
const HdDataSourceLocator &HdTetMeshTopologySchema::GetSurfaceFaceVertexIndicesLocator()
{
  static const HdDataSourceLocator locator = GetDefaultLocator().Append(
      HdTetMeshTopologySchemaTokens->surfaceFaceVertexIndices);
  return locator;
}

/*static*/
HdTokenDataSourceHandle HdTetMeshTopologySchema::BuildOrientationDataSource(
    const TfToken &orientation)
{

  if (orientation == HdTetMeshTopologySchemaTokens->leftHanded) {
    static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
        HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
    return ds;
  }
  if (orientation == HdTetMeshTopologySchemaTokens->rightHanded) {
    static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
        HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
    return ds;
  }
  // fallback for unknown token
  return HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
}

PXR_NAMESPACE_CLOSE_SCOPE