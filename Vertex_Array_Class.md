## Usage
- Declare `Renderer_API::VertexArray`
```cpp
Renderer_API::VertexArray TopoSurfaceVertexArray;
TopoSurfaceVertexArray.setLayout(Renderer_API::VertexArray::AttribLayout::VCN);
```
- Create or Set Vertex Data
```cpp
std::vector<float> pos = {1,2,3}, norm = {1,2,3}, color = {1,2,3};

```
- Build the VertexArray
```cpp
TopoSurfaceVertexArray.BuildVertexArray(&pos, &color, &norm); // its ok to destroy pos, norm, color vectors
```
- Get Attribute Data by using Vertex Data structure
  ```cpp
  Renderer_API::VertexArray::Vertex vertex = TopoSurfaceVertexArray[0];
  ```
- Get Attribute Data by indexing
```cpp
float* x = TopoSurfaceVertexArray[0].getColor();
float* y = TopoSurfaceVertexArray[0].getPosition();
float* x = TopoSurfaceVertexArray[0].getNormal();
```
- Get Position Data by x, y, z notation
```cpp
TopoSurfaceVertexArray[0].x
TopoSurfaceVertexArray[0].y
TopoSurfaceVertexArray[0].z
```
- Get Color Data by r, g, b notation
```cpp
TopoSurfaceVertexArray[0].r
TopoSurfaceVertexArray[0].g
TopoSurfaceVertexArray[0].b
```
- Get Normal Data by n1, n2, n3 notation
```cpp
TopoSurfaceVertexArray[0].n1
TopoSurfaceVertexArray[0].n2
TopoSurfaceVertexArray[0].n3
```
- Push New Vertex (not recomended for high number of push_backs, Use BuildVertexArray() for constructing large portions of array)
```cpp
Renderer_API::VertexArray::Vertex dummy_vertex;
dummy_vertex.setLayout(Renderer_API::VertexArray::AttribLayout::VCN);
dummy_vertex.setPosition(2,3,4);
dummy_vertex.setColor(9,9,9);
dummy_vertex.setNormal(0,0,0);
TopoSurfaceVertexArray.push_back(dummy_vertex);

```
- Update using updateAttrib() (Use this for small updates)
```cpp
TopoSurfaceVertexArray[0].updateColor(2,2,2);
```
- Update using UpdateVertexArray() (Use this for large updates.)
```cpp
std::vector<float> new_color = {3,4,5},
TopoSurfaceVertexArray.UpdateVertexArray(nullptr, new_color, nullptr);
```

## Class Protoype
```cpp
namespace Renderer_API {
class VertexArray {
public :
enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;

 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

struct Vertex {

Vertex* vertex_head = nullptr;
std::vector<float>* vertex_array_head = nullptr;
uint32_t index;

AttribLayout layout;

float position[3];
float color[3];
float normal[3];

float x, y, z;
float r, g, b;
float n1, n2, n3;

float* getPosition() { return this->position;}
float* getColor()    { return this->color;   }
float* getNormal()   { return this->normal;  }

bool update();
bool setLayout(AttribLayout input_layout);

bool setPosition(float x, float y, float z); 
bool setColor(float r, float g, float b); 
bool setNormal(float n1, float n2, float n3);

bool updatePosition(float x, float y, float z); 
bool updateColor(float r, float g, float b); 
bool updateNormal(float n1, float n2, float n3);
}; // Struct Vertex

Vertex curr_vertex;
std::vector<float> vertex_array;
bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout ; return (input_layout > 0 ? true : false); }

std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);
std::vector<float>* UpdateVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

bool push_back(Vertex vertex);

Vertex operator[](uint32_t index)
{
 uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 uint32_t stride_len = n*3;
 
 Vertex& vertex = this->curr_vertex;
 vertex.vertex_array_head = &(this->vertex_array);
 vertex.layout = this->layout;
 vertex.index = index;

 for(std::size_t i = 0 ; i < 3 ; ++i)
 {
   vertex.position[i] = this->vertex_array[index*stride_len + i];
   if(layout == 2 || layout == 4) 
   vertex.color[i]    = this->vertex_array[index*stride_len + 3 + i]; // color offset = 3 
   if(layout == 3)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 3 + i]; // normal offset = 3
   if(layout == 4)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 6 + i]; // normal offset = 6
 }
 
 vertex.update();
 return vertex;
}

}; // class VertexArray
} // namespace Renderer_API
```


## Class Methods Implementation
- `std::vector<float>* BuildVertexArray(<args>)` method implementation

```cpp

namespace Renderer_API {

std::vector<float>* VertexArray::BuildVertexArray(std::vector<float>* position = nullptr,
                                                  std::vector<float>* color = nullptr,
                                                  std::vector<float>* normal = nullptr) 
{
    assert(this->layout != NONE
           && "Set Layout of VertexArray.layout = Renderer_API::VertexArray::<args = {V, VC, VN, VCN}>");
    assert(position != nullptr && "No Positon array is given");

    if(this->layout == 2 || this->layout == 4) {
       assert(color != nullptr
              && "Color Array data not given but Layout is set to load Color Data [VC] or [VCN]");
       assert(color->size() == position->size()
             && "Sizeof ColorArrayData != Sizeof PositionArrayData"); 
     }

    if(this->layout == 3 || this->layout == 4) {
       assert(normal != nullptr
              && "Normal Array data not given but Layout is set to load Normal Data [VN] or [VCN]");
       assert(normal->size() == position->size()
              && "Sizeof NormalArrayData != Sizeof PositionArrayData"); 
    }

    for(std::size_t vertex_id = 0; vertex_id < (position->size())/3; ++vertex_id )
       {
         this->vertex_array.push_back((*position)[vertex_id+0]);
         this->vertex_array.push_back((*position)[vertex_id+1]);
         this->vertex_array.push_back((*position)[vertex_id+2]);

         if(color != nullptr)
           {
             this->vertex_array.push_back((*color)[vertex_id+0]);
             this->vertex_array.push_back((*color)[vertex_id+1]);
             this->vertex_array.push_back((*color)[vertex_id+2]);
           }

         if(normal != nullptr)
           {
             this->vertex_array.push_back((*normal)[vertex_id+0]);
             this->vertex_array.push_back((*normal)[vertex_id+1]);
             this->vertex_array.push_back((*normal)[vertex_id+2]);
           }

       } 
       
     return &this->vertex_array;     
};
}// namespace Renderer_API
```
  
