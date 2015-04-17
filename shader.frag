#version 400

in vec3 color_interp;
in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 outputColor;

uniform mat4 view_matrix;
uniform vec3 ambient_color;

vec3 lightPos = vec3(100.0,100.0,100.0);
const vec3 diffuseColor = vec3(0.0, 0.0, 1.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main(void)
{
    lightPos = vec3(view_matrix * vec4(lightPos,1));
    vec3 normal = normalize(vertex_normal);
    vec3 lightDir = normalize(lightPos - vertex_position);

    float lambertian = max(dot(lightDir,normal), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0) {

        vec3 viewDir = normalize(-vertex_position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, 16.0);
    }

    outputColor = vec4(ambient_color + lambertian * diffuseColor +specular * specColor, 1.0);

}
