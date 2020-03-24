#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;

out vec4 fragColor;



in vec3 gnormal;

uniform mat3 normalMatrix;

uniform sampler2D grass_top, grass_side;



void main()
{

    //cara vertical
    if (gnormal.z == 0) {
        //vec2 modtex = vec2(4*(gtexCoord.x - gtexCoord.y),1.0 - gtexCoord.z/d);
        fragColor = texture(grass_side,gtexCoord);
    
    }
    //cara horizantal
    else {
        fragColor = texture(grass_top,4*gtexCoord.xy);
    }
    

}
