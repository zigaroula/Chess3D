#version 400

in vec3 vertex;
in vec3 normal;
in vec2 texture;

out vec3 frag_position;
out vec3 frag_normal;
out vec4 shadow_coord[2];
out vec2 texture_coord;
out vec3 skybox_texcoords;

uniform mat4 normal_matrix;
uniform mat4 bias_matrix[2];

uniform mat4 view_model;
uniform mat4 proj_view_model;

void main(void)
{
	int light_count = 2;

    gl_Position = proj_view_model * vec4(vertex, 1.0);
    vec4 vertPos4 = view_model * vec4(vertex, 1.0);

    frag_position = vec3(vertPos4);
    frag_normal = vec3(normal_matrix * vec4(normal, 0.0));

    for (int i = 0; i < light_count; ++i)
    	shadow_coord[i] = bias_matrix[i] * vec4(vertex, 1.0);
    	
    texture_coord = texture;

    skybox_texcoords = vertex;
}
