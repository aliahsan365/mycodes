#version 330 core

in vec4 frontColor;
out vec4 fragColor;


//esta son las I's
uniform vec4 lightAmbient; //Ia
uniform vec4 lightDiffuse; //Id
uniform vec4 lightSpecular; //Is

uniform vec4 lightPosition; // pos del foco


//estas son las K's
uniform vec4 matAmbient; //Ka
uniform vec4 matDiffuse; //Kd
uniform vec4 matSpecular; //Ks

uniform float matShininess; //s



uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;



in vec3 fnormal;
in vec3 fvertex;


uniform bool world = true;

uniform mat4 modelViewMatrixInverse;
vec4 light(vec3 N, vec3 V, vec3 L) {
  N=normalize(N);
  V=normalize(V);
  L=normalize(L);
  vec3 R=normalize(2*dot(N, L)*N-L);
  float NdotL=max(0, dot(N, L));
  float RdotV=max(0, dot(R, V));
  float ldiff=NdotL;
  float lspec=0; 
  if (NdotL>0) lspec=pow(RdotV, matShininess); 
  return matAmbient*lightAmbient + matDiffuse*lightDiffuse*ldiff + matSpecular*lightSpecular*lspec;
}


void main()
{
   vec4 light_color = vec4(0,0,0,0);
   if (world) {
   	//light_color = vec4(0,0,0,0);
        vec3 N  = normalize(fnormal);
        // punto de la camara , al ser punto x eso en la 4rt componente es 1
        vec3 world_camara = (modelViewMatrixInverse*vec4(0,0,0,1)).xyz;
        vec3 V =  normalize(world_camara-fvertex);
        //pasamos la pos de la luz que esta en el eye space a world space
        vec3 world_light = (modelViewMatrixInverse*lightPosition).xyz;
        vec3 L = normalize(world_light-fvertex); 
   	light_color = light(N,V,L);
   }
   else {
        vec3 N = normalize(normalMatrix * fnormal);
	N = normalize(N);
    	vec3 vertice_eyespace = (modelViewMatrix*vec4(fvertex,1.0)).xyz;
    	vec3 V = normalize(vec3(0.0,0.0,0.0)-vertice_eyespace);
    	//vector light, en eye space
    	vec3 L = lightPosition.xyz-vertice_eyespace.xyz;
    	// L es normalizado por que por def es unitario
    	L = normalize(L);
        light_color = light(N,V,L);

    }
    fragColor =  light_color;

}
