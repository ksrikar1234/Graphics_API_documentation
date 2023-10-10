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

std::vector<float> vertex_array;
bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout ; return (input_layout > 0 ? true : false); }
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

}; // class VertexArray
} // namespace Renderer_API
#endif  // _VERTEX_ARRAY_CLASS_HPP_

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.cpp"
#endif
