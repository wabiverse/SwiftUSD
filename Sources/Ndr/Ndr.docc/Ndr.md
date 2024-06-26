# ``Ndr``

## Overview

**Ndr** provides a framework in which you can, agnostic to the node's domain
(shading, lighting, compositing, etc), register nodes with **Ndr**, and they
subsequently ask for information about those nodes. The information **Ndr**
provides about these nodes will be fairly generic, given that **Ndr** must
not cater to any specific type of node. However, specialized registries can
derive from **Ndr**, and it is there that domain-specific logic can be
implemented. Additionally, node parsing and "discovery" are done via
plugins, again to keep **Ndr** generic and extendable.

In addition to being able to instantiate specialized registries, domain-specific
nodes and properties deriving from the base Ndr classes can also be created.
This is explained in the sections below.

#### Ndr Organization

Ndr can be split into 5 major components, as described by the following
subsections.

##### Ndr Base Registry

The core Ndr registry, `NdrRegistry`, is where node-level queries are done.
In practice, it will not be used directly (in almost all cases, a specialized
registry deriving from Ndr core will be used instead). Upon initialization, the
registry searches for all parser and discovery plugins. During this start-up
phase the discovery plugins are all run, but the nodes that are found are NOT
parsed. The registry parses nodes on demand when information about a node(s) is
requested in order to keep the start-up process as fast as possible.

The type of information that the base Ndr registry provides includes:

<ul>
    <li>The names of nodes that have been registered</li>
    <li>Parsed node instances (created on-demand when requested)</li>
    <li>Where the nodes were found</li>
</ul>

##### Ndr Base Node

Ndr provides a base node class, `NdrNode`, which exposes domain-agnostic
information such as:

<ul>
    <li>The node type</li>
    <li>What the inputs and outputs are</li>
    <li>Any metadata attached to the node</li>
</ul>

An NdrNode represents a dataflow-connectable computation, intended to be a
node in a computational network. A node's NdrProperty's represent its
computational inputs and outputs, and its **URI**'s identify its external
sources:

- NdrNode::GetResolvedDefinitionURI() identifies the asset that provided
  the definition of the node, which is determined during
  \ref ndr_DiscoveryPlugin "node discovery."
- NdrNode::GetResolvedImplementationURI() identifies (if relevant) an
  implementation of the node's computation, for use by clients of computational
  networks in which node instances may appear. It is the responsibility of a
  \ref ndr_ParserPlugin "parser plugin" to determine and resolve an
  implementation from the node's definition.

##### Ndr Base Property

Ndr also provides a base property class, `NdrProperty`. Inputs and outputs are
on a node are collectively identified as "properties".

The base property exposes information like:

<ul>
    <li>The input type</li>
    <li>The default value, if any</li>
    <li>Any metadata attached to the property</li>
    <li>Whether the property is connectable</li>
</ul>

##### Discovery Plugins

Discovery plugins are how the registry finds (or "discovers") nodes. The
registry makes no assumptions on where, or how, nodes are stored. A discovery
plugin can be built to find file-based nodes on the filesystem (a typical case),
search a database, a cloud service, or any other system that might contain nodes.
If nodes are scattered across multiple systems, a discovery plugin can be
created for each. More info about discovery plugins is available in the
`NdrDiscoveryPlugin` documentation.

Note that a filesystem-based discovery plugin is active by default. More
information on how to configure this plugin can be found in the documentation
for `_NdrFilesystemDiscoveryPlugin`. In a nutshell, there are a few environment
variables that can be configured to control its behavior. However, the more
robust pattern that any renderer or shading-system plugin should follow is to
provide its **own** DiscoveryPlugin, so that its configuration will not interfere
with that of other plugins. The filesystem discovery machinery that the builtin
`_NdrFilesystemDiscoveryPlugin` plugin uses is available for other discovery
plugins to use - see NdrFsHelpersDiscoverNodes().

##### Parser Plugins

Once the registry knows about nodes via the discovery plugin(s), the parser
plugins parse the nodes and provide the registry with the resulting information.
The parser plugins are responsible for information such as the node's type,
its metadata, and all information about its inputs and outputs. In the end,
the parser plugin is responsible for determining all information about the node
that could not otherwise be determined via the discovery plugin. More
information about parser plugins is available in the `NdrParserPlugin`
documentation.

#### How to Set Up a Domain-Specific Registry

The base Ndr registry can be used as-is if only generic information about nodes
is needed. In most cases however, more detailed information about the nodes will
be necessary, and this is where domain-specific registries come into play. The
process can be divided into 5 areas of customization, which echo the 5 sections
above.

##### Custom Registry

The base Ndr registry can be derived from to create a specialized registry. In
many cases, not much will be needed here except doing dynamic casts to your
domain-specific nodes. The registry's base class provides methods such as
`NdrRegistry::GetNode()` (which returns a `NdrNode`), but you may want to
provide additional methods like `GetShadingNode()` which dynamic casts the
result from `NdrRegistry::GetNode()` to a shading node instance. See
`SdrRegistry` for an example.

##### Custom Nodes

As mentioned before, the base node class `NdrNode` only provides generic
information about the node. Specialized nodes can derive from `NdrNode` to
implement any additional functionality that is needed. The parser plugin for
the node can provide this information to the node via the constructor. Nodes
should be immutable once created. See `SdrShaderNode` for an example.

##### Custom Properties

The process here is the same as for nodes: derive from `NdrProperty` and add
new functionality, or override existing methods. See `SdrShaderProperty` for an
example.

##### Custom Discovery Plugin

See the documentation for `NdrDiscoveryPlugin` for more information.

##### Custom Parser Plugin

See the documentation for `NdrParserPlugin` for more information.
