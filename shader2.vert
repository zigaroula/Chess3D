#version 400

in vec3 vertex;
in vec3 color;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;

out vec4 color_out;

void main(void)
{
        gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex, 1.0);
        color_out = vec4(color, 1.0);
}
