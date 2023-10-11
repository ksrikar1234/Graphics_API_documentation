#ifdef  _MODEL_CLASS_CPP_
#define _MODEL_CLASS_CPP_

namespace Renderer_API {

void setVisibilityFlag(Visibility_Flag flag)
void setPrimitive(PrimitiveType primitive_type, float primitive_thickness);
void setPolygonMode(PolgonMode polygon_mode);
void setVertexAttribLayout(VertexArray::AttribLayout layout);
void setVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal);
void updateVertexAttribData(std::vector<float>* positon, std::vector<float>* color, std::vector<float>* normal);
void setIndexData(std::vector<uint32_t>& index_array);
void setShadeModel(ShadeModel shade_model);
void setModelMaterial(Material model_material);
void setLighting(bool Lighting_Switch_Flag);
void render();

}
#endif
