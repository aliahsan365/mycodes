#version 330 core


out vec4 fragColor;
in vec2 vtexCoord;

uniform sampler2D colorMap;


void main()
{
    vec4 colorTextura = texture(colorMap,vtexCoord);
    fragColor = colorTextura;
}
