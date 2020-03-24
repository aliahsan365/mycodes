#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colorMap;


void main()
{
    vec4 colorTextura = texture(colorMap,vtexCoord);
    fragColor = frontColor*colorTextura;
}
