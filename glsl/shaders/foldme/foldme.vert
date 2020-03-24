#version 330 core

layout (location = 0) in vec3 vertex;

layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;


vec4 blue = vec4(0,0,1,1);

void main()
{
    
    frontColor = blue;
    vtexCoord = texCoord;
    float fi = -1*time*texCoord.s;
    mat3 m = mat3(vec3(cos(fi),0,-1*sin(fi)),vec3(0,1,0),vec3(sin(fi),0,cos(fi)));
    vec3 vmod = m*vertex;  
    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
