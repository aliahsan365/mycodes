#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()

{
        vec4 colornoise = texture(noise0,vtexCoord);
        vec4 colorrock = texture(rock1,vtexCoord);
        vec4 colorgrass = texture(grass2,vtexCoord);
        
        vec4 colorfinal = mix(colorrock,colorgrass,colornoise.r);

   fragColor = colorfinal;
}
