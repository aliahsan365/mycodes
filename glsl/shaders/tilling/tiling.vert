 #version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform int tiles = 1;
//para hacerlo mas pequene y que se tenga que repetir mas n veces, lo que se hace es multiplicar
//para hacerlo mas grande y que no se tenga que reptir menos n veces, lo que se hace es dividir

void main()
{
    //vtexCoord.s = texCoord.s*tiles;
    //vtexCoord.t = texCoord.t*tiles;
    //funciona igual con lo que esta comentado
    vtexCoord = texCoord*vec2(tiles);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
