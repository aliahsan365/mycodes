#version 330 core
out vec4 fragColor;
in vec4 col;
uniform int n;
void main() {
  if (mod((gl_FragCoord.y-0.5), float(n)) > 0.0) discard;
  fragColor=col;
}
