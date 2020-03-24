#version 330 core

layout (location = 0) in vec3 vertex;

layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{

    frontColor = vec4(color,1.0);

    float y = vertex.y; // vertice coord y en object space
    float a = 0.0; 
    if (y >= 0.5) {
       a = (y-0.5)*sin(time);
    }
    vec3 xparalelo = vec3(0,1,0);
    //antes de rotar
    vec3 vertice_normalizado = normalize(vertex);
    if (xparalelo.y == vertice_normalizado.y) {
    
    }

    mat3 mx = mat3(vec3(1,0,0),vec3(0,cos(a),sin(a)),vec3(0,-1*sin(a),cos(a)));
    vec3 vmod = vertex-vec3(0,1,0);
    vmod = mx*vmod;
    vmod = vmod + vec3(0,1,0); 
    gl_Position = modelViewProjectionMatrix * vec4(vmod, 1.0);
}
