#version 400

in vec4 color_out;
in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 outputColor;

void main(void)
{
   outputColor = color_out;

}
