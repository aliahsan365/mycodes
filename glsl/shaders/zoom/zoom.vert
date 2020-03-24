#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;

    float scale = 0.5+abs(sin(time));
    vec4 pos = modelViewProjectionMatrix * vec4(vertex, 1.0);
    //el vertice en clip space es divido por la componente w para pasarlo a NDC
    vec4 v = (1.0/pos.w)*pos;
   //se pasa solamente la coord xy
    gl_Position = vec4(scale*v.xy, v.zw);
}
