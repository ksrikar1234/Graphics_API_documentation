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
class VertexArray {

public :
enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;

 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

float vertex_array;
bool setLayout(Renderer_API::VertexArray::AttribLayout input_layout) : layout(input_layout) {}
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

};
} // namespace Renderer_API
```


## Class Methods Implementation
- `setVertexArray(<args>)` method implementation

```cpp

namespace Renderer_API {

std::vector<float>* VertexArray::BuildVertexArray(std::vector<float>* position = nullptr,
                                                  std::vector<float>* color = nullptr,
                                                  std::vector<float>* normal = nullptr) 
{
    assert(this->layout != NONE
           && "Set Layout of VertexArray.layout = Renderer_API::VertexArray::<args = {V, VC, VN, VCN}>");
    assert(position != nullptr && "No Positon array is given");

    if(this->layout = 2 || this->layout = 4) {
       assert(color != nullptr
              && "Color Array data not given but Layout is set to load Color Data [VC] or [VCN]");
       assert(color->size() = position->size()
             && "Sizeof ColorArrayData != Sizeof PositionArrayData"); 
     }

    if(this->layout = 3 || this->layout = 4) {
       assert(normal != nullptr
              && "Normal Array data not given but Layout is set to load Normal Data [VN] or [VCN]");
       assert(normal->size() = position->size()
              && "Sizeof NormalArrayData != Sizeof PositionArrayData"); 
    }

   uint32_t n = (layout > 1) ? (layout > 3 ? 3 : 2) : 1 ;
   /*
   switch (layout) {
    case 1:
        n = 1;
        break;
    case 2:
    case 3:
        n = 2;
        break;
    case 4:
        n = 3;
        break;
    default:
        assert(layout <= 4);
        break;
}
*/

    for(size_t vertex_id = 0; vertex_id < n*position->size(); ++vertex_id )
       {
         this->vertex_array.push_back((*position)[vertex_id+0]);
         this->vertex_array.push_back((*position)[vertex_id+1]);
         this->vertex_array.push_back((*position)[vertex_id+2]);

         if(color != nullptr)
           {
             this->vertex_array.push_back((*color)[vertex_id+3]);
             this->vertex_array.push_back((*color)[vertex_id+4]);
             this->vertex_array.push_back((*color)[vertex_id+5]);
           }

         if(normal != nullptr)
           {
             this->vertex_array.push_back((*normal)[vertex_id+6]);
             this->vertex_array.push_back((*normal)[vertex_id+7]);
             this->vertex_array.push_back((*normal)[vertex_id+8]);
           }

       }     
}
```
  
