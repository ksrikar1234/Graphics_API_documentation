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
         this->vertex_array.push_back((*position)[vertex_id+0]);
         this->vertex_array.push_back((*position)[vertex_id+1]);
         this->vertex_array.push_back((*position)[vertex_id+2]);

         if(color != nullptr)
           {
             this->vertex_array.push_back((*color)[vertex_id+0]);
             this->vertex_array.push_back((*color)[vertex_id+1]);
             this->vertex_array.push_back((*color)[vertex_id+2]);
           }

         if(normal != nullptr)
           {
             this->vertex_array.push_back((*normal)[vertex_id+0]);
             this->vertex_array.push_back((*normal)[vertex_id+1]);
             this->vertex_array.push_back((*normal)[vertex_id+2]);
           }

       } 
       
     return &this->vertex_array;     
};
}// namespace Renderer_API
#endif
