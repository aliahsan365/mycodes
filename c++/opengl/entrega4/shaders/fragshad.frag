#version 330 core


out vec4 FragColor;



in vec3 matambf;
in vec3 matdifff;
in vec3 matspecf;
in float matshinf;



// Valors per als components que necessitem dels focus de llum
//color del foco ha de ser blanco en rgb
vec3 colFocus = vec3(1,1,1);
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
//vec3 posFocus = vec3(1, 1, 1);  // en SCA



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


// el posfocus lo recibimos desde la app 

uniform vec3 posFocus;

// lo mismo , des de app. indica si fijo o movil respeto a la escena 
uniform bool fescena;

//recivo la matriz de view para hacer los calculos.
in mat4 fview;


void main()
{	
	
	vec4 posFocusSCO;
	if (fescena) {
		//es mante fije segons l'escena
		posFocusSCO = fview * vec4(posFocus,1.0);
		}
	else {
		 //posfocus situado exactamente donde la camara.
		 posFocusSCO = vec4(vec3(0,0,0),1.0);
	}
	
   vec3 vectorLSCO = normalize(posFocusSCO.xyz-vertexSCO.xyz);

	//FragColor = Lambert(normalSCO,vectorLSCO);

	//calulo del color usando phon
	FragColor =  vec4(Phong(normalSCO,vectorLSCO,vec4(vertexSCO,1)), 1);	
}
