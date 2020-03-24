#version 330 core
        
layout(triangles) in;
layout(line_strip,max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform  vec3 boundingBoxMin;
uniform  vec3 boundingBoxMax;

vec4 negre = vec4 (0,0,0,1);

uniform mat4 modelViewProjectionMatrix;


void pinta_cara(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {

		gfrontColor = negre;
		gl_Position = modelViewProjectionMatrix * vec4(v0,1);
		EmitVertex();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v1,1);
		EmitVertex();
    	
    	EndPrimitive();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v1,1);
		EmitVertex();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v2,1);
		EmitVertex();
    	
    	EndPrimitive();
        
        gl_Position = modelViewProjectionMatrix * vec4(v2,1);
		EmitVertex();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v3,1);
		EmitVertex();
    	
    	EndPrimitive();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v3,1);
		EmitVertex();
    	
    	gl_Position = modelViewProjectionMatrix * vec4(v0,1);
		EmitVertex();

}







void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    if (gl_PrimitiveIDIn == 0) {
    	
        
        
        vec3 min = boundingBoxMin;
        vec3 max = boundingBoxMax;
        
        vec3 v0,v1,v2,v3; 
        vec3 v4,v5,v6,v7;
    	
    	v4 = min;
    	v2 = max;
    
    	v0 = vec3 (min.x,min.y,max.z);
    	v1 = vec3 (max.y,min.y,max.z);
    	v3 = vec3 (min.x,max.y,max.z);
    	
    	v5 = vec3 (max.x,min.y,min.z);
    	v6 = vec3 (min.x,max.y,min.z);
    	v7 = vec3 (max.x,max.y,min.z);
    	
 		pinta_cara(v0,v1,v2,v3); // z posiitva 
 		pinta_cara(v4,v5,v7,v6); // z negativa 
 		pinta_cara(v4,v0,v1,v5); // y negativa 
 		pinta_cara(v6,v3,v2,v7); // y positiva 
 		pinta_cara(v4,v0,v3,v6); // x negativa 
 		pinta_cara(v4,v0,v3,v6); // x negativa 
 		pinta_cara(v5,v1,v2,v7); // x positiva 
	    
	    
    }
    
    
}
