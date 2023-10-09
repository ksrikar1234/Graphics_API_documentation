# RenderableEnties_Data_Base_Class 
## Usage 
```cpp
Renderer_API::Data_Base DataBase;
uint64_t UniqueKey = DataBase.addEntity(topo_corner["assigned_corners"]);
DataBase.getEntity(UniqueKey);
```

## Class Prototype
```cpp
namespace Renderer_API {
class Data_Base {

uint64_t Assignable_UUID;
std::unordered_map<uint64_t, RenderableEntity*> RenderableEntities_DataBase;

 Data_Base() { Assignable_UUID = 0; } // Starting Assigned ID is = 0
~Data_Base() {}

uint64_t addEntity(RenderableEntity& renderable_entity);
// overload add() to store other elements as well

RenderableEntity* getEntity(uint64_t key);

};

}// namespace Renderer_API
```

## Class Implementation
```cpp

namespace Renderer_API {
uint64_t Data_Base::addEntity(RenderableEntity& renderable_entity)
{
  renderable_entity.UUID = Assignable_UUID;
  Assignable_UUID++;
  RenderableEntities_DataBase[renderable_entity.UUID] = &renderable_entity; 
}

RenderableEntity* Data_Base::getEntity(uint64_t key)
{  return RenderableEntities_DataBase[key]; }

};
```
