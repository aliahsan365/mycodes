#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;


in vec3 N;
in vec3 Vertice;

vec4 negre = vec4(0,0,0,1);


void main()
{
   //cara paralela con x
    if (N.x == Vertice.x) {
    	vec2 QX = vec2(Vertice.y,Vertice.z);
   	float dtx = distance(QX,vec2(0.0,0.0));
    	if (dtx < 0.2) {
            fragColor = negre;
           } 
       else  {
    	fragColor = frontColor;
    	}
    }
    //cara paralela con y
    else  if (N.y == Vertice.y)  {
    	vec2 QX = vec2(Vertice.x,Vertice.z);
   	vec2 QY  = vec2 (Vertice.x,Vertice.z);
    	float dtx = distance(QX,vec2(0.5,0.5));
    	float dty = distance(QY,vec2(-0.5,-0.5));
    	if (dtx < 0.2 || dty < 0.2 ) {
            fragColor = negre;
            }
    
        else {
     	    fragColor = frontColor;
        }
     }
    else  if (N.z == Vertice.z) {
    	vec2 QX,QY,QZ;
    	QX = vec2(Vertice.x,Vertice.y);
    	QY = vec2(Vertice.x,Vertice.y);
    	QZ = vec2(Vertice.x,Vertice.y);
        float dtx,dty,dtz;
        dtx = distance(QX,vec2(0.0,0.0));
        dty = distance(QY,vec2(0.5,0.5));
        dtz = distance(QZ,vec2(-0.5,-0.5));
        if (dtx < 0.2 || dty < 0.2 || dtz < 0.2) {
            fragColor = negre;
        }

        else {
            fragColor = frontColor;
        }
    }
    else {
       fragColor = frontColor;
    
    }
}
