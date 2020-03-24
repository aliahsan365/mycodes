#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;
in vec2 vtexCoord;
void main()
{


    vec2 C = vec2(0.275,0.09);
    float r = 0.065;

    vec2 d = vec2(time,0);
    vec2 Cprima =  C +  d;
    Cprima.s = fract(Cprima.s);
    Cprima.t = fract(Cprima.t);
    
    
    float distPrima = distance(vtexCoord,Cprima);
    if (distPrima < r) {

       fragColor = texture(colorMap,vtexCoord-d); 
    }
    
    else {
       float dist = distance(vtexCoord,C);
       if (dist < r) {
       fragColor = texture(colorMap,vec2(vtexCoord.s+0.5,vtexCoord.t));
       } 
       
       else {
            fragColor = texture(colorMap,vtexCoord);
       
       
       }
       
    
    
    }

} 
