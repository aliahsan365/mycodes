#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


uniform float t = 0.4;

uniform vec3 boundingBoxMin;

uniform vec3 boundingBoxMax;

uniform float scale = 4.0;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    float incy = boundingBoxMax.y-boundingBoxMin.y;
    float c = mix(boundingBoxMin.y,boundingBoxMax.y,t);
    vec3 vmod;
    if (vertex.y < c) {
    	
       vmod = vec3(vertex.x,scale*vertex.y,vertex.z);
    
    }
    
    else {
      float t = (c*scale)-c;
      vmod = vec3(vertex.x,t+vertex.y,vertex.z);
    
    }
    

    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
