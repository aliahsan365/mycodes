#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;


out vec4 gfrontColor;


const float step = 0.2;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform mat3 normalMatrix;


vec4 color_grey = vec4(0.8,0.8,0.8,1);

vec3 calcula_baricentro(vec3 a, vec3 b, vec3 c) {
     vec3 barc;
     barc = vec3((a.x+b.x+c.x)/3,(a.y+b.y+c.y)/3,(a.z+b.z+c.z)/3);
     return barc;
}




void pinta_cara_frontal_z(vec3 P) {

   float m = step; 
   vec3 P1 = vec3(P.x, P.y, P.z + m);
   vec3 v1 = vec3(P1.x - m , P1.y - m, P1.z);
   vec3 v2 = vec3(P1.x + m , P1.y - m, P1.z);
   vec3 v3 = vec3(P1.x - m , P1.y + m, P1.z);
   vec3 v4 = vec3(P1.x + m , P1.y + m, P1.z);
   gfrontColor = color_grey * (normalMatrix * vec3(0,0,1)).z;
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   EndPrimitive();
}



void pinta_cara_trasera_z(vec3 P) {

   float m = step;
   vec3 P1 = vec3(P.x, P.y, P.z - m);
   vec3 v1 = vec3(P1.x - m , P1.y - m, P1.z);
   vec3 v2 = vec3(P1.x + m , P1.y - m, P1.z);
   vec3 v3 = vec3(P1.x - m , P1.y + m, P1.z);
   vec3 v4 = vec3(P1.x + m , P1.y + m, P1.z);
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gfrontColor = color_grey * (normalMatrix * vec3(0,0,-1)).z;
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   EndPrimitive();
}


void pinta_cara_frontal_x(vec3 P) {

   float m = step;
   vec3 P1 = vec3(P.x + m, P.y, P.z);
   vec3 v1 = vec3(P1.x, P1.y-m, P1.z+m);
   vec3 v2 = vec3(P1.x, P1.y-m, P1.z-m);
   vec3 v3 = vec3(P1.x, P1.y+m, P1.z+m);
   vec3 v4 = vec3(P1.x, P1.y+m, P1.z-m);
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gfrontColor = color_grey * (normalMatrix * vec3(1,0,0)).z;
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   EndPrimitive();
}

void pinta_cara_trasera_x(vec3 P) {

   float m = step;

   vec3 P1 = vec3(P.x - m, P.y, P.z);
   vec3 v1 = vec3(P1.x, P1.y-m, P1.z-m);
   vec3 v2 = vec3(P1.x, P1.y-m, P1.z+m);
   vec3 v3 = vec3(P1.x, P1.y+m, P1.z-m);
   vec3 v4 = vec3(P1.x, P1.y+m, P1.z+m);
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gfrontColor = color_grey * (normalMatrix * vec3(-1,0,0)).z;
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   EndPrimitive();
}


void pinta_cara_frontal_y(vec3 P) {

   float m = step;
   vec3 P1 = vec3(P.x, P.y + m, P.z);
   vec3 v1 = vec3(P1.x-m, P1.y, P1.z+m);
   vec3 v2 = vec3(P1.x+m, P1.y, P1.z+m);
   vec3 v3 = vec3(P1.x-m, P1.y, P1.z-m);
   vec3 v4 = vec3(P1.x+m, P1.y, P1.z-m);
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gfrontColor = color_grey * (normalMatrix * vec3(0,1,0)).z;
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   EndPrimitive();
}


void pinta_cara_trasera_y(vec3 P) {

   float m = step;
   vec3 P1 = vec3(P.x, P.y - m, P.z);
   vec3 v1 = vec3(P1.x+m, P1.y, P1.z+m);
   vec3 v2 = vec3(P1.x-m, P1.y, P1.z+m);
   vec3 v3 = vec3(P1.x+m, P1.y, P1.z-m);
   vec3 v4 = vec3(P1.x-m, P1.y, P1.z-m);
   //--PUNTOS ACABADO el orden va de abajo hacia arriba de iz a drecha en zig-zag
   gfrontColor = color_grey * (normalMatrix * vec3(0,-1,0)).z;
   gl_Position = modelViewProjectionMatrix*vec4(v1,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v2,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v3,1.0);
   EmitVertex();
   gl_Position = modelViewProjectionMatrix*vec4(v4,1.0);
   EmitVertex();
   EndPrimitive();
}



void pinta_cubo(vec3 P) {
   
   pinta_cara_frontal_z(P);
   pinta_cara_trasera_z(P);
   pinta_cara_frontal_x(P);
   pinta_cara_trasera_x(P);
   pinta_cara_frontal_y(P);
   pinta_cara_trasera_y(P);
}



void main( void )
{
    //por cada tringualo pintar un cubo
    vec3 a = (gl_in[0].gl_Position).xyz;
    vec3 b = (gl_in[1].gl_Position).xyz;
    vec3 c = (gl_in[2].gl_Position).xyz;
    vec3 bar = calcula_baricentro(a,b,c);
	vec3 punto_central = round(bar/step)*step;
	pinta_cubo(punto_central);
}
