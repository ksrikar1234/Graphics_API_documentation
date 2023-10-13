#ifndef _RENDERER_API_IN_BUILT_SHADER_SOURCES_
#define _RENDERER_API_IN_BUILT_SHADER_SOURCES_

namespace Renderer_API {


/*
     Valid Shader combinations
     +---------------------------------------------------------------+
     NO LIGHT & NO MATERIAL SHADERS : FLAT_SHADING  
     (vc_vertex_shader ||  v_vertex_shader) + vc_fragment_shader;
     +---------------------------------------------------------------+
     LIGHTING SHADERS + MATERIAL : SMOOTH_SHADING
     (vcn_vertex_shader ||  vn_vertex_shader) + vcn_fragment_shader;
     +---------------------------------------------------------------+

*/
//------------------------------------------For Corner groups, Edges---------------------------------------------------------------+
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// NO LIGHTING SHADER /////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------------+

const char* vc_vertex_shader = R"(
    #version 330 core

    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    
    out vec3 outColor;
  
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;
    
    uniform float mono_color_scheme;
    uniform vec3 model_color;

    void main()
    {    
      gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
      if(mono_color_scheme == 1.0f) outColor = model_color;
      else { outColor = model_color;} ;
    }
)";


const char* v_vertex_shader = R"(
    #version 330 core

    layout (location = 0) in vec3 position;
    
    out vec3 outColor;
  
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;
    
    uniform float mono_color_scheme;
    uniform vec3 model_color;

    void main()
    {    
      gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
      outColor = model_color;
    }
)";

const char* vc_fragment_shader = R"(

    #version 330 core
    in vec3 outColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(outColor, 1.0);
    }
)";

//------------------------------------------For Corner groups, Edges---------------------------------------------------------------+
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////  LIGHTING SHADER -> Blinn Phongs Lighting algorithm ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------------------------------------+

const char* vcn_vertex_shader = R"(    
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 fragNormal;
out vec3 fragPosition;
out vec3 fragLightDir;
out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
    
uniform vec3 lightPosition;

uniform float vertex_light_enabled;
uniform float mono_color_scheme;
uniform vec3 model_color;

void main()
{
  
    // Transform vertex position and normal to world space
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
   
    if(vertex_light_enabled == 1.0f)
    {
      vec3 worldNormal = mat3(transpose(inverse(modelMatrix))) * normal;

      // Compute the light direction
      fragLightDir = normalize(lightPosition - worldPosition.xyz);

      // Pass data to the fragment shader
      fragNormal = worldNormal;
      fragPosition = worldPosition.xyz;
    }

    else 
    {
      fragNormal   = vec3(1.0f);
      fragPosition = vec3(1.0f);
      fragLightDir = vec3(1.0f);
    }

    if(mono_color_scheme == 1.0f)
    { 
        vertexColor = model_color;
    }
    else
    {
        vertexColor = color;
    }

    // Transform the vertex position to clip space
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
)";

//----------------------------------------------------------------------------------------------------------------------+
const char* vn_vertex_shader = R"(    
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 fragNormal;
out vec3 fragPosition;
out vec3 fragLightDir;
out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
    
uniform vec3 lightPosition;

uniform float vertex_light_enabled;
uniform vec3 model_color;

void main()
{
  
    // Transform vertex position and normal to world space
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
   
    if(vertex_light_enabled)
    {
      vec3 worldNormal = mat3(transpose(inverse(modelMatrix))) * normal;

      // Compute the light direction
      fragLightDir = normalize(lightPosition - worldPosition.xyz);

      // Pass data to the fragment shader
      fragNormal = worldNormal;
      fragPosition = worldPosition.xyz;
    }

    else 
    {
      fragNormal   = vec3(1.0f);
      fragPosition = vec3(1.0f);
      fragLightDir = vec3(1.0f);
    }
    
    vertexColor = color;

    // Transform the vertex position to clip space
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
)";

//------------------------------------------On Screen rendering Fragment Shader----------------------------------------------------------------+

const char* vcn_fragment_shader = R"(

#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec3 fragLightDir;
in vec3 vertexColor;


out vec4 fragColor;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

uniform float frag_light_enabled;

void main()
{  

if(frag_light_enabled == 1.0f)
{
  // Compute the normal and light direction in fragment space
  vec3 normal = normalize(fragNormal);
  vec3 lightDir = normalize(fragLightDir);
  vec3 viewDir = normalize(-fragPosition);

  // Compute the diffuse color
  float diffuseFactor = max(dot(normal, lightDir), 0.0);
  vec3 diffuseColor = lightDiffuse * materialDiffuse * diffuseFactor;

  // Compute the half-angle vector (Blinn-Phong)
  vec3 halfDir = normalize(lightDir + viewDir);

  // Compute the specular color (Blinn-Phong)
  float specularFactor = pow(max(dot(normal, halfDir), 0.0), materialShininess);
  vec3 specularColor = lightSpecular * materialSpecular * specularFactor;

  // Compute the final color (ambient + diffuse + specular)
  vec3 ambientColor = lightAmbient * materialAmbient;
  vec3 finalColor = ambientColor + diffuseColor + specularColor;

  finalColor = finalColor * vertexColor;
  fragColor = vec4(finalColor, 1.0f);
}

else 
{
 fragColor = vec4(vertexColor, 1.0f);   
}

}

)";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////// Refererence Shaders ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* simpleVertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in vec3 normal;
 
    out vec3 outColor;
  
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;
    
    uniform float mono_color_scheme;
    uniform float model_color;

    void main()
    {    
      int TriangleID = gl_VertexID/3; 
      gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPos, 1.0);
      if(mono_color_scheme == 1.0f) outColor = model_color;
      else { outColor = VertexColor} ;
    }
)";

const char* simpleFragmentShaderSource = R"(

    #version 330 core
    in vec3 outColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(outColor, 1.0);
    }
)";

const char* OffScreenVertexShaderSource = R"(
    #version 330 core

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;
    layout(location = 2) in vec3 normal;
 
    out vec3 outColor;
  
    uniform mat4 modelMatrix;
    uniform mat4 viewMatrix;
    uniform mat4 projectionMatrix;

    void main()
    {    
       int TriangleID = gl_VertexID/3; 

    // float b = float((TriangleID >> 16) & 0xFF) / 255.0;
    // float g = float((TriangleID >> 8) & 0xFF) / 255.0;
    // float r = float(TriangleID & 0xFF) / 255.0;

         gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPos, 1.0);
         outColor = VertexColor;
  // outColor  = vec3(r,g,b);
    }
)";

const char* OffScreenFragmentShaderSource = R"(

    #version 330 core
    in vec3 outColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(outColor, 1.0);
    }
)";

//----------------------------------------------------Blinn Phongs Lighting algorithm ------------------------------------------------------------------------------------+

const char* OnScreenVertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 fragNormal;
out vec3 fragPosition;
out vec3 fragLightDir;
out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightPosition;

void main()
{

    // Transform vertex position and normal to world space
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
    vec3 worldNormal = mat3(transpose(inverse(modelMatrix))) * normal;

    // Compute the light direction
    fragLightDir = normalize(lightPosition - worldPosition.xyz);

    // Pass data to the fragment shader
    fragNormal = worldNormal;
    fragPosition = worldPosition.xyz;
     
      vertexColor = color;
     //  vertexColor = vec3(0.8f, 0.4f , 0.8f );
    

    // Transform the vertex position to clip space
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
)";

//------------------------------------------On Screen rendering Fragment Shader----------------------------------------------------------------+

const char* OnScreenFragmentShaderSource = R"(

#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;
in vec3 fragLightDir;
in vec3 vertexColor;


out vec4 fragColor;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;


void main()
{  
  
// Compute the normal and light direction in fragment space
vec3 normal = normalize(fragNormal);
vec3 lightDir = normalize(fragLightDir);
vec3 viewDir = normalize(-fragPosition);

// Compute the diffuse color
float diffuseFactor = max(dot(normal, lightDir), 0.0);
vec3 diffuseColor = lightDiffuse * materialDiffuse * diffuseFactor;

// Compute the half-angle vector (Blinn-Phong)
vec3 halfDir = normalize(lightDir + viewDir);

// Compute the specular color (Blinn-Phong)
float specularFactor = pow(max(dot(normal, halfDir), 0.0), materialShininess);
vec3 specularColor = lightSpecular * materialSpecular * specularFactor;

// Compute the final color (ambient + diffuse + specular)
vec3 ambientColor = lightAmbient * materialAmbient;
vec3 finalColor = ambientColor + diffuseColor + specularColor;
finalColor = finalColor * vertexColor;
fragColor = vec4(finalColor, 1.0f);

}

)";


//} // ShaderSources
} // Renderer_API


#endif //  _RENDERER_IN_BUILT_SHADER_SOURCES_
