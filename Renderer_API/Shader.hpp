#ifndef _RENDERER_OPENGL_SHADER_CLASS_
#define _RENDERER_OPENGL_SHADER_CLASS_

#ifdef USE_QT_OPENGL_LOADER
#include <QOpenGLFunctions_3_3_Compatibility>
#else
#include <GL/glew.h>
#endif


class OpenGLShader : protected QOpenGLFunctions_3_3_Compatibility {
      public:
      std::string ShaderID;
      GLuint ShaderProgram;
      GLuint FragmentShaderProgram, VertexShaderProgram;      
      GLint  success;
      GLchar ShaderProgramInfoLog[512], VertexShaderInfoLog[512], FragmentShaderInfoLog[512];

      OpenGLShader(std::string ShaderProgramID);
      OpenGLShader(std::string ShaderProgramID = "", const char* VertexShaderSource = "", const char* FragmentShaderSource = "");
      GLuint ConstructShader(std::string ShaderProgramID, const char* VertexShaderSource, const char* FragmentShaderSource);
      ~OpenGLShader();
      
      private:
      GLuint compileVertexShader(const char* VertexShaderString);
      GLuint compileFragmentShader(const char* FragmentShaderString);
      GLuint linkShaderProgram(GLuint ShaderProgramHandle ,GLuint VertexShaderProgramHandle , GLuint FragmentShaderProgramHandle );
      
};

#endif

#ifdef USE_HEADER_ONLY_IMPLEMENTATION
#include "Shader.cpp"
#endif
