# ``Hd``
# Hydra Framework

## Overview

The **Hd** (**Hydra**) framework facilitates communication between multiple scene graphs 
and multiple renderers (**Hydra Render Delegate**).

## Render Index

The **Render Index** employs the **Render Delegate** for the purpose of generating and removing 
scene primitives, encompassing both geometry and non-drawable objects. 

Within **Hydra**, primitives are categorized into _Rprims_ (drawables), _Sprims_ (state objects 
such as cameras and materials), and _Bprims_ (buffer objects like textures). 

The fundamental set of primitives that a renderer must support includes 
at least one _Rprim_ (to prevent an empty scene) and the "camera" _Sprim_. 
The latter is imperative for **HdxRenderTask**, the task that executes basic **Hydra** drawing.
