#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform sampler2D colorMap;
void main()
{
    vec2 Q = vtexCoord - vec2(0,0);
    Q = 2*Q - 1;
    float r = length(Q);
    float rp = (r + (0.22*(r*r*r)) + (0.24*(r*r*r*r*r)));
    vec2 Qp = rp * normalize(Q);
    Qp = (Qp+1)/2;
    vec2 nvtextCoord = Qp;
    vec4 C;
    if (0 <= nvtextCoord.s && nvtextCoord.s <= 1 && 0 <= nvtextCoord.t && nvtextCoord.t <= 1) {
       C = texture(colorMap,nvtextCoord);
    
    }
    else {
      C = vec4(0,0,0,1);
    
    }
    fragColor = C;
    
    
}
