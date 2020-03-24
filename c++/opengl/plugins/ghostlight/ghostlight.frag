#version 330 core
out vec4 fragColor;
in vec4 col;
in vec2 vtex;


uniform float mouseX;
uniform float mouseY;
uniform int n;
void main() {
  //if (mod((gl_FragCoord.y-0.5), float(n)) > 0.0) discard;
  
  vec2 mosuePos = vec2(mouseX,mouseY);
  float d  = distance(vtex,mosuePos);
  vec4 colp = col;
  
  if (d>100) {
	  //colp = vec4(1,0,0,1);
	  colp.a = 0.025;
	  
	  }
  else {
	  colp.a = 0.25;
	  
	  }
  
  fragColor=colp;
}
