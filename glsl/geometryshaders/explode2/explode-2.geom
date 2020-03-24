#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

in vec3 vnormal[];

const float speed=1.2;
const float angSpeed = 8.0;
uniform float time;

uniform mat4 modelViewProjectionMatrix;


vec3 calcula_baricentro(vec3 a, vec3 b, vec3 c) {
     vec3 barc;
     barc = vec3((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3,(a.z+b.z+c.z)/3);
     return barc;

}

void main( void )
{
   vec3 N = (vnormal[0] + vnormal[1] + vnormal[2])/3;
   vec3 C = calcula_baricentro(gl_in[0].gl_Position.xyz,gl_in[1].gl_Position.xyz,gl_in[2].gl_Position.xyz);
   vec3 movi =  speed * time * N;
   float a = angSpeed*time;        
   vec3 c1 = vec3(cos(a),sin(a),0);
   vec3 c2 = vec3((-1*sin(a)),cos(a),0);
   vec3 c3 = vec3(0,0,1);
   mat3 rz = mat3(c1,c2,c3);
   for( int i = 0 ; i < 3 ; i++ ) {
       gfrontColor = vfrontColor[i];
       vec3 V = gl_in[i].gl_Position.xyz;
       vec3 T = (-1*C) + V;
       vec3 R = rz*T;
       vec3 TT = movi + R;
       vec3 TTT = (1*C)+TT;
       gl_Position = modelViewProjectionMatrix*vec4(TTT,1);
	   EmitVertex();
	}
   EndPrimitive();
}
