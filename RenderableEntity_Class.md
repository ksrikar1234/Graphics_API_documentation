## RenderableEntity class implemetation

```cpp
struct RenderableEntity {

uint64_t UUID;
uint32_t LayerID;
std::string name;

uint32_t vertex_buffer_object_id;
uint32_t vertex_array_object_id;
uint32_t shader_program_handle_id;

enum class Visibility            {TRUE, FALSE};
enum class PrimitiveType         {POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, QUADS, QUAD_STRIP };
enum class ShadeModel            {FLAT , SMOOTH};
enum class ColorSchema           {MONO, PER_PRIMITIVE, PER_VERTEX};
enum class PolygonMode           {POINTS, LINES, FILL};
enum class Material              {ENABLE, DISABLE};
enum class Lighting              {ENABLE, DISABLE};

Visibility visibility;
PrimitiveType primitive_type;
PolygonMode polygon_mode;
float primitive_thickness;

ShadeModel shade_model;

struct Material_pty
{   
   float color;
   float shininess;
   glm::vec3 ambient, diffuse , specular;
};

Material_pty material_pty;

struct VertexAttributes 
{

   std::vector<float>* position_array_ptr = nullptr;
   std::vector<float>* color_array_ptr = nullptr;
   std::vector<float>* normal_array_ptr = nullptr;
   std::vector<uint32_t>* index_array_ptr = nullptr;
   
   std::vector<float>  vertex_attribute_array;
   std::vector<float>* vertex_attribute_array_ptr = nullptr;

   enum VertexAttributeLayout {V, VC, VN, VCN};
  
   VertexAttributeLayout vertex_attribute_layout;
   
   VertexAttributes() : position_array_ptr(nullptr), color_array_ptr(nullptr), normal_array_ptr(nullptr), 
                        index_array_ptr(nullptr) , vertex_attribute_array_ptr(nullptr)                 
   {
      /* Constructor*/
   }

   ~VertexAttributes()
   {
      /* Destructor */
      vertex_attribute_array.resize(0);
   }

  
VertexAttributes vertex_attributes;
glm::mat4 model_matrix;

};

```

- `set_vertex_attribute_array()` implementation


```cpp

void RenderableEntity::set_vertex_attribute_array()
   {  
      if(this->vertex_attribute_array_ptr != nullptr) return; // That means Vertex Attribute Array is externally generated & its location is assigned
         
      uint32_t n = vertex_attribute_layout + 1; 
      n = n > 3 ? 3 : n;    
      
      this->vertex_attribute_array.reserve(n*position_array_ptr->size());

      if(this->vertex_attribute_array.capacity()){}
      
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

```

