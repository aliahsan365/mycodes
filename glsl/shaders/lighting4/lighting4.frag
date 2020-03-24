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



    vec3 N = normalize(normalMatrix * fnormal);
    N = normalize(N);
    vec3 vertice_eyespace = (modelViewMatrix*vec4(fvertex,1.0)).xyz;
    vec3 V = normalize(vec3(0.0,0.0,0.0)-vertice_eyespace);
    //vector light, en eye space
    vec3 L = lightPosition.xyz-vertice_eyespace.xyz;
    // L es normalizado por que por def es unitario
    L = normalize(L);
         

    fragColor =  phong(N,V,L);
    

}
