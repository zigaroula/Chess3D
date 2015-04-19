#version 400

uniform mat4 proj_view_model;

in vec3 vertex;
in vec2 texture;

out vec2 texture_coord;


void main()
{
    gl_Position = proj_view_model * vec4(vertex, 1.0);
    texture_coord = texture;

}
