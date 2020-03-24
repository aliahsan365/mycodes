#version 330 core

in vec3 fcolor;
out vec4 FragColor;

uniform bool carcel;

vec4 NEGRO = vec4(0,0,0,1);
vec4 BLANCO  = vec4(1,1,1,1);

void main()
{



    if (carcel) {
         //es la parte entera de dividir entre 10 que nos interesa
         // luego, el mod es solo para elegir el color en funcion
         // de si la parte entera es divisible por 2 o no.
        if (int(gl_FragCoord.y/10)%2 !=0 ) {
            FragColor = NEGRO;
            }
        else {
            FragColor = BLANCO;
            }
        }
   else {
        FragColor = vec4(fcolor,1);
       }



}
