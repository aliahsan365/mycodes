#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

const float pi = 3.141592;
uniform int n = 4;
uniform float amp = 0.5;
uniform float freq = 0.25;

uniform float time;
void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    float vyo = vertex.y;

    float w = n*freq*pi/2; // que es el calculo de w a partir de freq,n,pi..
    float t = time;
    float phase = vertex.y;
    // w * t + phase, luego a es:
    float a = amp*sin(w*t+phase);
    mat3 rx = mat3(vec3(1,0,0),
                     vec3(0,cos(a),sin(a)),
		     vec3(0,-1*sin(a),cos(a)));
    vec3 vmod = rx*vertex;

    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
