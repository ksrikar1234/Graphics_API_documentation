# Graphics_API_Revamp_documentation

GridPro Graphics_API_Revamp_documentation.

## Table of Contents

- [About](#about)
- [Existing RenderPipeline](#existing-renderpipeline)
- [Challenges in Porting](#challenges-in-porting)
- [Solutions](#solutions)
- [Renderer API Usage](#renderer-api-usage)
- [Renderer API Reference](#renderer-api-reference)

## About

To replace Fixed pipeline approach with shader approach in GridPro WS. 

## Existing RenderPipeline

Existing RenderPipeline Structure & Configuration exists as
- MVP pattern is used to seperate `MODEL <-> PRESENTER_LAYER <-> VIEW`
  using `Gp_gui_Models <-> Gp_gui_presenter <-> Gp_gui_view` classes  
- A class derived from `QApplication` class called -> `Gp_gui_Application` which has `Gp_gui_mainwindow`
- `Gp_gui_mainwindow` has subwindow attached called `gp_gui_glwidget`
- `gp_gui_glwidget` class is derived from `QOGLWiget`, is used to setup windowing, OpenGL context,
   Scene Configuration (Not Exactly but setting up mvp from camera pos , view volume evaluation , peripheral input handling etc...) 
- `gp_gui_glwidget::paintGL()` is where frame rendering starts.
-  Inside `gp_gui_glwidget::paintGL`, a reference for gp_gui_model objects are accquired.
  
#### What are gp_gui_models ??
   Since bare data structures like topology do not contain all the data to represent all visual aspects of topology model,
   a new model data structure is built by inheriting base topology data structure & additionally data members & methods are created
   for rendering all aspects, properties of topology model.
   
#### Each gp_gui_model is derived from a core data structure that contain the actual buisness logic
-  Get avaliable gp_gui_model from `Gp_gui_mainwindow::view() -> presenter();`

#### Example :
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
#### Rendering is done using a render method implemented in gp_gui_model class
```cpp
  topology.draw_surface_displaylist()`
```
## Challenges in Porting
- Models contain view methods like `model.render()`
- Example : `topology.draw_surface_render()` which binds the model data structure to a render api paradigm.
- Mild & Extreme Explicit API's like `OpenGL 3.3, OpenGL 4.3` & `Vulkan , DirectX` cannot be used in this manner.
     
## Solutions

### Temporary Solution : 
- Create a wrapper class to encapsulate all `OpenGL 2.1` , `OpenGL 3.3` calls into a custom Renderer API & replace them. (Not an Elegant solution as i thought initially) 

### Permanent Solution :
- Create a Proper `(RenderableEntity -> SceneRenderer)` abstraction system. Seperate the `Model_Data` `<->` `Renderer` properly.
- No Graphics API calls inside Model class should allowed
- Use a Scene Class to manage
- `Camera System.`
- `Calculation of view-projection matrices.`
- `Setiing Lighting Parameter & Properties.`
- `Setting model Visibility flags.`
    
## Renderer API Usage 
- Create a gp_gui_class by inheriting the topology (already implemented) & instead of maintaining a lot of variables , containers to store vertices, indices, color_data ,    
   surface_ids , etc 
- Use [RenderableEntity](RenderableEntity_Class.md) class to group together all required data. 
   
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

topo_corners["assigned_corners"].setPrimitiveType(Renderer_API::PrimitiveType::POINTS);
topo_corners["assigned_corners"].setVertexArray(vertexarray);

topo_corners["assigned_corners"].setColorSchema(Renderer_API::ColorSchema::PER_VERTEX);
topo_corners["assigned_corners"].setColorArray(colorarray);

//Optional
float shininess;
glm::vec3 ambient, diffuse, specular;
topo_corners["assigned_corners"].setMaterialPty(ambient, diffuse, specular, shininess);


```


Example for setting other 3d linear surface segments:

```cpp

topo_surfaces["linear_surface_segments"][1].setPrimitiveType(Renderer_API::PrimitiveType::POINTS);
topo_surfaces["linear_surface_segments"][1].setVertexArray(vertexarray);

topo_surfaces["linear_surface_segments"][1].setColorSchema(Renderer_API::ColorSchema::PER_PRIMITIVE);

float shininess;
glm::vec3 ambient, diffuse, specular;

topo_surfaces["linear_surface_segments"][1].setMaterialPty(ambient, diffuse, specular, shininess);
topo_surfaces["linear_surface_segments"][1].setColorArray(colorarray);

```

In paintGL use [Scene Class](Scene_Class.md) class object to render

```cpp

Gp_gui_topology & topology = Gp_gui_mainwindow::view() -> presenter() -> topology_model();

if(topology.isUpdated())
topology.updateRenderableEntities(); // ReEvaluate the RenderableEntities based on flags other wise cached data is rendered

std::vector<Renderer_API::RenderableEntity>& Topo_RenderableEntitiesList = topology.getRenderableEntities(); 

Scene.Render(Topo_RenderableEntitiesList, topology_display_flags);

// Similarly for Grids, Cad Model, Control Net


```


If you encounter any issues or have questions, please don't hesitate to [open an issue](https://github.com/srikargridpro/Graphics_API_documentation/issues) on GitHub.

Happy coding!
