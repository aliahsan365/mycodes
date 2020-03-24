#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;




uniform sampler2D spheremap;


vec4 samplerSphereMap(sampler2D sampler, vec3 V) {
    float z = sqrt((V.z+1.0)/2.0);
    vec2 st = vec2((V.x/(2.0*z)+1.0)/2.0,(V.y/(2.0*z)+1.0)/2.0);
    return texture(sampler,st);

}



void main()
{
    vec3 vision = normalize(vec3(vtexCoord.x,vtexCoord.y,0));
    fragColor = samplerSphereMap(spheremap,vision);
}
