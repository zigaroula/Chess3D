#version 400

in vec3 vertex;
in vec3 normal;
in vec2 texture;

out vec3 frag_position;
out vec3 frag_normal;
out vec4 shadow_coord;
out vec2 texture_coord;

uniform mat4 normal_matrix;
uniform mat4 bias_matrix;

uniform mat4 view_model;
uniform mat4 proj_view_model;

void main(void)
{
    gl_Position = proj_view_model * vec4(vertex, 1.0);
    vec4 vertPos4 = view_model * vec4(vertex, 1.0);

    frag_position = vec3(vertPos4);
    frag_normal = vec3(normal_matrix * vec4(normal, 0.0));

    shadow_coord = bias_matrix * vec4(vertex, 1.0);
    texture_coord = texture;
}
