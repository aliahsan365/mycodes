#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D foot0;
uniform sampler2D foot1;
uniform sampler2D foot2;
uniform sampler2D foot3;

const float R = 80.0;

uniform int layer = 1;

uniform vec2 mousePosition;
uniform bool virtualMouse = false;
uniform float mouseX,mouseY;

vec2 mouse()
{
	if (virtualMouse) return vec2(mouseX, mouseY);
	else return mousePosition;
}

void main()
{
    
    vec2 pos = mouse();
    fragColor = texture(foot0,vtexCoord);
    vec4 C = texture(foot0,vtexCoord); 
    //distancia que hay entre la pos del mouse y el texcel selecionado
    float d = distance(pos, vec2(gl_FragCoord.x, gl_FragCoord.y));
    if(d>=R) { fragColor= C;}
    else {
    	vec4 D;
    	int i = layer;
    	if (i == 0) {D = texture(foot0,vtexCoord);}
        if (i == 1) {D = texture(foot1,vtexCoord);}
        if (i == 2) {D = texture(foot2,vtexCoord);}
    
        if (i == 3) {D = texture(foot3,vtexCoord);}
    
        vec4 DC = mix(C,D,d/R);
        //fragColor = C* d/R + D *(1-d/R);
        fragColor = DC;
    }
    
    
    
    
}





