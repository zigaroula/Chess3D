#version 400

in vec3 vertex;
in vec3 color;
in vec3 normal;

out vec3 vertex_position;
out vec3 vertex_normal;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 normal_matrix;

out vec4 color_out;

void main(void)
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex, 1.0);
    vec4 vertPos4 = view_matrix * model_matrix * vec4(vertex, 1.0);
    vertex_position = vec3(vertPos4);
    vertex_normal = vec3(normal_matrix * vec4(normal, 0.0));
    color_out = vec4(color, 1.0);
}
