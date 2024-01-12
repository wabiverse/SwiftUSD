# ``Usd``

Authoring, composing, and reading **Universal Scene Description** (**USD**).

## Overview

**Usd** is the core client-facing module for authoring, composing, and reading
**Universal Scene Description**. **USD** is designed to encode scalable,
hierarchically organized, static and time-sampled data, for the primary
purpose of interchanging and augmenting the data between cooperating Digital
Content Creation applications.

### **Core API Manual**

This manual contains the API documentation for the core Usd module, prefaced
with an introduction to the key concepts behind the API, and including a
guide to making effective use of the API. In this manual we do not deeply
explore the composition semantics that underly Usd scenegraphs - that is the
domain of the (forthcoming) **Universal Scene Description Composition Compendium**.
We will discuss some aspects of the composition operators, primarily as they affect
authoring workflows and/or scalability and/or import/export.

| Key Classes           | Description                                                            |
| --------------------- | ---------------------------------------------------------------------- |
| `Usd/UsdStage`        | owns the scenegraph and provides access to a composition.              |
| `Usd/UsdPrim`         | is the hierarchically nestable unit of scene description.              |
| `Usd/UsdAttribute`    | records time-varying data on prims.                                    |
| `Usd/UsdRelationship` | records links to other prims and properties.                           |
| `Usd/UsdEditTarget`   | allows editing of any layer/variation contained in a stage.            |
| `Usd/UsdNotice`       | contains notifications that Usd issues when a stage's contents change. |
| `Usd/UsdSchemaBase`   | is the base class for generated schema classes.                        |
| `Usd/UsdTimeCode`     | is an ordinate that can be floating-point or an unvarying 'default'.   |

## Topics

### Object Model

- `Usd/SdfLayer`
- `Usd/UsdStage`
- `Usd/UsdPrim`
- `Usd/UsdProperty`
- `Usd/UsdAttribute`
- `Usd/UsdRelationship`
  <!-- - ``Usd/Metadata`` -->
  <!-- - ``Usd/OtherObjects`` -->

<!-- ### Data Types

- Basic Types
- Roles
- Arrays
- Dictionaries -->

<!-- ### Properties of Scene Description

- Ordering
- Value Resolution
- Prim Specifiers
- Model Hierarchy
- Active & Inactive
- File Types
- Asset Resolution -->

<!-- ### Advanced Features

- Dynamic File Format
- Scenegraph Instancing
- Value Clips -->

<!-- ### Authoring Editing

- Selective Editing
- Notification -->

<!-- ### Common Idioms

- Stage Traversal
- Working with Schemas
- Bool Returns
- Error Reporting -->

<!-- ###  BestPractices

- Shared References
- Data Streaming
- Payloads  -->

<!-- ### Multi-Threading

- Thread Safety Model
- Internal Multi-Threading -->

<!-- ### Generating Schemas

- `is(a:)` vs API Schemas
- Schema Extension Philosophy -->
