#pragma once
#ifndef  _MODEL_CLASS_CPP_
#define  _MODEL_CLASS_CPP_

#include "Model_Class.hpp"

namespace Renderer_API {

 Model::Model() 
 {
  initializeOpenGLFunctions(); 
  index_array.push_back(1);
  index_array.push_back(2);
  index_array.push_back(3);
  index_array.push_back(4);
  index_array.push_back(5);
  index_array.push_back(6);
  index_array.push_back(7);
  index_array.push_back(8);
  glEnable(GL_DEBUG_OUTPUT);
  gl_error();
  glUseProgram(0);
  gl_error();
 }
 
void Model::setVisibilityFlag(Visibility_Flag visibility_flag)
{
  this->model_visibility = visibility_flag;
}

void Model::setPrimitive(PrimitiveType primitive_type, float primitive_thickness = 5.0f)
{
  this->primitive_type = primitive_type;
  this->primitive_thickness = primitive_thickness;
  
  switch (primitive_type)
    {
        case PrimitiveType::POINTS:
            this->GL_primitive_type = GL_POINTS;
            break;
        case PrimitiveType::LINES:
            this->GL_primitive_type = GL_LINES;
            break;
        case PrimitiveType::LINE_STRIP:
            this->GL_primitive_type = GL_LINE_STRIP;
            break;
        case PrimitiveType::TRIANGLES:
            this->GL_primitive_type = GL_TRIANGLES;
            break;
        case PrimitiveType::TRIANGLE_STRIP:
            this->GL_primitive_type = GL_TRIANGLE_STRIP;
            break;
        case PrimitiveType::TRIANGLE_FAN:
            this->GL_primitive_type = GL_TRIANGLE_FAN;
            break;
        case PrimitiveType::QUADS:
            this->GL_primitive_type = GL_QUADS;
            break;
        case PrimitiveType::QUAD_STRIP:
            this->GL_primitive_type = GL_QUAD_STRIP;
            break;
        default:
            this->GL_primitive_type = GL_POINTS; 
            this->primitive_type = PrimitiveType::POINTS;
            break;   
    }
}

void Model::setPolygonMode(PolygonMode polygon_mode)
{
  this->polygon_mode = polygon_mode;
}

void Model::setVertexAttribLayout(VertexArray::AttribLayout layout)
{
  this->vertex_array.setLayout(layout);
}

void Model::setVertexAttribData(std::vector<float>* position = nullptr, std::vector<float>* color = nullptr, std::vector<float>* normal = nullptr)
{
  this->vertex_array.BuildVertexArray(position, color, normal);
  GetFirstNMessages(10);
  CreateVertexBuffer();
}

void Model::updateVertexAttribData(std::vector<float>* position = nullptr, std::vector<float>* color = nullptr, std::vector<float>* normal = nullptr)
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
  this->model_material = model_material;
}

void Model::setLighting(bool Lighting_Switch_Flag)
{
  this->lighting_flag =  Lighting_Switch_Flag ? Lighting_Flag::ENABLE : Lighting_Flag::DISABLE ;
}

void Model::render() 
{
  glEnable(GL_DEPTH_TEST); // Enable depth testing
  glBindVertexArray(this->VAO); 
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO); 
  this->Setup_Uniforms();  
  const uint32_t n = (this->vertex_array.layout > 1) ? (this->vertex_array.layout > 3 ? 3 : 2) : 1;
  const uint32_t stride_len = n*3;
  // glDrawArrays(GL_POINTS , 0 , this->vertex_array.vertex_array.size()/stride_len);
  glDrawElements(GL_TRIANGLES , index_array.size(),  GL_UNSIGNED_INT, nullptr); // &(topology_corners_cur_group_indices_array[0])
}

//--------------------------Private Members Implementation----------------------------------+

void Model::SelectShader(std::string Name, const char* vertexShaderSource, const char* fragmentShaderSource)
{
  this->ModelShader.ConstructShader(Name, vertexShaderSource, fragmentShaderSource);
  glUseProgram(this->ModelShader.ShaderProgram);
}

void Model::CreateVertexBuffer()
{
     gl_error();
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    printf("Before buffer data \n"); 
    gl_error();
    glBufferData(GL_ARRAY_BUFFER, (vertex_array.vertex_array.size())*sizeof(GLfloat), &(vertex_array.vertex_array[0]), GL_STATIC_DRAW);
    printf("after buffer data gen \n"); 
    gl_error();
    
    gl_error();
    glGenBuffers(1, &this->IBO);
    printf("BeforeIBO gen \n"); 
    gl_error();
    printf("afterIBO gen \n"); 

    printf("BeforeIBO Bind \n"); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    gl_error();
    printf("after IBO Bind \n"); 

    for(auto i : index_array) std::cout << i << " : indexed are \n";
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_array.size(), &index_array[0], GL_STATIC_DRAW);
    gl_error();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //glBufferData(GL_ARRAY_BUFFER, (vertex_array.vertex_array.size() + 1000)*sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_array.vertex_array.size() *sizeof(GLfloat),  &(vertex_array.vertex_array[0]));

    GLint PosAttrib = glGetAttribLocation(this->ModelShader.ShaderProgram, "position");

    if(PosAttrib != -1)    printf("Found boom  boom Vertex Attribute : position");
    //else std::cerr << "No VertexAttributeLocation in shader with Name " << "position" << "\n";
    
    uint32_t n = (this->vertex_array.layout > 1) ? (this->vertex_array.layout > 3 ? 3 : 2) : 1;
    uint32_t stride_len = n*3;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride_len * sizeof(GLfloat) , (void*)0); // Position Data Layout
    glEnableVertexAttribArray(0); 
    
    if(this->vertex_array.layout == 2 || this->vertex_array.layout == 4)
    // GLint ColorAttrib = glGetAttribLocation(this->ModelShader.ShaderProgram, "Color");
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride_len * sizeof(GLfloat) , (void*)(3 * sizeof(GLfloat)));  // color Data Layout
    glEnableVertexAttribArray(1);
   
    if(this->vertex_array.layout == 3)
    // GLint NormalAttrib = glGetAttribLocation(this->ModelShader.ShaderProgram, "Normal"); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride_len * sizeof(GLfloat) , (void*)(3 * sizeof(GLfloat))); // Normal Data Layout
    glEnableVertexAttribArray(1);

    if(this->vertex_array.layout == 4)
    GLint NormalAttrib = glGetAttribLocation(this->ModelShader.ShaderProgram, "Normal"); 
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride_len * sizeof(GLfloat) , (void*)(6 * sizeof(GLfloat))); // Normal Data Layout
    glEnableVertexAttribArray(2);

    //glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    //printf("Unbinding Element array buffer");
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
 
}

void Model::Setup_Uniforms()
{
   this->SetMaterialProperties(128,  glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f) ,glm::vec3(0.5f, 1.0f, 1.0f)); 
   glUseProgram(this->ModelShader.ShaderProgram);
   this->uniformLocations["projectionMatrix"] = glGetUniformLocation(this->ModelShader.ShaderProgram, "projectionMatrix");
   this->uniformLocations["viewMatrix"] = glGetUniformLocation(this->ModelShader.ShaderProgram, "viewMatrix");
   this->uniformLocations["modelMatrix"] = glGetUniformLocation(this->ModelShader.ShaderProgram, "modelMatrix");
   
   glUniformMatrix4fv(this->uniformLocations["projectionMatrix"], 1, GL_FALSE, glm::value_ptr(this->ProjectionMatrix));
   glUniformMatrix4fv(this->uniformLocations["viewMatrix"], 1, GL_FALSE, glm::value_ptr(this->ViewMatrix));
   glUniformMatrix4fv(this->uniformLocations["modelMatrix"], 1, GL_FALSE, glm::value_ptr(this->ModelMatrix));

   this->uniformLocations["materialAmbient"]   =  glGetUniformLocation(this->ModelShader.ShaderProgram, "materialAmbient");
   this->uniformLocations["materialDiffuse"]   =  glGetUniformLocation(this->ModelShader.ShaderProgram, "materialDiffuse");
   this->uniformLocations["materialSpecular"]  =  glGetUniformLocation(this->ModelShader.ShaderProgram, "materialSpecular");
   this->uniformLocations["materialShininess"] =  glGetUniformLocation(this->ModelShader.ShaderProgram, "materialShininess");
   
   glUniform3fv(this->uniformLocations["materialAmbient"], 1,  glm::value_ptr(this->Ambient));
   glUniform3fv(this->uniformLocations["materialDiffuse"], 1,  glm::value_ptr(this->Diffuse));
   glUniform3fv(this->uniformLocations["materialSpecular"],  1,  glm::value_ptr(this->Specular));
   glUniform1f (this->uniformLocations["materialShininess"] , this->Shininess);

   this->uniformLocations["lightPosition"] = glGetUniformLocation(this->ModelShader.ShaderProgram, "lightPosition");
   this->uniformLocations["lightAmbient"]  = glGetUniformLocation(this->ModelShader.ShaderProgram, "lightAmbient");
   this->uniformLocations["lightDiffuse"]  = glGetUniformLocation(this->ModelShader.ShaderProgram, "lightDiffuse");
   this->uniformLocations["lightSpecular"] = glGetUniformLocation(this->ModelShader.ShaderProgram, "lightSpecular");
            
   glm::vec3 lightPosition(10.0f  , 2.0f , 0.0f); 

   glUniform3fv(this->uniformLocations["lightPosition"], 1,  glm::value_ptr(lightPosition));
   glUniform3f(this->uniformLocations["lightAmbient"], 0.8f, 0.8f, 0.8f);
   glUniform3f(this->uniformLocations["lightDiffuse"], 0.8f, 0.8f, 0.8f);
   glUniform3f(this->uniformLocations["lightSpecular"], 1.0f, 1.0f, 1.0f);

}

void Model::Update_Uniforms()
{

}

 void Model::SetMaterialProperties(float shininess = 128,   glm::vec3 ambient = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 diffuse =  glm::vec3(0.8f, 0.8f, 0.8f) , glm::vec3 specular =  glm::vec3(0.5f, 1.0f, 1.0f))
{
  this->Shininess = shininess;
  this->Ambient   = ambient;
  this->Diffuse   = diffuse;
  this->Specular  = specular; 
}

void Model::Setup_MVP(glm::mat4 SceneProjectionMatrix = glm::mat4(1.0f) , glm::mat4 SceneViewMatrix = glm::mat4(1.0f), glm::mat4 ModelMatrix = glm::mat4(1.0f))
{
  this->ProjectionMatrix = SceneProjectionMatrix;
  this->ViewMatrix = SceneViewMatrix;
  this->ModelMatrix = ModelMatrix;
}

 Model::~Model() 
 {  
   glBindBuffer(GL_ARRAY_BUFFER, VBO);  
   glBindVertexArray(this->VAO); 
   glDeleteVertexArrays(1, &this->VAO);
   glDeleteBuffers(1, &this->VBO); 
   glDeleteBuffers(1, &this->IBO); 
   glUseProgram(0);
   glDeleteProgram(this->ModelShader.ShaderProgram);
 }


void Model::GetFirstNMessages(GLuint numMsgs)
{
	GLint maxMsgLen = 0;
	glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);

	std::vector<GLchar> msgData(numMsgs * maxMsgLen);
	std::vector<GLenum> sources(numMsgs);
	std::vector<GLenum> types(numMsgs);
	std::vector<GLenum> severities(numMsgs);
	std::vector<GLuint> ids(numMsgs);
	std::vector<GLsizei> lengths(numMsgs);

	GLuint numFound = glGetDebugMessageLog(numMsgs, msgData.size(), &sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);

	sources.resize(numFound);
	types.resize(numFound);
	severities.resize(numFound);
	ids.resize(numFound);
	lengths.resize(numFound);

	std::vector<std::string> messages;
	messages.reserve(numFound);

	std::vector<GLchar>::iterator currPos = msgData.begin();
	for(size_t msg = 0; msg < lengths.size(); ++msg)
	{
		messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
		currPos = currPos + lengths[msg];
	}
}

void Model::gl_error() 
{
GLenum error;
while ((error = glGetError()) != GL_NO_ERROR) {
    switch (error) {
        case GL_INVALID_ENUM:
            std::cerr << "OpenGL Error: GL_INVALID_ENUM" << std::endl;
            break;
        case GL_INVALID_VALUE:
            std::cerr << "OpenGL Error: GL_INVALID_VALUE" << std::endl;
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "OpenGL Error: GL_INVALID_OPERATION" << std::endl;
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "OpenGL Error: GL_STACK_OVERFLOW" << std::endl;
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "OpenGL Error: GL_STACK_UNDERFLOW" << std::endl;
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "OpenGL Error: GL_OUT_OF_MEMORY" << std::endl;
            break;
        default:
            std::cerr << "OpenGL Error: Unknown error code " << error << std::endl;
            break;
    }
}
}



} // namespace Renderer_API 
#endif
