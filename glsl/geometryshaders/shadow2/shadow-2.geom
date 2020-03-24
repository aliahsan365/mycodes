#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;


uniform mat4 modelViewProjectionMatrixInverse;

uniform mat4 modelViewProjectionMatrix;

vec4 colornegro = vec4(0,0,0,0);

float R;
vec3 C;

vec4 colorcian = vec4 (0,1,1,1);


void pinta_suelo() {
   
   //pintar un cuadrado usando 4 vertices a una cierta Y, y de color cian.
   gfrontColor = colorcian;
   vec3 P = vec3(C.x,boundingBoxMin.y-0.01,C.z);
   vec3 P1 = vec3(P.x - R, P.y, P.z - R);
   vec3 P2 =  vec3(P.x + R, P.y, P.z - R);
   vec3 P3 =  vec3(P.x - R, P.y, P.z + R);
   vec3 P4 =  vec3(P.x + R, P.y, P.z + R);
   
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gl_Position = modelViewProjectionMatrix*vec4(P1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(P2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(P3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(P4,1.0);
   EmitVertex();
   EndPrimitive();
}

void main( void )
{
	
	//radi
	R = (distance(boundingBoxMin,boundingBoxMax)/2);
	// centro caja
	C = (boundingBoxMax + boundingBoxMin)/2;
	
	if (gl_PrimitiveIDIn == 0) {
	   pinta_suelo();
	
	}
	
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
