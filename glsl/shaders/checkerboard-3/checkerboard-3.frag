#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;



vec4 grey = vec4(0,0,0,1);
vec4 black = vec4(0.8,0.8,0.8,1);

uniform float n = 8;


void main() {
   float x=fract(vtexCoord.x*n);
  float y=fract(vtexCoord.y*n);
  if (x>0.1 && y>0.1) fragColor=black;
else fragColor=grey;
}
