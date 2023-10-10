namespace Renderer_API {
class VertexArray {

public :
enum AttribLayout { NONE, V, VC, VN, VCN };
AttribLayout layout;

 VertexArray() : layout(AttribLayout::NONE) {}
~VertexArray() {}

float vertex_array;
bool setLayout(Renderer_API::VertexArray::AttribLayout input_layout) : layout(input_layout) {}
std::vector<float>* BuildVertexArray(std::vector<float>* position, std::vector<float>* color, std::vector<float>* normal);

};
} // namespace Renderer_API
