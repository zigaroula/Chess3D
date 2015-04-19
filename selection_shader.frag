#version 400

uniform int code;

uniform sampler2D object_texture;
uniform bool texture_enabled;

out vec4 outputF;

void main()
{
	if (texture_enabled)
		outputF = vec4(100/255.0, 0, 0, 0);
	else
    	outputF = vec4(code/255.0, 0, 0, 0);
}
