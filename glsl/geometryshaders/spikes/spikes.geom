#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;


const float disp = 0.05;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


vec4 blanco = vec4(1,1,1,0);

vec3 calcula_baricentro(vec3 a, vec3 b, vec3 c) {
     vec3 barc;
     barc = vec3((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3,(a.z+b.z+c.z)/3);
     return barc;
}

vec3 getNormal(vec3 A, vec3 B, vec3 C) {
  vec3 P=B-A;
  vec3 Q=C-A;
  return vec3(P.y*Q.z-P.z*Q.y,P.z*Q.x-P.x*Q.z,P.x*Q.y-P.y*Q.x);
}


void pinta_spike_face(vec3 v1, vec3 v2 , vec3 bcn) {

    gfrontColor = vfrontColor[0];
    gl_Position = projectionMatrix * vec4(v1,1.0);
    EmitVertex();
    gl_Position = projectionMatrix * vec4(v2,1.0);
	EmitVertex();
	gfrontColor = blanco;
	gl_Position = projectionMatrix * vec4(bcn,1.0);
	EmitVertex();		
    EndPrimitive();	


}


void main( void )
{
	
	vec3 v0 = (viewMatrix * modelMatrix * gl_in[0].gl_Position).xyz;
	vec3 v1 = (viewMatrix * modelMatrix * gl_in[1].gl_Position).xyz;
	vec3 v2 = (viewMatrix * modelMatrix * gl_in[2].gl_Position).xyz;
    vec3  N = getNormal(v0,v1,v2);
	//calculamos baricentro
	vec3 bc = calcula_baricentro(v0,v1,v2);
    vec3 bcn = bc + (N*disp);
    
    //base        
    gfrontColor = vfrontColor[0];
    gl_Position = projectionMatrix * vec4(v0,1.0);
    EmitVertex();
    gl_Position = projectionMatrix * vec4(v1,1.0);
	EmitVertex();
	gl_Position = projectionMatrix * vec4(v2,1.0);
	EmitVertex();		
    EndPrimitive();	
    
    pinta_spike_face(v0,v1,bcn);
    pinta_spike_face(v1,v2,bcn);
    pinta_spike_face(v2,v0,bcn);
}
