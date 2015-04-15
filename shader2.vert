#version 400

in vec3 vertex;
in vec3 color;

out vec4 color_out;

void main(void)
{
        gl_Position = vec4(vertex, 1.0);
        color_out = vec4(color, 1.0);
}
