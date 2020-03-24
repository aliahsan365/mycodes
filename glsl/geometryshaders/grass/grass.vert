#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;



out vec4 vfrontColor;
out vec3 vnormal;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;




void main()
{

    vnormal = normal;
    vtexCoord = texCoord;
    
    gl_Position = vec4(vertex, 1.0);
}
