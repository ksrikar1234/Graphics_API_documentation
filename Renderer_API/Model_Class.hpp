#ifndef _MODEL_CLASS_HPP_
#define _MODEL_CLASS_HPP_

#define USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.hpp"
#define USE_QT_OPENGL_LOADER
#include "Shader_Class.hpp"
#undef USE_HEADER_ONLY_IMPLEMENTATION

namespace Renderer_API {
class Model {
public :

uint64_t UUID;
uint32_t LayerID;
std::string name;

uint32_t VBO, VAO;

enum class PrimitiveType         {POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, QUADS, QUAD_STRIP};
enum class ShadeModel            {FLAT , SMOOTH};
enum class ColorSchema           {MONO, PER_PRIMITIVE, PER_VERTEX};
enum class PolygonMode           {POINTS, LINES, FILL};
enum class DisplayType           {NODisplay, DisplayHLR, DisplayShade, DisplayShadeHLR, DisplayLines, DisplayPoints}

enum Visibility_Flag             {ENABLE, DISABLE};
enum Material_Flag               {ENABLE, DISABLE};
enum Lighting_Flag               {ENABLE, DISABLE};

Visibility_Flag visibility;
void setVisibilityFlag(Visibility_Flag flag);

PrimitiveType primitive_type;
float primitive_thickness;
void setPrimitive(PrimitiveType primitive_type, float primitive_thickness);

PolygonMode polygon_mode;
void setPolygonMode(PolgonMode polygon_mode);

VertexArray vertex_array;
VertexArray::AttribLayout layout;
void setVertexAttribLayout(VertexArray::AttribLayout layout);
void setVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal);
void updateVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal);
void setIndexData(std::vector<uint32_t>& index_array);

Shader ModelShader;
ShadeModel shade_model;
void setShadeModel();

struct Material
{
   Material_Flag material_flag
   float color;
   float shininess;
   float ambient[3], diffuse[3] , specular[3];
};
Material ModelMaterial;
void setModelMaterial(Material model_material);

void setLighting(bool Lighting_Switch_Flag);

void render();

};

} // namespace Renderer_API
#endif // _MODEL_CLASS_HPP_
