#version 400

in vec3 vertex;
in vec3 normal;

out vec3 vertex_position;
out vec3 vertex_normal;
out vec4 shadow_coord;

uniform mat4 projection_matrix;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 normal_matrix;
uniform mat4 bias_matrix;

void main(void)
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex, 1.0);
    vec4 vertPos4 = view_matrix * model_matrix * vec4(vertex, 1.0);
    vertex_position = vec3(vertPos4);
    vertex_normal = vec3(normal_matrix * vec4(normal, 0.0));

    shadow_coord = bias_matrix * vec4(vertex, 1.0);
}
