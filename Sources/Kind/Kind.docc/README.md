### <sub>Extensible Categorization</sub>
# <sup>**Pixar.Kind**</sup>

### **Overview**

The **Kind** library provides a runtime-extensible taxonomy known as "kinds".

**Kinds** are just **TfToken** symbols, but the KindRegistry allows for organizing
kinds into taxonomies of related/refined concepts, and the ``KindRegistry::GetBaseKind()``
and ``KindRegistry::IsA()`` queries enable reasoning about the hierarchy and classifying
objects by kind.

**Kinds** are useful for classifying scenegraph objects, such as by tagging objects
representing the roots of models with the kind of model it represents; it is scenegraph
taxonomy that motivates the "builtin" kind hierarchy.

### The Core Kind Hierarchy

The **KindRegistry** begins its life pre-loaded with the following hierarchy of kinds
that define our concept of "model hierarchy", which is so central to our organization
and discovery of scene description. Of course, as described in the next section,
unlimited new, entirely unrelated taxonomies can be created by extension.

  - **model** Everything in the model hierarchy is a kind of model.

  - **component** A component model is a terminal model in the model
    hierarchy, it can have no child models.

  - **group** A model that is simply a container for other models.

  - **assembly** An "important" group model - often because it is
    itself a published asset.

  - **subcomponent** Within a component model, subcomponents identify
    important (generally articulable) sub-trees. Subcomponents are
    "stopping points" when dynamically unrolling/expanding a component.


### Extending the KindRegistry

The kind registry can be *extended* using the facilities provided by **PlugRegistry**,
by adding a 'Kinds' sub-dictionary to the *plugInfo.json* file of any module within your
"pixar-base aware" build environment.

The dictionary entries will look like the following:

```json
"Info": 
{
  "Kinds": 
  {
    "chargroup": 
    {
      "baseKind": "assembly",
      "description": "A chargroup is an assembly ..."
    },
    "charprop": 
    {
      "baseKind": "component"
    },
    "newRootKind": {}
  }
}
```

> [!NOTE]
> One cannot alter core kinds or their place in the
> hierarchy or any other data associated with them by
> attempting to override them in the extension file.
> Attempting to do so will result in a registration
> error.
