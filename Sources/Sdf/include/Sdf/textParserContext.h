//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_TEXT_PARSER_CONTEXT_H
#define PXR_USD_SDF_TEXT_PARSER_CONTEXT_H

#include "Sdf/data.h"
#include "Sdf/layerHints.h"
#include "Sdf/layerOffset.h"
#include "Sdf/listOp.h"
#include "Sdf/parserValueContext.h"
#include "Sdf/path.h"
#include "Sdf/payload.h"
#include "Sdf/reference.h"
#include "Sdf/types.h"
#include "pxr/pxrns.h"

#include "Vt/dictionary.h"

#include "Tf/token.h"

#include <optional>
#include <string>
#include <vector>

// Lexical scanner type.
typedef void *yyscan_t;

PXR_NAMESPACE_OPEN_SCOPE

// This class contains the global state while parsing an sdf file.
// It contains the data structures that we use to create the scene description
// from the file.

class Sdf_TextParserContext {
 public:
  // Constructor.
  Sdf_TextParserContext();

  std::string magicIdentifierToken;
  std::string versionString;
  std::string fileContext;

  // State for layer refs, in general
  std::string layerRefPath;
  SdfLayerOffset layerRefOffset;

  // State for sublayers
  std::vector<std::string> subLayerPaths;

  // State for sublayer offsets
  std::vector<SdfLayerOffset> subLayerOffsets;

  // String list currently being built
  std::vector<TfToken> nameVector;

  SdfTimeSampleMap timeSamples;
  double timeSampleTime;

  SdfPath savedPath;

  // Whether the current relationship target being parsed is allowed to
  // have data like relational attributes.
  bool relParsingAllowTargetData;
  // relationship target paths that will be saved in a list op
  // (use a std::optional to track whether we have seen an opinion at all.)
  std::optional<SdfPathVector> relParsingTargetPaths;
  // relationship target paths that will be appended to the relationship's
  // list of target children.
  SdfPathVector relParsingNewTargetChildren;

  // helpers for connection path parsing
  SdfPathVector connParsingTargetPaths;
  bool connParsingAllowConnectionData;

  // helpers for inherit path parsing
  SdfPathVector inheritParsingTargetPaths;

  // helpers for specializes path parsing
  SdfPathVector specializesParsingTargetPaths;

  // helpers for reference parsing
  SdfReferenceVector referenceParsingRefs;

  // helpers for payload parsing
  SdfPayloadVector payloadParsingRefs;

  // helper for relocates parsing
  SdfRelocates relocatesParsing;

  // helpers for generic metadata
  TfToken genericMetadataKey;
  SdfListOpType listOpType;

  // The value parser context
  Sdf_ParserValueContext values;

  // Last parsed value
  VtValue currentValue;

  // Vector of dictionaries used to parse nested dictionaries.
  // The first element in the vector contains the last parsed dictionary.
  std::vector<VtDictionary> currentDictionaries;

  bool seenError;

  bool custom;
  SdfSpecifier specifier;
  SdfDataRefPtr data;
  SdfPath path;
  TfToken typeName;
  VtValue variability;
  VtValue assoc;

  // Should we only read metadata from the file?
  bool metadataOnly;

  // Hints to fill in about the layer's contents.
  SdfLayerHints layerHints;

  // Stack for the child names of all the prims currently being parsed
  // For instance if we're currently parsing /A/B then this vector
  // will contain three elements:
  //    names of the root prims
  //    names of A's children
  //    names of B's children.
  std::vector<std::vector<TfToken>> nameChildrenStack;

  // Stack for the property names of all the objects currently being parsed
  std::vector<std::vector<TfToken>> propertiesStack;

  // Stack of names of variant sets  being built.
  std::vector<std::string> currentVariantSetNames;

  // Stack of names of variants for the variant sets being built
  std::vector<std::vector<std::string>> currentVariantNames;

  unsigned int sdfLineNo;

  // Used by flex for reentrant parsing
  yyscan_t scanner;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_SDF_TEXT_PARSER_CONTEXT_H
