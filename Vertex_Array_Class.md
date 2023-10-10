## Usage
```cpp

Renderer_API::VertexArray TopoSurfaceVertexAttribArray;
TopoSurfaceVertexAttribArray.setVertexArray(&position_array, &color_array,  &normal_araay);
TopoSurfaceVertexAttribArray[1].getPosition();

float x, y ,z;
TopoSurfaceVertexAttribArray[1].setPosition(x, y, z);

```

## Class Protoype
```cpp
namespace Renderer_API {
enum AttribLayout { NONE, V, VC, VN, VCN };
class VertexArray {
public :

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

bool setPosition(float x, float y, float z) 
{
 if(layout > 0) {
 this->x = x;  this->y = y;  this->z = z;
 this->position[0] = x; this->position[1] = y; this->position[2] = z;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;

 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 0 ;
   (*(this->vertex_array_head))[index*stride_len + i + offset] = this->position[i];
 }
 return true;
 }
 return false;
}

bool setColor(float r, float g, float b) 
{
 if(layout == 2 || layout == 4) {
 this->r = r;  this->g = g;  this->b = b;
 this->color[0] = r; this->color[1] = g; this->color[2] = b;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 3 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->color[i];
 }
 return true;
 }
 return false;
}

bool setNormal(float n1, float n2, float n3) 
{
 if(layout == 3 || layout == 4) {
 this->n1 = n1;  this->n2 = n2;  this->n3 = n3;
 this->normal[0] = n1; this->normal[1] = n2; this->normal[2] = n3;
 
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = (layout == 3) ? 3 : 6 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->normal[i];
 }
 return true;
 }
 return false; 
}
};

Vertex curr_vertex;

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
 return vertex;
}

std::vector<float> vertex_array;
bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout ; return (input_layout > 0 ? true : false); }
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

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
  
