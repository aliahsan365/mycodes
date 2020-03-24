#version 330 core

in vec4 frontColor;
out vec4 fragColor;


in vec3 normalf;



void main()
{
    //la normalizo otra vex pk pasa interpolada del vs -> fs
    vec3 normalized_normal = normalize(normalf);
    fragColor = frontColor * normalized_normal.z;


}
