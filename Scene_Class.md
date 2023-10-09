# Scene Class

## Usage :
```cpp
Renderer_API::Scene Scene;
Scene.SetLighting(ambient, diffuse, specular, color);
Scene.Render(RenderableEntitiesArray, Display_Flags);
```

## Class Prototype :
```cpp
namespace Renderer_API {

class RenderableEntity;
class Scene {
public :
void Render(std::vector<RenderableEntity> , Display_Flags topo_display_flags)
};

} // Renderer_API

```
## Class Methods Implementation :
```cpp
// TO be done
```
