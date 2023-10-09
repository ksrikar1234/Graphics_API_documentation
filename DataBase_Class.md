# Renderer_API : : Data_Base Class 
## Usage 
```cpp
Renderer_API::Data_Base DataBase;
Renderer_API::RenderableEntity topo_corners;

topo_corners["assigned_corners"].setVertexArray(vertex_array);
// Set some other data as well

uint64_t assigned_corners_entity_key = DataBase.addEntity(topo_corners["assigned_corners"]);
DataBase.getEntity(assigned_corners_entity_key)->vertex_array_ptr;
```

## Class Prototype
```cpp
namespace Renderer_API {
class Data_Base {

uint64_t Assignable_UUID;
std::unordered_map<uint64_t, RenderableEntity> RenderableEntities_DataBase;

Data_Base() : Assignable_UUID(0) {} // Starting Assigned ID is = 0
~Data_Base() {}

uint64_t addEntity(RenderableEntity& renderable_entity);
RenderableEntity* getEntity(uint64_t key);
// overload addEntity() & getEntity() to store & retrive other types of Entity Objects as well
};

}// namespace Renderer_API
```

## Class Implementation
```cpp

namespace Renderer_API {
    uint64_t Data_Base::addEntity(RenderableEntity& renderable_entity) {
        renderable_entity.UUID = Assignable_UUID;
        RenderableEntities_DataBase[renderable_entity.UUID] = renderable_entity;
        Assignable_UUID++;
        return renderable_entity.UUID; // Return the assigned UUID
    }

    RenderableEntity* Data_Base::getEntity(uint64_t key) {
        std::unordered_map<uint64_t, RenderableEntity>::iterator it = RenderableEntities_DataBase.find(key);
        if (it != RenderableEntities_DataBase.end()) {
            return &(it->second);
        }
        return nullptr; // Entity with the given key not found
    }
} // namespace Renderer_API


```
