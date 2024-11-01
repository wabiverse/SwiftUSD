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

#ifndef PXR_IMAGING_HD_MATERIAL_NODE_SCHEMA_H
#define PXR_IMAGING_HD_MATERIAL_NODE_SCHEMA_H

/// \file

#include "Hd/api.h"
#include "Hd/schemaTypeDefs.h"

#include "Hd/schema.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

// --(BEGIN CUSTOM CODE: Declares)--
// --(END CUSTOM CODE: Declares)--

#define HD_MATERIAL_NODE_SCHEMA_TOKENS \
  (parameters)(inputConnections)(nodeIdentifier)(renderContextNodeIdentifiers)(nodeTypeInfo)

TF_DECLARE_PUBLIC_TOKENS(HdMaterialNodeSchemaTokens, HD_API, HD_MATERIAL_NODE_SCHEMA_TOKENS);

//-----------------------------------------------------------------------------

class HdMaterialNodeSchema : public HdSchema {
 public:
  /// \name Schema retrieval
  /// @{

  HdMaterialNodeSchema(HdContainerDataSourceHandle container) : HdSchema(container) {}

  /// @}

  // --(BEGIN CUSTOM CODE: Schema Methods)--
  // --(END CUSTOM CODE: Schema Methods)--

  /// \name Member accessor
  /// @{

  HD_API
  HdMaterialNodeParameterContainerSchema GetParameters() const;

  HD_API
  HdMaterialConnectionVectorContainerSchema GetInputConnections() const;

  /// This identifies the shader the node represents. The
  /// renderContextNodeIdentifier container can store alternative values for
  /// this. A consumer which is interested in a specific render context
  /// should check for that token within renderContextNodeIdentifiers and
  /// fall back on this value in its absence.
  HD_API
  HdTokenDataSourceHandle GetNodeIdentifier() const;

  /// A shading node can hold a nodeIdentifier value for multiple render
  /// contexts at once. This allows multiple renderer target representations
  /// to coexist in the same renderable scene. The contents of this
  /// container are alternate possible values for nodeIdentifier. A consumer
  /// which is interested in a specific render context should check for that
  /// token within this container and fall back on nodeIdentifier in its
  /// absence.
  HD_API
  HdContainerDataSourceHandle GetRenderContextNodeIdentifiers() const;

  /// Rather than having an identifier, a shader can be specified by other
  /// information.
  HD_API
  HdContainerDataSourceHandle GetNodeTypeInfo() const;

  /// @}

  /// \name Schema construction
  /// @{

  /// \deprecated Use Builder instead.
  ///
  /// Builds a container data source which includes the provided child data
  /// sources. Parameters with nullptr values are excluded. This is a
  /// low-level interface. For cases in which it's desired to define
  /// the container with a sparse set of child fields, the Builder class
  /// is often more convenient and readable.
  HD_API
  static HdContainerDataSourceHandle BuildRetained(
      const HdContainerDataSourceHandle &parameters,
      const HdContainerDataSourceHandle &inputConnections,
      const HdTokenDataSourceHandle &nodeIdentifier,
      const HdContainerDataSourceHandle &renderContextNodeIdentifiers,
      const HdContainerDataSourceHandle &nodeTypeInfo);

  /// \class HdMaterialNodeSchema::Builder
  ///
  /// Utility class for setting sparse sets of child data source fields to be
  /// filled as arguments into BuildRetained. Because all setter methods
  /// return a reference to the instance, this can be used in the "builder
  /// pattern" form.
  class Builder {
   public:
    HD_API
    Builder &SetParameters(const HdContainerDataSourceHandle &parameters);
    HD_API
    Builder &SetInputConnections(const HdContainerDataSourceHandle &inputConnections);
    HD_API
    Builder &SetNodeIdentifier(const HdTokenDataSourceHandle &nodeIdentifier);
    HD_API
    Builder &SetRenderContextNodeIdentifiers(
        const HdContainerDataSourceHandle &renderContextNodeIdentifiers);
    HD_API
    Builder &SetNodeTypeInfo(const HdContainerDataSourceHandle &nodeTypeInfo);

    /// Returns a container data source containing the members set thus far.
    HD_API
    HdContainerDataSourceHandle Build();

   private:
    HdContainerDataSourceHandle _parameters;
    HdContainerDataSourceHandle _inputConnections;
    HdTokenDataSourceHandle _nodeIdentifier;
    HdContainerDataSourceHandle _renderContextNodeIdentifiers;
    HdContainerDataSourceHandle _nodeTypeInfo;
  };

  /// @}
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
