#ifdef  _MODEL_CLASS_CPP_
#define _MODEL_CLASS_CPP_

#include "Model_Class.hpp"

namespace Renderer_API {

void Model::setVisibilityFlag(Visibility_Flag visibility_flag)
{
  this->model_visibility = visibility_flag;
}

void Model::setPrimitive(PrimitiveType primitive_type, float primitive_thickness)
{
  this->primitive_type = primitive_type;
  this->primitive_thickness = primitive_thickness;
}

void Model::setPolygonMode(PolgonMode polygon_mode)
{
  this->polygon_mode = polygon_mode;
}

void Model::setVertexAttribLayout(VertexArray::AttribLayout layout)
{
  this->vertex_array.setLayout(layout);
}

void Model::setVertexAttribData(std::vector<float>* positon = nullptr, std::vector<float>* color = nullptr, std::vector<float>* normal = nullptr)
{
  this->vertex_array.BuildVertexArray(position, color, normal)
}

void Model::updateVertexAttribData(std::vector<float>* positon = nullptr, std::vector<float>* color = nullptr, std::vector<float>* normal = nullptr)
{
  this->vertex_array.UpdateVertexArray(position, color, normal);
}

void Model::setIndexData(std::vector<uint32_t>& index_array)
{
  this->index_array = index_array;
}

void Model::setShadeModel(ShadeModel shade_model)
{
  this->shade_model = shade_model;
}

void Model::setModelMaterial(Material model_material)
{
  this->ModelMaterial = model_material;
}

void Model::setLighting(bool Lighting_Switch_Flag)
{
  this->lighting_flag =  Lighting_Switch_Flag ? 0 : 1;
}

void Model::render()
{
  
}

} // namespace Renderer_API 

#endif
