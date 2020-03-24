#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;


in vec3 vnormal[];

const float d = 1.0;


out vec3 gnormal;


vec3 getNormal(vec3 A, vec3 B, vec3 C) {
  vec3 P=B-A;
  vec3 Q=C-A;
  return vec3(P.y*Q.z-P.z*Q.y,P.z*Q.x-P.x*Q.z,P.x*Q.y-P.y*Q.x);
}






void main( void )
{
        vec3 N = ((vnormal[0]+vnormal[1]+vnormal[2])/3);
    
        vec3 v0 = gl_in[0].gl_Position.xyz;
        vec3 v1 = gl_in[1].gl_Position.xyz;
        vec3 v2 = gl_in[2].gl_Position.xyz;
        
        vec3 v0p = gl_in[0].gl_Position.xyz + (d*N);
        vec3 v1p = gl_in[1].gl_Position.xyz + (d*N);
        vec3 v2p = gl_in[2].gl_Position.xyz + (d*N);
	
	//cara lateral frontal 
	gfrontColor = vfrontColor[0];
        gnormal = getNormal(v0,v1,v2);
        gl_Position = modelViewProjectionMatrix * vec4(v0,1.0);
        EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v1,1.0);
	EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v0p,1.0);
	EmitVertex();		
	

        gl_Position = modelViewProjectionMatrix * vec4(v1p,1.0);
	EmitVertex();	
	EndPrimitive();
	
	//cara lateral trasera
        gfrontColor = vfrontColor[0];
        gnormal = getNormal(v2,v0,v2p);
        gl_Position = modelViewProjectionMatrix * vec4(v0,1.0);
        EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v2,1.0);
	EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v2p,1.0);
	EmitVertex();		
	

        gl_Position = modelViewProjectionMatrix * vec4(v0p,1.0);
	EmitVertex();	
	EndPrimitive();	
	
	//cara trasera 
	gfrontColor = vfrontColor[0];
        gnormal = getNormal(v1,v2,v1p);
        gl_Position = modelViewProjectionMatrix * vec4(v1,1.0);
        EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v2,1.0);
	EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v1p,1.0);
	EmitVertex();		
	

        gl_Position = modelViewProjectionMatrix * vec4(v2p,1.0);
	EmitVertex();	
	EndPrimitive();	
	
	//top   
	gfrontColor = vfrontColor[0];
        gnormal = getNormal(v0p,v1p,v2p);
        gl_Position = modelViewProjectionMatrix * vec4(v0p,1.0);
        EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v1p,1.0);
	EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v2p,1.0);
	EmitVertex();		
        EndPrimitive();	

        // base
       
        gfrontColor = vfrontColor[0];
        gnormal = getNormal(v0,v1,v2);
        gl_Position = modelViewProjectionMatrix * vec4(v0,1.0);
        EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v1,1.0);
	EmitVertex();

        gl_Position = modelViewProjectionMatrix * vec4(v2,1.0);
	EmitVertex();		
        EndPrimitive();	
       
}
