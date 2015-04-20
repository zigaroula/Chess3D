#version 400

struct Light
{
    vec3 position;
    vec3 diffuse_color;
    vec3 specular_color;
};

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

uniform Light lights[1];

void main(void)
{
    vec3 lightPos = lights[0].position;
    vec3 diffuseColor = lights[0].diffuse_color;
    vec3 specColor = lights[0].specular_color;

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

    //float bias = 1-(0.001*tan(acos(dot(normal, lightDir))));
    float bias = 0.9999;
    vec4 shadow_coord2 = shadow_coord;
    shadow_coord2.z *= bias;
    float shadow = textureProj (shadow_text , shadow_coord2);

    vec3 ambient = ambient_color;

    if (texture_enabled) {
        ambient = vec3(texture(object_texture, texture_coord));
    }

    if (shadow<1.0) {
        shadow = 0.1;
    }

    outputColor = vec4(ambient + shadow*diffuse + shadow*specular, 1.0);

}
