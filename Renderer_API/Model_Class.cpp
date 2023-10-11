#ifdef  _MODEL_CLASS_CPP_
#define _MODEL_CLASS_CPP_

namespace Renderer_API {

void Model::setVisibilityFlag(Visibility_Flag flag)
{
  
}

void Model::setPrimitive(PrimitiveType primitive_type, float primitive_thickness)
{
  
}

void Model::setPolygonMode(PolgonMode polygon_mode)
{
  
}

void Model::setVertexAttribLayout(VertexArray::AttribLayout layout)
{
  
}

void Model::setVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal)
{
  
}

void Model::updateVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal)
{
  
}

void Model::setIndexData(std::vector<uint32_t>& index_array)
{
  
}

void Model::setShadeModel(ShadeModel shade_model)
{
  
}

void Model::setModelMaterial(Material model_material)
{
  
}

void Model::setLighting(bool Lighting_Switch_Flag)
{
  
}

void Model::render()
{
  
}

} // namespace Renderer_API 

#endif
