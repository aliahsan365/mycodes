#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;


out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;


uniform float time;
uniform float speed = 0.5;



void main()
{

    frontColor = vec4(color,1.0);
    float fi = speed*time;
    mat3 m = mat3(vec3(cos(fi),0,-1*sin(fi)),vec3(0,1,0),vec3(sin(fi),0,cos(fi)));
    vec3 vmod = m*vertex;

    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
