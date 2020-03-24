#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;


vec4 colorprimo = vec4(0.3,0.3,0.9,1.0);


float triangleWave(float x) {
  return abs(mod(x,2)-1.0);
}

uniform float scale = 8;
uniform float time;





void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(colorprimo) * N.z;
    vec3 T0 = vec3(-1,-1,0);
    vec3 V = vec3(2,2,0);
    
    vec3 t = vec3(triangleWave(time/1.618),triangleWave(time),0);
    vec3 T = scale * (T0+V*t);
    vec3 vt = (1/scale)*(vertex + T);
    
    
    

    gl_Position = modelViewProjectionMatrix * vec4(vt, 1.0);
}
