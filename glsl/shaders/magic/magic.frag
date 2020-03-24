#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D window0;
uniform sampler2D interior1;
uniform sampler2D exterior2;

in vec2 vtexCoord;
in vec3 Neye;
void main()
{

    vec4 colorFinal;
    vec4 C = texture(window0,vtexCoord);
    

    float ta = C.a;
    if (ta < 1.0) {
        vec4 D = texture(interior1,vtexCoord+0.5*Neye.xy);
        if (D.a == 1.0) {
            colorFinal = D;
        }
        else {
           colorFinal = texture(exterior2,vtexCoord+0.7*Neye.xy);
        
        }
    }
    else {
       colorFinal = C;
    
    }
    
    
    fragColor = colorFinal;
}
