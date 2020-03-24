#version 330 core


out vec4 FragColor;



in vec3 matambf;
in vec3 matdifff;
in vec3 matspecf;
in float matshinf;


// Valors per als components que necessitem dels focus de llum
//luz blanca
uniform vec3 colFocus;

// = vec3(0.8, 0.8, 0.8);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
//foco de camara camara
vec3 posFocus = vec3(0, 0, 0);  // en SCA


in vec3 fcolor;
in vec3 normalSCO;
in vec3 vertexSCO;







vec3 Lambert (vec3 NormSCO, vec3 L)
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matambf;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdifff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO)
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertSCO.xyz);

    if ((dot(R, V) < 0) || (matshinf == 0))
      return colRes;  // no hi ha component especular

    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinf);
    return (colRes + matspecf * colFocus * shine);
}



in mat4 viewaux;





void main()
{
    //pasando posfocus en sco
    vec3 PosFocosCamara = vec3(viewaux*(posFocus,1)).xyz;
    vec3 vectorLSCO = normalize(PosFocosCamara-vertexSCO.xyz);

    //FragColor = Lambert(normalSCO,vectorLSCO);
    //Phong(normalSCO,vectorLSCO,vec4(vertexSCO,1))

    FragColor =  vec4(Phong(normalSCO,vectorLSCO,vec4(vertexSCO,1)), 1);
}
