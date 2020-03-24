#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

in vec3 vnormal[];

const float speed=0.5;
uniform float time;

uniform mat4 modelViewProjectionMatrix;

uniform mat4 modelViewProjectionMatrixInverse;

void main( void )
{
        vec3 normal_promig = (vnormal[0] + vnormal[1] + vnormal[2])/3;
        vec3 movi =  speed * time * normal_promig;
	for( int i = 0 ; i < 3 ; i++ )
	{
	  gfrontColor = vfrontColor[i];
	  //position en object space
	  vec4 pos_obj = gl_in[i].gl_Position;

          vec4 pos_movido =  pos_obj + vec4(movi,0.0);
          gl_Position = modelViewProjectionMatrix *pos_movido; 
          EmitVertex();
	}
    EndPrimitive();
}
