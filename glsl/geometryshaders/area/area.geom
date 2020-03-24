#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

const float areamax = 0.0005;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

vec4 vermell = vec4(1,0,0,1);
vec4 groc = vec4(1,1,0,1);


vec4 color_gradiente(float area ) {

    vec4 c = mix(vermell,groc,area);
    return c;
}


void main( void )
{
    vec3 v0 = (viewMatrix*modelMatrix*gl_in[0].gl_Position).xyz;
    vec3 v1 = (viewMatrix*modelMatrix*gl_in[1].gl_Position).xyz;
    vec3 v2 = (viewMatrix*modelMatrix*gl_in[2].gl_Position).xyz;         
    vec3 u =  v0 - v1;
    vec3 v =  v0 - v2;
    vec3 pv = cross(u,v);
    float area_total  = length(pv);
    float area_triangulo = area_total/2;
    float atn = area_triangulo / areamax; 
    //color progressivo  
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = color_gradiente(atn);
		gl_Position = projectionMatrix * viewMatrix * modelMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
