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

#include "Hd/cubeSchema.h"

#include "Hd/retainedDataSource.h"

#include "Trace/traceImpl.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdCubeSchemaTokens, HD_CUBE_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdDoubleDataSourceHandle HdCubeSchema::GetSize() const
{
  return _GetTypedDataSource<HdDoubleDataSource>(HdCubeSchemaTokens->size);
}

/*static*/
HdContainerDataSourceHandle HdCubeSchema::BuildRetained(const HdDoubleDataSourceHandle &size)
{
  TfToken _names[1];
  HdDataSourceBaseHandle _values[1];

  size_t _count = 0;

  if (size) {
    _names[_count] = HdCubeSchemaTokens->size;
    _values[_count++] = size;
  }
  return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdCubeSchema::Builder &HdCubeSchema::Builder::SetSize(const HdDoubleDataSourceHandle &size)
{
  _size = size;
  return *this;
}

HdContainerDataSourceHandle HdCubeSchema::Builder::Build()
{
  return HdCubeSchema::BuildRetained(_size);
}

/*static*/
HdCubeSchema HdCubeSchema::GetFromParent(const HdContainerDataSourceHandle &fromParentContainer)
{
  return HdCubeSchema(fromParentContainer ? HdContainerDataSource::Cast(fromParentContainer->Get(
                                                HdCubeSchemaTokens->cube)) :
                                            nullptr);
}

/*static*/
const TfToken &HdCubeSchema::GetSchemaToken()
{
  return HdCubeSchemaTokens->cube;
}

/*static*/
const HdDataSourceLocator &HdCubeSchema::GetDefaultLocator()
{
  static const HdDataSourceLocator locator(GetSchemaToken());
  return locator;
}

PXR_NAMESPACE_CLOSE_SCOPE
