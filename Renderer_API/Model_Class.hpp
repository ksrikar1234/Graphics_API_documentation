#pragma once
#ifndef _MODEL_CLASS_HPP_
#define _MODEL_CLASS_HPP_

#define USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.hpp"
#define USE_QT_OPENGL_LOADER
#include <QOpenGLFunctions_3_3_Compatibility>
#include "Shader_Class.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Renderer_API {

void PrintDebugMsg(std::string debug_message)
{
   #ifdef RENDERER_API_ENABLE_DEBUG_MESSAGING
   std::cout << debug_message << "\n" ;
   #endif
}

class Model : protected QOpenGLFunctions_3_3_Compatibility {
public :

 Model ();
~Model();

uint64_t UUID;
uint32_t LayerID;
std::string name;
                                  
enum class PrimitiveType         {POINTS, LINES, LINE_STRIP, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, QUADS, QUAD_STRIP};
enum class ShadeModel            {FLAT , SMOOTH};
enum class ColorSchema           {MONO, PER_PRIMITIVE, PER_VERTEX};
enum class PolygonMode           {POINTS, LINES, FILL};
enum class DisplayType           {NODisplay, DisplayHLR, DisplayShade, DisplayShadeHLR, DisplayLines, DisplayPoints};

enum class Visibility_Flag             {ENABLE, DISABLE};
enum class Material_Flag               {ENABLE, DISABLE};
enum class Lighting_Flag               {ENABLE, DISABLE};

Visibility_Flag model_visibility;
void setVisibilityFlag(Visibility_Flag visibility_flag);

PrimitiveType primitive_type = PrimitiveType::POINTS;
float primitive_thickness;
void setPrimitive(PrimitiveType primitive_type, float primitive_thickness);

PolygonMode polygon_mode;
void setPolygonMode(PolygonMode polygon_mode);

std::vector<GLuint> index_array;
VertexArray vertex_array;

VertexArray::AttribLayout layout;
void setVertexAttribLayout(VertexArray::AttribLayout layout);
void setVertexAttribData(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);
void updateVertexAttribData(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);
void setIndexData(std::vector<uint32_t>& index_array);

glm::mat4 ProjectionMatrix, ViewMatrix, ModelMatrix;
void Setup_MVP(glm::mat4 SceneProjectionMatrix, glm::mat4 SceneViewMatrix, glm::mat4 ModelMatrix);

ShadeModel shade_model;
void setShadeModel(ShadeModel);

struct Material
{
   Material_Flag material_flag;
   float color;
   float shininess;
   glm::vec3 ambient, diffuse, specular;
  // float ambient[3], diffuse[3] , specular[3];
};

GLfloat model_color;
GLfloat Shininess;
glm::vec3 Ambient, Diffuse, Specular; 
Material model_material;

void SetMaterialProperties(float shininess, glm::vec3 ambient , glm::vec3 diffuse , glm::vec3 specular );
void setModelMaterial(Material model_material);

Lighting_Flag lighting_flag;
void setLighting(bool Lighting_Switch_Flag);

void SelectShader(std::string Name, const char* vertexShaderSource, const char* fragmentShaderSource);
void render();

void gl_error();
void GetFirstNMessages(GLuint numMsgs);

private :

GLenum GL_primitive_type = GL_POINTS;
GLuint VBO, VAO, IBO;
void CreateVertexBuffer();

OpenGL_Shader ModelShader;
std::unordered_map<std::string, GLuint> uniformLocations;
std::unordered_map<std::string, GLuint> VertexAttributeLocations;

bool already_setup_uniform = false;
void Setup_Uniforms();
void Update_Uniforms();

};

} // namespace Renderer_API
#endif // _MODEL_CLASS_HPP_

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Model_Class.cpp"
#undef USE_HEADER_ONLY_IMPLEMENTATION
#endif
