/*
  author: Srikar Kadiyam <srikar@gridpro.com>
 -----------------------------------------------+
  Interleaved VertexArray Data structure :
 -----------------------------------------------+
  An Interleaved Array Data structure to efficiently build, update & pass it to OpenGL Buffers &
  Shaders. Enables Bandwidth Optimisation by cache Locality.
  Provides Convenience structures & functions to access data across the strides     
*/

#ifndef _VERTEX_ARRAY_CLASS_HPP_
#define _VERTEX_ARRAY_CLASS_HPP_
#include <cstdint>
#include <vector>

namespace Renderer_API {
class VertexArray {
public :
 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;
bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout; this->vertex_array.resize(0) ; return (input_layout > 0 ? true : false); }

struct Vertex {

Vertex* vertex_head = nullptr;
std::vector<float>* vertex_array_head = nullptr;
uint32_t index;

AttribLayout layout;

float position[3];
float color[3];
float normal[3];

float x, y, z;
float r, g, b;
float n1, n2, n3;

 Vertex() : layout(AttribLayout::NONE) {}
~Vertex() {}

float* getPosition() { return ((layout != 0) ?  this->position :  nullptr );}
float* getColor()    { return ((layout == 2 || layout == 4) ?  this->color  : nullptr); }
float* getNormal()   { return ((layout == 3 || layout == 4) ?  this->normal :  nullptr); }

bool setLayout(AttribLayout input_layout);

bool updateAliases();

bool setPosition(float x, float y, float z); 
bool setColor(float r, float g, float b); 
bool setNormal(float n1, float n2, float n3);

bool updatePosition(float x, float y, float z); 
bool updateColor(float r, float g, float b); 
bool updateNormal(float n1, float n2, float n3);

bool updateArray();
};

Vertex curr_vertex;

std::vector<float> vertex_array;
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);
std::vector<float>* UpdateVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

bool push_back(Vertex vertex);

Vertex& operator[](uint32_t index)
{
 uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 uint32_t stride_len = n*3;
 
 Vertex& vertex = this->curr_vertex;
 vertex.vertex_array_head = &(this->vertex_array);
 vertex.layout = this->layout;
 vertex.index = index;

 for(std::size_t i = 0 ; i < 3 ; ++i)
 {
   vertex.position[i] = this->vertex_array[index*stride_len + i];
   if(layout == 2 || layout == 4) 
   vertex.color[i]    = this->vertex_array[index*stride_len + 3 + i]; // color offset = 3 
   if(layout == 3)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 3 + i]; // normal offset = 3
   if(layout == 4)
   vertex.normal[i]   = this->vertex_array[index*stride_len + 6 + i]; // normal offset = 6
 }
 
  vertex.updateAliases();
 return vertex;
}

}; // class VertexArray
} // namespace Renderer_API
#endif  // _VERTEX_ARRAY_CLASS_HPP_

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.cpp"
#endif
