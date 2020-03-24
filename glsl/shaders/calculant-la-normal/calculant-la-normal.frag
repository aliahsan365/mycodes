#version 330 core

in vec4 frontColor;
out vec4 fragColor;


uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;


uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform vec4 matShininess;



vec4 colorLightLambert() {
   vec4 lightColor = vec4(1,1,1,1);
   return lightColor;

}




void main()
{
    fragColor = frontColor;
} 
