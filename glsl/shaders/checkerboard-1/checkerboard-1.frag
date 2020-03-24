#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 NEGRO = vec4(0,0,0,1);
vec4 GRIS = vec4(0.8,0.8,0.8,1);




void main()
{
  float slice=1.0/8;
  int x=int(mod(vtexCoord.x/slice, 2));
  int y=int(mod(vtexCoord.y/slice, 2));
  if (x==y) fragColor=GRIS;
else fragColor=NEGRO;
}
