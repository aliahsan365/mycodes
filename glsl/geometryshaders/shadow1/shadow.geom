#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;

uniform mat4 modelViewProjectionMatrixInverse;

uniform mat4 modelViewProjectionMatrix;

vec4 colornegro = vec4(0,0,0,0);

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
   for( int i = 0 ; i < 3 ; i++ )
	{
		
         // de clip space a object space
         vec4  objspace =modelViewProjectionMatrixInverse *gl_in[i].gl_Position;
         float ymin = boundingBoxMin.y;
         vec3  sombrapos = vec3(objspace.x,ymin,objspace.z);
         gfrontColor = colornegro;
         gl_Position = modelViewProjectionMatrix*vec4(sombrapos,1.0);
	 EmitVertex();
	}
    EndPrimitive();
}
