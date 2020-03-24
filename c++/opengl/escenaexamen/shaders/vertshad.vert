#version 330 core



uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;


out vec3 matambf;
out vec3 matdifff;
out vec3 matspecf;
out float matshinf;



in vec3 vertex;
in vec3 normal;


out vec3 fcolor;
out vec3 normalSCO;
out vec3 vertexSCO;


out mat4 viewaux;


void main()
{
    matambf = matamb;
    matdifff = matdiff;
    matspecf = matspec;
    matshinf = matshin;
    viewaux = view;
    mat3 normalMatrix = inverse(transpose(mat3(view*TG)));
    normalSCO = normalize(normalMatrix*normal);
    //vec4 posFocusSCO = view * vec4(posFocus,1.0);
    //vec4 posFocusSCO = vec4(posFocus,1.0);
    vertexSCO = (view*TG*vec4(vertex,1.0)).xyz;
    gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
