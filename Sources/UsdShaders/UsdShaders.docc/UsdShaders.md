### <sub>Definitions and Implementations of Usd Shader Nodes</sub>
# <sup>**Pixar.UsdShaders**</sup>

### Overview

This library houses the definitions and implementations for all the current 
(and future) "Usd*" shader nodes, eg. **UsdPreviewSurface**, **UsdUVTexture**,
etc.

The definitions are represented by a UsdShade-based shader definition file. 
See **UsdShadeShaderDefinition**. It currently only contains "glslfx"
implementations for the hydra GL backend. In the (not-too-distant) future, it 
will contain "oso" files that provide OSL implementations of the Usd* shaders.

In addition to shader definitions and implementations, this library may also 
provide Usd schemas for robust authoring and querying of shader properties in
the future.
