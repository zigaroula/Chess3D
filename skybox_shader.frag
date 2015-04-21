#version 400

in vec3 texcoords;
uniform samplerCube cube_texture;
out vec4 frag_colour;

void main () {
  //frag_colour = texture (cube_texture, texcoords);
    frag_colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
