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

- gp_gui_glwidget class
- paintGL 
- Get avaliable gp_gui_model from Gp_gui_mainwindow::view() -> presenter();
### Each gp_gui_model is derived from a core data structure that contain the actual buisness logic
### Example :

   ```cpp
   Gp_gui_mainwindow::view() -> presenter() -> topology_model();
   ```

   ```cpp
   Gp_gui_multiblock_grid_list & gp_grids = Gp_gui_mainwindow::view() -> presenter() -> grid_model()
   Gp_gui_multiblock_grid * curr_grid = gp_grids.get_current_grid();
   ```
   
   ```cpp
   Gp_gui_mainwindow::view() -> presenter() -> cad_model()
   ```    

  
 
Primary Data Structures : 



Surface
Topology
Grid
cad_model
Data is 




## Challenges in Porting

To get started with the HPS Application Framework, check out the [Getting Started Guide](./docs/getting-started.md) for detailed instructions on how to create your first project.

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
}

```


If you encounter any issues or have questions, please don't hesitate to [open an issue](https://github.com/ksrikar1234/HPS_API_Documentation/issues) on GitHub.

Happy coding!
