#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;


out vec4 frontColor;


uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

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


vec4 phong(vec3 N, vec3 V, vec3 L) {
     
      //calculamos R y lo normalizado (unitario)
      vec3 R=normalize(2*dot(N, L)*N-L);

      float nlmaxdot = max(0.0,dot(N,L));
      float rvmaxdot = max(0.0,dot(R,V));
      // en un punto incial la contribuacion de lamber y phonh es nula v4(0)
      vec4 lambertContrib = vec4(0,0,0,0);
      vec4 phongContrib = vec4(0,0,0,0);
      if (nlmaxdot > 0) {
       	lambertContrib = matDiffuse*lightDiffuse*nlmaxdot;
      }
      if (rvmaxdot > 0)  {
           if (nlmaxdot>0)  { 
            phongContrib = matSpecular*lightSpecular*pow(rvmaxdot,matShininess);
            }
           // si nlmaxdot no supera es pk la s no tiene efecto
           else {
            phongContrib = matSpecular*lightSpecular;
           
           }
      
      }
     return matAmbient*lightAmbient+lambertContrib+phongContrib;
}




void main()
{
    vec3 N = normalize(normalMatrix * normal);
    //N es la normal en eye space unitaria por haber sido normalizada.
    N = normalize(N);
    vec3 vertice_eyespace = (modelViewMatrix*vec4(vertex,1.0)).xyz;
    //se puede poner directamente -vertice_eyespace
    vec3 V = normalize(vec3(0.0,0.0,0.0)-vertice_eyespace);
    //vector light, en eye space
    vec3 L = lightPosition.xyz-vertice_eyespace.xyz;
    // L es normalizado por que por def es unitario
    L = normalize(L);
    frontColor = phong(N,V,L);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
