#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform bool eyespace;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

float PI = acos(-1.0);
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);

    float dist = distance(boundingBoxMax,boundingBoxMin);
    float y = vertex.y; // en object space
    float r = dist/2;
    if (eyespace) {
       vec4 aux = viewMatrix*modelMatrix*vec4(vertex,1.0);
       y = aux.y;
    }
    
    float amplitude = (r/10)*y;
    float dt  = amplitude*sin(time);
    //desplazando en la dir de la normal
    vec3 vmod = vertex + (normal*dt);
    
    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
} 
