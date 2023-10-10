#ifndef _VERTEX_ARRAY_CLASS_HPP_
#define _VERTEX_ARRAY_CLASS_HPP_
#include <cstdint>
#include <vector>
namespace Renderer_API {

class VertexArray {
public :
enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;

 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

struct Vertex {
float position[3];
float color[3];
float normal[3];
float* getPosition() { return this->position;}
float* getColor()    { return this->color;   }
float* getNormal()   { return this->normal;  }
};

Vertex operator[](int index)
{
 uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1 ;
 uint32_t stride_len = n*3;
 Vertex vertex;
 for(size_t i = 0 ; i < 3 ; ++i)
 {
   vertex.position[i] = this->vertex_array[index*stride_len + i];
   if(n == 2 || n == 4)
   vertex.color[i]    = this->vertex_array[index*stride_len + 3 + i]; // color offset = 3
   if(n == 3)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 3 + i]; // normal offset = 3
   if(n == 4)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 6 + i]; // normal offset = 6
 }
 return vertex;
}

bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout ; return (input_layout > 0 ? true : false); }
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

private :
std::vector<float> vertex_array;
}; // class VertexArray
} // namespace Renderer_API
#endif  // _VERTEX_ARRAY_CLASS_HPP_

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.cpp"
#endif
