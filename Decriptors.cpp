#include <string>
#include <vector>

enum class ValueType {
    // Add possible value types
};

struct BlendStateDesc {
    GLenum sourceFactorRGB;
    GLenum destFactorRGB;
    GLenum sourceFactorAlpha;
    GLenum destFactorAlpha;
    GLenum blendEquationRGB;
    GLenum blendEquationAlpha;
    GLboolean enableBlending;
    // Add other members as needed

    // Constructor with default values
    BlendStateDesc() 
        : sourceFactorRGB(GL_SRC_ALPHA),
          destFactorRGB(GL_ONE_MINUS_SRC_ALPHA),
          sourceFactorAlpha(GL_SRC_ALPHA),
          destFactorAlpha(GL_ONE_MINUS_SRC_ALPHA),
          blendEquationRGB(GL_FUNC_ADD),
          blendEquationAlpha(GL_FUNC_ADD),
          enableBlending(GL_FALSE) {
        // Initialize other members with default values if needed
    }
};

struct RasterizerStateDesc {
    GLenum polygonMode;
    GLenum cullFace;
    GLenum frontFace;
    GLfloat lineWidth;
    // Add other members as needed

    // Constructor with default values
    RasterizerStateDesc()
        : polygonMode(GL_FILL),
          cullFace(GL_BACK),
          frontFace(GL_CCW),
          lineWidth(1.0f) {
        // Initialize other members with default values if needed
    }
};

struct DepthStencilStateDesc {
    GLboolean enableDepthTest;
    GLenum depthFunc;
    GLboolean enableDepthWrite;
    GLboolean enableStencilTest;
    GLenum stencilFunc;
    GLint stencilRef;
    GLuint stencilMask;
    GLenum stencilFailOp;
    GLenum stencilDepthFailOp;
    GLenum stencilPassOp;
    GLuint stencilWriteMask;
    // Add other members as needed

    // Constructor with default values
    DepthStencilStateDesc()
        : enableDepthTest(GL_TRUE),
          depthFunc(GL_LESS),
          enableDepthWrite(GL_TRUE),
          enableStencilTest(GL_FALSE),
          stencilFunc(GL_ALWAYS),
          stencilRef(0),
          stencilMask(0xFFFFFFFF),
          stencilFailOp(GL_KEEP),
          stencilDepthFailOp(GL_KEEP),
          stencilPassOp(GL_KEEP),
          stencilWriteMask(0xFFFFFFFF) {
        // Initialize other members with default values if needed
    }
};

struct ElementLayout {
    ValueType ValueType;    // Data Type
    uint32_t StartIndex;    // Element Index in stride {layout = 0,1}
    uint32_t NumComponents; // Number of components per stride
    uint32_t StrideLength;  // in bytes (Number of Elements * size(each_element))
    uint32_t InstanceDataStepRate; // ++1
    bool IsNormalized;    // false
    // Add other members related to element layout
};

struct InputLayoutDesc {
    ElementLayout ElementLayout;
    std::vector<ValueType> Elements; // Elements in the input layout
    // Add other members related to input layout description
};

enum class PRIMITIVE_TOPOLOGY {
    PRIMITIVE_TOPOLOLGY_POINT,
    PRIMITIVE_TOPOLOLGY_LINE,
    PRIMITIVE_TOPOLOLGY_TRIANGLE,
    PRIMITIVE_TOPOLOLGY_QUAD
};

struct GraphicsPipelineDescriptor {
    uint8_t NumViewports;
    uint8_t NumRenderTargets;
    std::vector<int> RTVFormats; // Placeholder, change to the appropriate type
    // Add other members related to graphics pipeline description
    BlendStateDesc BlendState;
    RasterizerStateDesc RasterizerState;
    DepthStencilStateDesc DepthStencilState;
    InputLayoutDesc InputLayout;
    PRIMITIVE_TOPOLOGY PrimitiveTopology;
    // Add other members as needed
};

struct GraphicsPipelineStateCreateInfo {
    GraphicsPipelineDescriptor PSODesc;
    // Add other members as needed
};

int main() {
    // Example usage
    GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = PipeLineEnum::PIPELINE_TYPE_OPENGL_4_3_GRAPHICS;

    // Graphics pipeline configuration
    PSOCreateInfo.PSODesc.NumViewports = 1;
    PSOCreateInfo.PSODesc.NumRenderTargets = 1;
    PSOCreateInfo.PSODesc.RTVFormats.push_back(0); // Placeholder format
    PSOCreateInfo.PSODesc.BlendState = {}; // Placeholder, add actual blend state configuration
    PSOCreateInfo.PSODesc.RasterizerState = {}; // Placeholder, add actual rasterizer state configuration
    PSOCreateInfo.PSODesc.DepthStencilState = {}; // Placeholder, add actual depth-stencil state configuration
    PSOCreateInfo.PSODesc.InputLayout.Elements.push_back({}); // Placeholder, add actual input layout elements
    PSOCreateInfo.PSODesc.PrimitiveTopology = PRIMITIVE_TOPOLOGY::PRIMITIVE_TOPOLOLGY_TRIANGLE;

    // Add other configuration as needed

    return 0;
}
