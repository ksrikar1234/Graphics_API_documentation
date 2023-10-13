/*
  author: Srikar Kadiyam <srikar@gridpro.com>
 -----------------------------------------------+
  Interleaved VertexArray Data structure :
 -----------------------------------------------+
  An Interleaved Array Data structure to efficiently build, update & pass it to OpenGL Buffers &
  Shaders. Enables Bandwidth Optimisation by cache Locality.
  Provides Convenience structures & functions to access data across the strides     
*/

#ifndef _VERTEX_ARRAY_CLASS_CPP_
#define _VERTEX_ARRAY_CLASS_CPP_

#include <cassert>
#include "Vertex_Array_Class.hpp"

namespace Renderer_API {

std::vector<float>* VertexArray::BuildVertexArray(std::vector<float>* position = nullptr,
                                                  std::vector<float>* color = nullptr,
                                                  std::vector<float>* normal = nullptr) 
{
    assert(this->layout != NONE
           && "Set Layout of VertexArray.layout = Renderer_API::VertexArray::<args = {V, VC, VN, VCN}>");
    assert(position != nullptr && "No Positon array is given");

    if(this->layout == 2 || this->layout == 4) {
       assert(color != nullptr
              && "Color Array data not given but Layout is set to load Color Data [VC] or [VCN]");
       assert(color->size() == position->size()
             && "Sizeof ColorArrayData != Sizeof PositionArrayData"); 
     }

    if(this->layout == 3 || this->layout == 4) {
       assert(normal != nullptr
              && "Normal Array data not given but Layout is set to load Normal Data [VN] or [VCN]");
       assert(normal->size() == position->size()
              && "Sizeof NormalArrayData != Sizeof PositionArrayData"); 
    }

    for(std::size_t vertex_id = 0; vertex_id < (position->size())/3; ++vertex_id )
       {
         this->vertex_array.push_back((*position)[vertex_id*3+0]);
         this->vertex_array.push_back((*position)[vertex_id*3+1]);
         this->vertex_array.push_back((*position)[vertex_id*3+2]);
         
         if(this->layout == 2 || this->layout == 4)
         if(color != nullptr)
           {
             this->vertex_array.push_back((*color)[vertex_id*3+0]);
             this->vertex_array.push_back((*color)[vertex_id*3+1]);
             this->vertex_array.push_back((*color)[vertex_id*3+2]);
           }
         
         if(this->layout == 3 || this->layout == 4)
         if(normal != nullptr)
           {
             this->vertex_array.push_back((*normal)[vertex_id*3+0]);
             this->vertex_array.push_back((*normal)[vertex_id*3+1]);
             this->vertex_array.push_back((*normal)[vertex_id*3+2]);
           }
       } 
  
     return &this->vertex_array;     
}


std::vector<float>* VertexArray::UpdateVertexArray(std::vector<float>* position = nullptr, std::vector<float>* color = nullptr, std::vector<float>* normal = nullptr)
{   
     const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
     
     if(layout == 1)  {
       if(position != nullptr)
         assert(position->size() == vertex_array.size()/n);
       }
     
     if(layout == 2 || layout == 4) {
       if(color != nullptr)
         assert(color->size() == vertex_array.size()/n);
      }
      
     if(layout == 3 || layout == 4) { 
       if(normal != nullptr)
       assert(normal->size() == vertex_array.size()/n);
     }
  
      for(std::size_t vertex_id = 0; vertex_id < (vertex_array.size())/(3*n); ++vertex_id )
       {
         if(layout == 1) 
         if(position != nullptr) {
           this->vertex_array[vertex_id+0]  = (*position)[3*vertex_id+0];
           this->vertex_array[vertex_id+1] =  (*position)[3*vertex_id+1];
           this->vertex_array[vertex_id+2] =  (*position)[3*vertex_id+2];
         }
         
         if(layout == 2 || layout == 4)
         if(color != nullptr)
           {
             this->vertex_array[vertex_id + 3] = (*color)[3*vertex_id+0];
             this->vertex_array[vertex_id + 4] = (*color)[3*vertex_id+1];
             this->vertex_array[vertex_id + 5] = (*color)[3*vertex_id+2];
            
             if(layout == 4)     
             if(normal != nullptr)
             {
              this->vertex_array[vertex_id + 6] = (*normal)[3*vertex_id+0];
              this->vertex_array[vertex_id + 7] = (*normal)[3*vertex_id+1];
              this->vertex_array[vertex_id + 8] = (*normal)[3*vertex_id+2];
             }
           }
           
         if(layout == 3)  
         if(normal != nullptr)
            {
             this->vertex_array[vertex_id + 3] = (*normal)[3*vertex_id+0];
             this->vertex_array[vertex_id + 4] = (*normal)[3*vertex_id+1];
             this->vertex_array[vertex_id + 5] = (*normal)[3*vertex_id+2];
            } 
       } 
       
    return &this->vertex_array;   
}


bool VertexArray::push_back(Vertex vertex)
{
   assert(vertex.layout == this->layout);
  
   this->vertex_array.push_back(vertex.position[0]);
   this->vertex_array.push_back(vertex.position[1]);
   this->vertex_array.push_back(vertex.position[2]);
   
   if(vertex.layout == 2 || vertex.layout == 4 )
   {
    this->vertex_array.push_back(vertex.color[0]);
    this->vertex_array.push_back(vertex.color[1]);
    this->vertex_array.push_back(vertex.color[2]);
   }
   
   if(vertex.layout == 3 || vertex.layout == 4 )
   {
    this->vertex_array.push_back(vertex.normal[0]);
    this->vertex_array.push_back(vertex.normal[1]);
    this->vertex_array.push_back(vertex.normal[2]);
   }
   
   return true;
   
}


bool VertexArray::Vertex::setLayout(AttribLayout input_layout) {
 this->layout = input_layout;
 return true;
}


bool VertexArray::Vertex::updateAliases()
{
   x  = this->position[0] ; y = this->position[1] ; z = this->position[2];
   r  = this->color[0]    ; g = this->color[1]    ; b = this->color[2] ;
   n1 = this->normal[0]   ; n2 = this->normal[1]  ; n3 = this->normal[2];
   return true;
}

bool VertexArray::Vertex::updateArray()
{
   updateAliases();
   updatePosition(this->x,this->y,this->z);
   updateColor(this->r, this->g, this->b);
   updateNormal(this->n1, this->n2, this->n3); 
   return true;
}

bool VertexArray::Vertex::setPosition(float x, float y, float z) 
{
 if(layout > 0) {
 this->x = x;  this->y = y;  this->z = z;
 this->position[0] = x; this->position[1] = y; this->position[2] = z;
 return true;
 }
 return false;
}

bool VertexArray::Vertex::setColor(float r, float g, float b) 
{
  
 if(layout == 2 || layout == 4) {
 this->r = r;  this->g = g;  this->b = b;
 this->color[0] = r; this->color[1] = g; this->color[2] = b;
 return true;
 }
 return false;
}

bool VertexArray::Vertex::setNormal(float n1, float n2, float n3)
{
  if(layout == 3 || layout == 4) {
  this->n1 = n1;  this->n2 = n2;  this->n3 = n3;
  this->normal[0] = n1; this->normal[1] = n2; this->normal[2] = n3;

 return true;
 }
 return false; 
}

bool VertexArray::Vertex::updatePosition(float x, float y, float z) 
{
 if(layout > 0) {
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 const uint32_t offset = 0 ;
 this->setPosition(x, y, z);
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   (*(this->vertex_array_head))[index*stride_len + i + offset] = this->position[i];
 }
 return true;
 }
 return false;
}

bool VertexArray::Vertex::updateColor(float r, float g, float b) 
{
 if(layout == 2 || layout == 4) {
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 const uint32_t offset = 3 ;
 this->setColor(r, g, b);
 for(std::size_t i = 0 ; i < 3 ; ++i) {
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->color[i];
 }
 return true;
 }
 return false;
}

bool VertexArray::Vertex::updateNormal(float n1, float n2, float n3) 
{
 if(layout == 3 || layout == 4) {
 const uint32_t n = (this->layout > 1) ? (this->layout > 3 ? 3 : 2) : 1;
 const uint32_t stride_len = n*3;
 const uint32_t offset = (layout == 3) ? 3 : 6 ;
 this->setNormal(n1, n2, n3);  
 for(std::size_t i = 0 ; i < 3 ; ++i) { 
   (*(this->vertex_array_head))[index*stride_len + offset + i] = this->normal[i];
 }
 return true;
 }
 return false; 
}

}// namespace Renderer_API
#endif
