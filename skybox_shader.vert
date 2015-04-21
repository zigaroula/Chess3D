#version 400

in vec3 vertex;

out vec3 texcoords;

uniform mat4 MVP;

void main () {
  //texcoords = vertex;
  gl_Position = MVP * vec4 (vertex, 1.0);
}
