# ``Sdr``

## Overview

Sdr is a shading-specialized version of Ndr, and provides the following
specialized classes:

- `SdrRegistry`
- `SdrShaderNode`
- `SdrShaderProperty`

For more details on the registry, nodes, or properties, see the base Ndr
classes:

- `NdrRegistry`
- `NdrNode`
- `NdrProperty`

For a high-level view of the system and how all the parts work together, see
the overview page for Ndr.

# Discussion of [SdrPropertyTypes](Pixar/SdrPropertyTypes)

Sdr defines a limited set of types:

- Int
- String
- Float
- Color
- Point
- Normal
- Vector
- Matrix
- Struct
- Terminal
- VStruct
- Unknown

## Two notions of types (SdrPropertyType and SdfValueTypeName)

The SdrPropertyType is not written out to a USD layer, but with the aid of other
information and metadata gathered from a node's shader definition, the
SdrPropertyType is mapped to an SdfValueTypeName that is written into USD
layers. The SdfValueTypeNames are a much richer and wider set of types, and it
is this type that is looked at during opinion composition.

For most of the basic SdrPropertyTypes, we have direct mappings to
SdfValueTypeNames given the Sdr type and if it is an array. For some of the
SdrPropertyTypes, we use metadata to aid the translation to a particular
SdfValueTypeName (see below).

Clients writing NdrParserPlugin sub-classes for Sdr need only be concerned with
a property's SdrPropertyType. Sdr will handle the details of assigning the
correct SdfValueTypeName.

## Discussion of the special Sdr property types

Some SdrPropertyTypes are a little special because there is no reasonable
corresponding SdfValueTypeName, so we map them all to SdfValueTypeName->Token,
which is typically reserved for an Unknown type.

The special SdrPropertyTypes that map to 'Token' are:

- Struct - Struct types
- Terminal - Certain properties represent 'terminal' ports (ie. surface,
  displacement, volume, etc)
- Vstruct - An abstract struct type that can connect to any other 'vstruct', and
  connections are only made if a matching vstruct member is found.

As described, these special SdrPropertyTypes cannot be represented as a
SdfValueTypeName, which is why we simply map them to 'Token'. A user can
find the original struct type or terminal type of one of these properties by
examining the 'renderType' metadata on the property, since this original type
information is not preserved in either the SdrPropertyType or SdfValueTypeName.

## Sdr metadata that is used to determine SdrPropertyType

As mentioned previously, metadata can be used to drive the parsing of a
SdrPropertyType. This metadata does need to be authored by shader writers.
Some of these metadata tags are:

- 'renderType' - The 'renderType' metadata should be specified for Struct,
  Terminal, and Vstruct properties.
  - On a Struct, the metadata would be 'renderType' = 'struct structName',
    where structName is the actual struct's typename
  - On a Terminal, the metadata would be 'renderType' = 'terminal terminalName'
    where terminalName is the actual kind of terminal
  - On a Vstruct, the metadata would be 'renderType' = 'vstruct', since there is
    no further specific type name for a vstruct
- 'role' - The 'role' metadata can be specified for any SdrPropertyType, and the
  value of 'role' will determine if the property will be transformed to a
  different SdrPropertyType. This metadata is special in that parser plugin
  writers do NOT need to handle any SdrPropertyType transformations. Parser
  writers simply need to parse the property as usual and allow
  SdrShaderProperty to apply any needed transformations to the SdrPropertyType.
  The 'role' metadata can only have the following predefined values:
  - 'none' - If 'role' is 'none', then the SdrPropertyType will be
    transformed to be as generic as possible. For example, if a property of
    original SdrPropertyTypes->Color has 'role' specified as 'none', then the
    property will actually become SdrPropertyTypes->Float.

## Sdr metadata that is used to determine SdfValueTypeName

Some metadata is used to drive the conversion of an SdfValueTypeName.
Metadata that is used for SdfValueTypeName conversion is authored either by
shader writers (SdrUsdDefinitionName), or it should be injected into an
SdrShaderProperty by a parser plugin writer (IsAssetIdentifier).
This includes:

- SdrPropertyMetadata->IsAssetIdentifier - This metadata tag is injected by a
  parser if the parser determines that the property is an asset. The presence
  of this metadata tag then guides the type mapping to choose
  SdfValueTypeNames->Asset
- SdrPropertyMetadata->SdrUsdDefinitionType - This metadata, explicitly
  authored in a shader definition, specifies the SdfValueTypeName as string.
  Note that this metadata takes precendence in determining the SdfValueTypeName
  for the SdrShaderProperty. Authors of shader definition will have to provide
  explicit TfType value aliases (Refer SdfValueTypeName::GetAliasesAsTokens())
  associated with the SdfValueTypeName, which generally match the type
  declarations found in a usda file.
  Example "bool" for SdfValueTypeNames->Bool, "bool[]" for
  SdfValueTypeNames->BoolArray, etc. This is specifically important in
  determining types which are represented as an "int" in the sdr type system but
  should be represented as SdfValueTypeNames->Bool in the equivalent Sdf/USD
  representation. When sdrUsdDefinitionType is specified, Sdr will do its best
  to convert the default value provided in the shader definition into the
  requested SdfValueType.

## Some examples illustrating the treatment of property types

```{.usd}
shader TestOSLShader
(
    color foo = color(1.0, 1.0 1.0),
    token bar = "baz",
    token surface = ""
    [[
        string renderType = "terminal surface"
    ]]
)
```

In the above example, the properties would be translated as follows:

| Property | SdrPropertyType            | SdfValueTypeName          |
| :------- | :------------------------- | :------------------------ |
| foo      | SdrPropertyTypes->Color    | SdfValueTypeNames->Color  |
| bar      | SdrPropertyTypes->String   | SdfValueTypeNames->String |
| surface  | SdrPropertyTypes->Terminal | SdfValueTypeNames->Token  |
