# Graphics_API_Revamp_documentation

GridPro Graphics_API_Revamp_documentation.

## Table of Contents

- [About](#about)
- [Existing RenderPipeline](#existing-renderpipeline)
- [Challenges in Porting](#challenges-in-porting)
- [Solutions](#solutions)
- [Renderer API Reference](#renderer-api-reference)

## About

To replace Fixed pipeline approach with shader approach in GridPro WS. 

## Existing RenderPipeline

Existing RenderPipeline Structure & Configuration exists as
- A class derived from `QApplication` class called -> `Gp_gui_Application` which has `Gp_gui_mainwindow`
- MVP pattern is used to seperate `MODEL <-> PRESENTER_LAYER <-> VIEW` 
- `Gp_gui_mainwindow` has subwindow attached called `gp_gui_glwidget`
- `gp_gui_glwidget` class derived from `QOGLWiget`, is used to setup windowing, OpenGL context,
   Scene Configuration (Not Exactly but setting up mvp from camera pos , view volume evaluation , peripheral input handling) 
- `paintGL` is where rendering starts.
-  Inside `gp_gui_glwidget::paintGL` , a reference for gp_gui_model objects are accquired.
  
#### What are gp_gui_models ??
   Since bare data structures like topology do not contain all the data to represent all visual aspects of topology model,
   a new model data structure is built by inheriting base topology data structure & additionally data members & methods are created
   for rendering all aspects, properties of topology model.
   
##### Each gp_gui_model is derived from a core data structure that contain the actual buisness logic
-  Get avaliable gp_gui_model from `Gp_gui_mainwindow::view() -> presenter();`

##### Example :
   For topology
   ```cpp
   Gp_gui_topology & topology = Gp_gui_mainwindow::view() -> presenter() -> topology_model();
   ```
   For grids
   ```cpp
   Gp_gui_multiblock_grid_list & gp_grids = Gp_gui_mainwindow::view() -> presenter() -> grid_model()
   Gp_gui_multiblock_grid * curr_grid = gp_grids.get_current_grid();
   ```
   For cad model
   ```cpp
  Gp_gui_minicad & cad_model =  Gp_gui_mainwindow::view() -> presenter() -> cad_model()
  
   ```    


## Challenges in Porting
- Models contain view methods like `model.render()`
  Example : `topology.draw_surface_render()` which binds the model data structure to a render api paradigm 
## Solutions

### Temporary Solution : 
   Create a wrapper class to encapsulate all `OpenGL 2.1` , `OpenGL 3.3` calls into a custom Renderer API 

### Permanent Solution :
   Create a Proper `(RenderableEntity -> SceneRenderer)` abstraction system.
  
## New Renderer_API Reference & Guidelines :
   Create a gp_gui_class by inheriting the topology just like it is currently implemented & instead of maintaining a lot of variables , containers to store vertices, indices, color_data , surface_ids , etc 
   use RenderableEntity class to group together all required data. 
   
```cpp

class gp_gui_topology : public topology
{
public :
std::unordered_map<std::string, std::map<uint32_t, Renderer_API::RenderableEntity>> topo_surfaces,
std::unordered_map<std::string, Renderer_API::RenderableEntity> topo_corners, topo_edges;

// Member functions to create renderable entities and set flags

};

```
Example for setting corners:

```cpp
topo_corners["assigned_corners"].setVertexArray(vertexarray);
topo_corners["assigned_corners"].setColorArray(colorarray);
```

In paintGL 

```cpp
Gp_gui_topology & topology = Gp_gui_mainwindow::view() -> presenter() -> topology_model();
std::vector<Renderer_API::RenderableEntity>& RenderableEntitiesList = topology.getRenderableEntities(); 
Scene.Render(RenderableEntitiesList);
```


If you encounter any issues or have questions, please don't hesitate to [open an issue](https://github.com/srikargridpro/Graphics_API_documentation/issues) on GitHub.

Happy coding!
