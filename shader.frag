#version 400

in vec3 frag_position;
in vec3 frag_normal;
in vec4 shadow_coord;
in vec2 texture_coord;

out vec4 outputColor;

uniform mat4 view_matrix;
uniform vec3 ambient_color;
uniform sampler2DShadow shadow_text;

uniform sampler2D object_texture;
uniform bool texture_enabled;

vec3 lightPos = vec3(100.0,100.0,100.0);
const vec3 diffuseColor = vec3(0.0, 0.0, 1.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main(void)
{
    lightPos = vec3(view_matrix * vec4(lightPos,1));
    vec3 normal = normalize(frag_normal);
    vec3 lightDir = normalize(lightPos - frag_position);

    float lambertian = max(dot(lightDir,normal), 0.0);
    vec3 diffuse = lambertian * diffuseColor;

    vec3 specular = vec3(0.0);

    if(lambertian > 0.0) {

        vec3 viewDir = normalize(-frag_position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, 16.0) * specColor;
    }

    float bias = 0.98;
    vec4 shadow_coord2 = shadow_coord;
    shadow_coord2.z *= bias;
    float shadow = textureProj (shadow_text , shadow_coord2);

    vec3 ambient = ambient_color;

    if (texture_enabled) 
        ambient = vec3(texture(object_texture, texture_coord));

    outputColor = shadow * vec4(ambient + diffuse + specular, 1.0);

}
