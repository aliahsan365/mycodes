#version 330 core

in vec4 frontColor;
out vec4 fragColor;



uniform int n = 5;
void main()
{
    
    float y = gl_FragCoord.y;
    int zero = int(mod(y,n));
    // si dejas pasar cuyo mod sea 0
    if (zero == 0) {
    	fragColor = frontColor;
    }
    else discard;

}
