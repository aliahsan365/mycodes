#version 330 core

in vec4 frontColor;
out vec4 fragColor;


uniform sampler2D colorMap;

uniform float time;

in vec2 vtexCoord;


void main()
{

    float  x = fract(time);
    vec2 mytext = vtexCoord;
    vec4 mytextcolor = texture(colorMap,vtexCoord); 
    if(x <= 0.5) {
        if (vtexCoord.s < 0.5) {
           mytext.s = (1-vtexCoord.s);
           }
       else {
           mytext.s = vtexCoord.s;
       } 
       mytextcolor = texture(colorMap,mytext); 
    }
    
    else {
      if (vtexCoord.s < 0.5) {
         mytext.s = vtexCoord.s;
      	}
      else {
         mytext.s = (1-vtexCoord.s);
       }
      mytextcolor = texture(colorMap,mytext); 
    }
    fragColor = mytextcolor;
}
