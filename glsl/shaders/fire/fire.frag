#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float time;

uniform float slice = 0.1;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;



void main()
{



    vec4 ctex;
    float c = int(mod(time/slice,4));


    if (c == 0){
    	ctex = texture (sampler0,vtexCoord);
    } 
    
    else if (c == 1) {
        	ctex = texture (sampler1,vtexCoord);
    }   
      else if (c == 2) {
        	ctex = texture (sampler2,vtexCoord);
    }   
     
     
       else if (c == 3) {
        	ctex = texture (sampler3,vtexCoord);
    }   
    
    fragColor = ctex;
}
