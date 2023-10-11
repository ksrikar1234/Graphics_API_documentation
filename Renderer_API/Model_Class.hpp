#ifndef _MODEL_CLASS_HPP_
#define _MODEL_CLASS_HPP_
#define USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.hpp"

namespace Renderer_API {
class Model {
public :

uint32_t VBO, VAO;
VertexArray vertex_array; 
Shader ModelShader;




};




} // namespace Renderer_API
#endif // _MODEL_CLASS_HPP_
