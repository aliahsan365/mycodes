#version 330 core

in vec4 frontColor;
out vec4 fragColor;



uniform int levels = 5;
uniform sampler2D noise;

void main()
{  

    float l = levels-1;
    vec4 D = texture(noise,gl_FragCoord.xy/64.0);
    vec4 cp = frontColor + (D - vec4(0.5))/l;
    
    

    
    float r,g,b,a;
    
    r = round(cp.x*l)/l;
    g = round(cp.y*l)/l;
    b = round(cp.z*l)/l;
    a = round(cp.a*l)/l;
    fragColor = vec4(r,g,b,a);
}
