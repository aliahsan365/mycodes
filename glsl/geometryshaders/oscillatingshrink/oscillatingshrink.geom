#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

//uniform float speed;
//uniform float time;

const float speed = 1.0;
const float time = 0.2;



vec3 calcula_baricentro(vec3 a, vec3 b, vec3 c) {
     vec3 barc;
     barc = vec3((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3,(a.z+b.z+c.z)/3);
     return barc;
}

uniform mat4 modelViewProjectionMatrix;



void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
                if (0 <= time && time < 1.0/speed) {
		   if (gl_PrimitiveIDIn%2 == 0) {
		        gfrontColor = vfrontColor[i];
		        gl_Position = gl_in[i].gl_Position;
		        EmitVertex();
		    }
		   else {
		      
		      vec3 v0 = (gl_in[0].gl_Position).xyz;
		      vec3 v1 = (gl_in[1].gl_Position).xyz;
		      vec3 v2 = (gl_in[2].gl_Position).xyz;
		      
		      vec3 bc = calcula_baricentro(v0,v1,v2);
		      float f = time * speed; 
		      
		      vec3 nv0 = mix(v0,bc,fract(f));
		      gfrontColor = vfrontColor[0];
		      gl_Position =modelViewProjectionMatrix * vec4(nv0,1) ;
		      EmitVertex();
		      
		      vec3 nv1 = mix(v1,bc,fract(f));
		      gfrontColor = vfrontColor[1];
		      gl_Position =modelViewProjectionMatrix * vec4(nv1,1) ;
		      EmitVertex();
		   
		      vec3 nv2 = mix(v2,bc,fract(f));
		      gfrontColor = vfrontColor[2];
		      gl_Position =modelViewProjectionMatrix * vec4(nv2,1) ;
		      EmitVertex();
		      EndPrimitive();
		      
		   } 
		
		}
		else if (1.0/speed <= time && time < 2.0/speed) {
		   if (gl_PrimitiveIDIn%2 != 0) {
		        gfrontColor = vfrontColor[i];
		        gl_Position = gl_in[i].gl_Position;
		        EmitVertex();
		    }
		    else {		      
		      vec3 v0 = (gl_in[0].gl_Position).xyz;
		      vec3 v1 = (gl_in[1].gl_Position).xyz;
		      vec3 v2 = (gl_in[2].gl_Position).xyz;
		      
		      vec3 bc = calcula_baricentro(v0,v1,v2);
		      float f = time * speed; 
		      
		      vec3 nv0 = mix(v0,bc,fract(f));
		      gfrontColor = vfrontColor[0];
		      gl_Position =modelViewProjectionMatrix * vec4(nv0,1) ;
		      EmitVertex();
		      
		      vec3 nv1 = mix(v1,bc,fract(f));
		      gfrontColor = vfrontColor[1];
		      gl_Position =modelViewProjectionMatrix * vec4(nv1,1) ;
		      EmitVertex();
		   
		      vec3 nv2 = mix(v2,bc,fract(f));
		      gfrontColor = vfrontColor[2];
		      gl_Position =modelViewProjectionMatrix * vec4(nv2,1) ;
		      EmitVertex();
		      EndPrimitive();
		    }
		}
		
		


	}
    EndPrimitive();
}
