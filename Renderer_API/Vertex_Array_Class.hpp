#ifndef _VERTEX_ARRAY_CLASS_HPP_
#define _VERTEX_ARRAY_CLASS_HPP_
#include <cstdint>
#include <vector>
#include <iostream>
namespace Renderer_API {

class VertexArray {
public :
enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;

 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

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

float* getPosition() { return this->position;}
float* getColor()    { return this->color;   }
float* getNormal()   { return this->normal;  }

bool setPosition(float x, float y, float z) 
{
 if(layout > 0) {
 this->x = x;  this->y = y;  this->z = z;
 this->position[0] = x; this->position[1] = y; this->position[2] = z;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;

 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 0 ;
   (*(this->vertex_array_head))[index*stride_len + i + offset] = this->position[i];
 }
 return true;
 }
 return false;
}

bool setColor(float r, float g, float b) 
{
 if(layout == 2 || layout == 4) {
 this->r = r;  this->g = g;  this->b = b;
 this->color[0] = r; this->color[1] = g; this->color[2] = b;
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = 3 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->color[i];
 }
 return true;
 }
 return false;
}

bool setNormal(float n1, float n2, float n3) 
{
 if(layout == 3 || layout == 4) {
 this->n1 = n1;  this->n2 = n2;  this->n3 = n3;
 this->normal[0] = n1; this->normal[1] = n2; this->normal[2] = n3;
 
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   const uint32_t offset = (layout == 3) ? 3 : 6 ;
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->normal[i];
 }
 return true;
 }
 return false; 
}
};

Vertex curr_vertex;

Vertex operator[](uint32_t index)
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
 return vertex;
}

std::vector<float> vertex_array;
bool setLayout(AttribLayout input_layout)  {  this->layout = input_layout ; return (input_layout > 0 ? true : false); }
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

}; // class VertexArray
} // namespace Renderer_API
#endif  // _VERTEX_ARRAY_CLASS_HPP_

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Vertex_Array_Class.cpp"
#endif
