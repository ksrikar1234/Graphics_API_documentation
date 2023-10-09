# Graphics_API_Revamp_documentation

GridPro Graphics_API_Revamp_documentation.

## Table of Contents

- [About](#about)
- [Existing RenderPipeline](#existing-renderpipeline)
- [Challenges in Porting](#challenges-in-porting)
- [Solutions](#solutions)
- [Renderer API Reference](#renderer-api-reference)


## About

To replace Fixed pipeline approach with shader approach in GridPro WS. 

## Existing RenderPipeline

[Installation](Installation.md)

## Challenges in Porting

To get started with the HPS Application Framework, check out the [Getting Started Guide](./docs/getting-started.md) for detailed instructions on how to create your first project.

## Solutions

### Temporary Solution : 
    Create a wrapper class to encapsulate all draw calls

### Permanent Solution :
    Create a Proper (RenderableEntity -> SceneRenderer) abstraction system.
  
## New Renderer_API Reference & Guidelines

Renderer_API::RenderableEntity

```cpp

struct RenderableEntity {

uint64_t UUID;
uint32_t LayerID;
std::string name;

uint32_t vertex_buffer_object_id;
uint32_t vertex_array_object_id;
uint32_t shader_program_handle_id;

enum class Visibility            {TRUE, FALSE};
enum class PrimitiveType         {POINTS, LINES, LINE_STRIP , TRIANGLES , TRIANGLE_STRIP , QUAD};
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
   Material material;
   float color;
   float shininess;
   glm::vec3 ambient, diffuse , specular;
};

Material_pty material_pty;

// Should be implemented in Scene class
struct Lighting_pty
{   
   Lighting lighting;
   glm::vec3 ambient, diffuse , specular;
};

Lighting_pty lighting_pty;


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

   void set_vertex_attribute_array()
   {  
      if(this->vertex_attribute_array_ptr != nullptr) return;
         
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
   }
}; // struct VertexAttributes

VertexAttributes vertex_attributes;
glm::mat4 model_matrix;

};

```


If you encounter any issues or have questions, please don't hesitate to [open an issue](https://github.com/ksrikar1234/HPS_API_Documentation/issues) on GitHub.

Happy coding!
