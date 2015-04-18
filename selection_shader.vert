#version 400

uniform mat4 proj_view_model;

in vec3 vertex;

void main()
{
    gl_Position = proj_view_model * vec4(vertex, 1.0);
}
