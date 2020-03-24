#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;



vec3 matambaux;
vec3 matdiffaux;
vec3 matspecaux;
float matshinaux;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
vec3 colFocus = vec3(0.8, 0.8, 0.8);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocusEscena = vec3(1, 1, 1);
vec3 posFocusCamera = vec3(0, 0, 0);


out vec3 fcolor;

vec3 Lambert (vec3 NormSCO, vec3 L)
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * matambaux;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * matdiffaux * dot (L, NormSCO);
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

    if ((dot(R, V) < 0) || (matshin == 0))
      return colRes;  // no hi ha component especular

    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinaux);
    return (colRes + matspecaux * colFocus * shine);
}

vec3 ambv = vec3(0.25,0.25,0.25);
vec3 diffv = vec3(0.74,0.74,0.74);
vec3 specv = vec3(1,1,1);
float shinv = 100;


uniform bool vacagris;
uniform bool fescena;


vec3 focusCian = vec3(0.0,0.8,0.8);
vec3 focusBlanco = vec3(0.8,0.8,0.8);


void main()
{

    mat3 normalMatrix = inverse(transpose(mat3(view*TG)));
    vec3 normalSCO = normalize(normalMatrix*normal);

    vec4 posFocusSCO;
    if(fescena)  {
        posFocusSCO = view*vec4(posFocusEscena,1.0);
        colFocus = focusCian;
    }
    else {
        posFocusSCO = vec4(posFocusCamera,1.0);
        colFocus = focusBlanco;
    }
    vec4 vertexSCO = view*TG*vec4(vertex,1.0);
    vec3 vectorLSCO = normalize(posFocusSCO.xyz-vertexSCO.xyz);
    //fcolor = Lambert(normalSCO,vectorLSCO);
    if (vacagris) {
        matambaux  = matamb;
        matdiffaux = diffv;
        matspecaux = specv;
        matshinaux = shinv;
       }
    else {

        matambaux  = matamb;
        matdiffaux = matdiff;
        matspecaux = matspec;
        matshinaux = matshin;

        }
    if(fescena) {



        }
    fcolor = Phong(normalSCO,vectorLSCO,vertexSCO);
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
