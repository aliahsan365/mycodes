#version 330 core
uniform mat4 modelViewProjectionMatrix;

in vec3 vertex;
in vec3 color;
in vec2 texture;

out vec4 col;
out vec2 vtex;



void main() {
  gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
  
  col=vec4(color,1.0);
  vtex = texture;
}

