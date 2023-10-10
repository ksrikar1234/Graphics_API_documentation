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
float* getColor() { return this->color;}
float* getNormal() { return this->normal;}
};

Vertex operator[](int index)
{
 
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
