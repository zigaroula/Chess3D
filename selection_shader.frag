#version 400

uniform int code;

uniform bool texture_enabled;

in vec2 texture_coord;

out vec4 outputF;

void main()
{
	if (texture_enabled) {

		int x_row = int((texture_coord.x - 0.703) / 0.036);
		int y_row = int((texture_coord.y - 0.709) / 0.0353);

		int cell = 8*y_row+x_row + 100;
		outputF = vec4(cell/255.0, 0, 0, 0);
	}
	else
        outputF = vec4(code/255.0, 0, 0, 0);
}
