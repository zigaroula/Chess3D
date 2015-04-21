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
in vec3 skybox_texcoords;

out vec4 outputColor;

uniform mat4 view_matrix;
uniform vec3 diffuse_color;
uniform sampler2DShadow shadow_text;

uniform sampler2D object_texture;
uniform bool texture_enabled;
uniform bool skybox_enabled;

uniform samplerCube cube_texture;

uniform Light lights[1];

void main(void)
{
    vec3 diffuse_color_ = diffuse_color;

    if (texture_enabled) {
        diffuse_color_ = vec3(texture(object_texture, texture_coord));
    }

    vec3 lightPos = lights[0].position;
    vec3 diffuseColor = lights[0].diffuse_color;
    vec3 specColor = lights[0].specular_color;

    lightPos = vec3(view_matrix * vec4(lightPos,1));
    vec3 normal = normalize(frag_normal);
    vec3 lightDir = normalize(lightPos - frag_position);

    float lambertian = max(dot(lightDir,normal), 0.0);
    vec3 diffuse = lambertian * diffuse_color_;

    vec3 specular = vec3(0.0);

    if(lambertian > 0.0) {

        vec3 viewDir = normalize(-frag_position);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, 16.0) * specColor;
    }

    //float bias = 1-(0.001*tan(acos(dot(normal, lightDir))));
    float bias = 0.999;
    vec4 shadow_coord2 = shadow_coord;
    shadow_coord2.z *= bias;
    float shadow = textureProj (shadow_text , shadow_coord2);

    if (shadow<1.0) 
        shadow = 0.5;

    vec3 ambient = vec3(0.0);
    
    if (skybox_enabled) {
        outputColor = vec4(texture (cube_texture, skybox_texcoords));
        //outputColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    } else {
        outputColor = vec4(ambient + shadow * (diffuse + specular), 1.0);
    }


}
