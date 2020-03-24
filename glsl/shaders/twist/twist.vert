#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


uniform float time;
void main()
{
    float y = vertex.y;
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float fy = 0.4*y*sin(time);
    mat3 ry = mat3(vec3(cos(fy),0,-1*sin(fy)),vec3(0,1,0),vec3(sin(fy),0,cos(fy)));
    vec3 vmod = ry*vertex;
    
    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
