#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

vec4 yellow = vec4(1,1,0,0);
vec4 red = vec4(1,0,0,0);


void main()
{

    float f = fract(vtexCoord.s);
    float a = 1.0/9.0;
    if (f <= 0 && f < a) {
       fragColor = yellow;
    }
    else if (2*a <= f && f < 3*a){
            fragColor = yellow;

    }
  else if (4*a <= f && f < 5*a){
            fragColor = yellow;

    }
      else if (6*a <= f && f <= 7*a){
            fragColor = yellow;

    } 

     else if (8*a <= f && f < 9*a){
            fragColor = yellow;

    }
    else {
        fragColor = red;
    }
}
