#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

void aplica_translacio(float x , float y) {

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
	
		float w = gl_in[i].gl_Position.w;
		float xt = x * w;
		float yt = y * w;
		vec4 v = gl_in[i].gl_Position;
		v.x += xt;
		v.y += yt;
		gl_Position = v;
		EmitVertex();
	}
    EndPrimitive();



}


void main( void )
{
  aplica_translacio(0.5,0.5);
  aplica_translacio(0.5,-0.5);
  aplica_translacio(-0.5,0.5);
  aplica_translacio(-0.5,-0.5);
}
