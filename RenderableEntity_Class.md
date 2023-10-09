## RenderableEntity class 
### Usage
```cpp

{
// Localised Namespace

using namespace Renderer_API;
RenderableEntity linear_surface_segment;

linear_surface_segment.UUID = 1234;

linear_surface_segment.setPrimitiveType(PrimitiveType::QUADS);
linear_surface_segment.setColorSchema(ColorSchema::PER_PRIMITIVE);
linear_surface_segment.setVertexAttributeLayout(VertexAttributeLayout::VCN);

linear_surface_segment.setVertexArray(vertex_array);
linear_surface_segment.setColorArray(color_array);
linear_surface_segment.setNormalArray(normal_array);

topo_surfaces[linear_surface_segments][1] = linear_surface_segment;

// Localised Namespace
}

```


### implemetation

```cpp

namespace Renderer_API {


enum class PrimitiveType         {POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, QUADS, QUAD_STRIP };
enum class ShadeModel            {FLAT , SMOOTH};
enum class ColorSchema           {MONO, PER_PRIMITIVE, PER_VERTEX};
enum class PolygonMode           {POINTS, LINES, FILL};

enum Visibility_Flag             {ENABLE, DISABLE};
enum Material_Flag               {ENABLE, DISABLE};
enum Lighting_Flag               {ENABLE, DISABLE};
enum VertexAttributeLayout       {V, VC, VN, VCN};

struct RenderableEntity {

uint64_t UUID;
uint32_t LayerID;
std::string name;

uint32_t vertex_buffer_object_id;
uint32_t vertex_array_object_id;
uint32_t shader_program_handle_id;
glm::mat4 model_matrix;

Visibility_Flag visibility;
PrimitiveType primitive_type;
ShadeModel shade_model;
PolygonMode polygon_mode;
float primitive_thickness;

struct Material_pty
{
   Material_Flag material_flag
   float color;
   float shininess;
   glm::vec3 ambient, diffuse , specular;
};

Material_pty material_pty;

struct VertexAttributes 
{
   VertexAttributeLayout vertex_attribute_layout;
   std::vector<float>* position_array_ptr; std::vector<float>* color_array_ptr; std::vector<float>* normal_array_ptr;
   std::vector<uint32_t>* index_array_ptr;
   std::vector<float>  vertex_attribute_array;
   std::vector<float>* vertex_attribute_array_ptr;

   
   VertexAttributes() : position_array_ptr(nullptr), color_array_ptr(nullptr), normal_array_ptr(nullptr), 
                        index_array_ptr(nullptr) , vertex_attribute_array_ptr(nullptr)                 
   {
      /* Constructor*/
      visibility = Visibility_Flag::ENABLE;
   }

   ~VertexAttributes()
   {
      /* Destructor */
      vertex_attribute_array.resize(0);
   }

VertexAttributes vertex_attributes;

void set_vertex_attribute_array();  

// Getters & setters

};
} // namespace Renderer_API
```

## Method Implementations
###  1. set_vertex_attribute_array()

- set_vertex_attribute_array() is used to accumulate all vertex attributes into a interleaved array

- `set_vertex_attribute_array()` implementation



```cpp

namespace Renderer_API {

void RenderableEntity::set_vertex_attribute_array()
   {  
      if(this->vertex_attribute_array_ptr != nullptr) return; // That means Vertex Attribute Array is externally generated & its location is assigned
         
      uint32_t n = vertex_attribute_layout;
      // Fancy way of saying layout of Vertex array = { {vertex} , {color} , {normal} } set of combinations { V , VC , VN , VCN}
      n = n > 0 ? (n <= 2 ? 2 : 3) : 1;
    
      this->vertex_attribute_array.reserve(n*position_array_ptr->size());
      
      for(size_t vertex_id = 0; vertex_id < position_array_ptr->size()*n; vertex_id += n)
         {       
            if(this->position_array_ptr != nullptr && this->position_array_ptr->size() != 0 )
              {
               this->vertex_attribute_array.push_back((*this->position_array_ptr)[vertex_id]);
               this->vertex_attribute_array.push_back((*this->position_array_ptr)[vertex_id+1]);
               this->vertex_attribute_array.push_back((*this->position_array_ptr)[vertex_id+2]);
              }

            if(vertex_attribute_layout == 1 || vertex_attribute_layout == 3 )
              {           
               if(this->color_array_ptr != nullptr && this->color_array_ptr->size() != 0 )
                 {
                   this->vertex_attribute_array.push_back((*this->color_array_ptr)[vertex_id]);
                   this->vertex_attribute_array.push_back((*this->color_array_ptr)[vertex_id+1]);
                   this->vertex_attribute_array.push_back((*this->color_array_ptr)[vertex_id+2]);
                 }
              }

           if(vertex_attribute_layout == 2 || vertex_attribute_layout == 3 )
             {
              if(this->normal_array_ptr != nullptr && this->normal_array_ptr->size() != 0 )
                {
                 this->vertex_attribute_array.push_back((*this->normal_array_ptr)[vertex_id]);
                 this->vertex_attribute_array.push_back((*this->normal_array_ptr)[vertex_id+1]);
                 this->vertex_attribute_array.push_back((*this->normal_array_ptr)[vertex_id+2]);
                }
            }
         }
   } /* for loop for VA array end */
}; // struct VertexAttributes

}
```

