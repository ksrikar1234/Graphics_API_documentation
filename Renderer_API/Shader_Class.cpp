#ifndef _SHADER_CLASS_CPP_
#define _SHADER_CLASS_CPP_
#include "Shader_Class.hpp"

namespace Renderer_API {

OpenGLShader::OpenGLShader(std::string ShaderProgramID)
{
  this->ShaderID = ShaderProgramID;
}

OpenGLShader::OpenGLShader(std::string ShaderProgramID , const char* VertexShaderSource, const char* FragmentShaderSource )
{  
   initializeOpenGLFunctions();
   if(FragmentShaderSource != "" || VertexShaderSource != "" ) 
   {
    this->ShaderID = ShaderProgramID; // Set Name of the Shader ID Not compulsory but just makes your life easy during debugging
    compileFragmentShader(FragmentShaderSource);
    compileVertexShader(VertexShaderSource);
    this->ShaderProgram =  linkShaderProgram(this->ShaderProgram , this->VertexShaderProgram , this->FragmentShaderProgram);       
   }
  else printf("No proper shader sources were given in constructor , construct your shader using OpenGLShader::ConstructShader() ");
        
  if(ShaderProgramID == "") printf("Mild Warning: No Internal ID was given to Shader Program. Please given an Unique ID for Debugging \n");
}
  
GLuint OpenGLShader::ConstructShader(std::string ShaderProgramID = "", const char* VertexShaderSource = "", const char* FragmentShaderSource = "")
{
  if(FragmentShaderSource != "" || VertexShaderSource != "" )
   {
    this->ShaderID = ShaderProgramID; // Set Name of the Shader ID Not compulsory but just makes your life easy during debugging
    compileFragmentShader(FragmentShaderSource);
    compileVertexShader(VertexShaderSource);
    this->ShaderProgram =  linkShaderProgram(this->ShaderProgram , this->VertexShaderProgram , this->FragmentShaderProgram);       
    return (this->ShaderProgram);
   }
  
  else printf("ERROR: INVALID SHADER SOURCES");      
  if(ShaderProgramID == "") printf("Mild Warning: No Internal ID was given to Shader Program. Please given an Unique ID for Debugging \n");
}


GLuint OpenGLShader::compileVertexShader(const char* VertexShaderString)  
{
 this->VertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
 glShaderSource(this->VertexShaderProgram, 1, &VertexShaderString, nullptr);
 glCompileShader(this->VertexShaderProgram);
 if (!success) 
   {
    glGetShaderInfoLog(this->VertexShaderProgram, 512, nullptr, this->VertexShaderInfoLog);
    std::cerr << "Vertex shader failed to compile  : \n" << this->VertexShaderInfoLog << std::endl;
   }
 else { std::cout  << this->ShaderID <<" Vertex shader sucessfully compiled\n"; }
 return this->VertexShaderProgram;
}
        
GLuint OpenGLShader::compileFragmentShader(const char* FragmentShaderString) 
{
 this->FragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
 glShaderSource(this->FragmentShaderProgram, 1, &FragmentShaderString, nullptr);
 glCompileShader(this->FragmentShaderProgram);
 glGetShaderiv(this->FragmentShaderProgram, GL_COMPILE_STATUS, &success);
 if (!success) 
    {
     glGetShaderInfoLog(this->FragmentShaderProgram, 512, nullptr, this->FragmentShaderInfoLog);
     std::cerr << this->ShaderID  << " Fragment shader  failed to compile :\n" << this->FragmentShaderInfoLog << std::endl; 
    }
 else { 
       std::cout  << this->ShaderID <<" Fragment shader sucessfully compiled\n";
      }
 return this->FragmentShaderProgram;
}

GLuint OpenGLShader::linkShaderProgram(GLuint ShaderProgramHandle ,GLuint VertexShaderProgramHandle , GLuint FragmentShaderProgramHandle )
{
   this->ShaderProgram = glCreateProgram();
   glAttachShader(this->ShaderProgram ,  this->VertexShaderProgram);
   glAttachShader(this->ShaderProgram ,  this->FragmentShaderProgram);
   glLinkProgram(this->ShaderProgram );
   //glDeleteShader(VertexShaderProgramHandle);
   //glDeleteShader(FragmentShaderProgramHandle); 

   glGetProgramiv(this->ShaderProgram , GL_LINK_STATUS, &success);
   if (!success)
     {
      glGetProgramInfoLog(this->ShaderProgram , 512, nullptr, this->ShaderProgramInfoLog);
      std::cerr << "Shader program linking failed:\n" << this->ShaderProgramInfoLog << "\n";
     }
   
   else { std::cout  << this->ShaderID <<" ShaderProgram sucessfully linked\n" ;};

   return this->ShaderProgram ;
}

OpenGLShader::~OpenGLShader()
{ 
   glDeleteProgram(ShaderProgram);
   std::cout << "Shader Program ID : " << this->ShaderID << " is deleted \n" ;
}

} // namespace Renderer_API
#endif 
