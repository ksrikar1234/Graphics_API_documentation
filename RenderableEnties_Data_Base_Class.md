# RenderableEnties_Data_Base_Class 
## Usage 
```
Renderer_API::Data_Base DataBase;

uint64_t UUID = topo_corner["assigned_corners"].UUID;

DataBase.add(topo_corner["assigned_corners"]);


```

## Class Prototype
```cpp
namespace Renderer_API {

class Data_Base {

std::unordered_map<uint64_t, RenderableEntity*> RenderableEntities_DataBase;

void add(RenderableEntity& renderable_entity);

};

}// namespace Renderer_API
```

## Class Implementation
```cpp
namespace Renderer_API {

void Data_Base::add(RenderableEntity& renderable_entity)
{
  RenderableEntities_DataBase[renderable_entity.UUID] = &renderable_entity; 
}

};
```
