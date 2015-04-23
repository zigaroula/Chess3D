#version 400

struct Light
{
    vec3 position;
    vec3 diffuse_color;
    vec3 specular_color;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec4 shadow_coord[2];
in vec2 texture_coord;
in vec3 skybox_texcoords;

out vec4 outputColor;

uniform mat4 view_matrix;
uniform mat4 inv_view_matrix;
uniform vec3 diffuse_color;
uniform sampler2DShadow shadow_text[2];

uniform sampler2D object_texture;
uniform bool texture_enabled;
uniform bool skybox_enabled;
uniform bool shadow_enabled;
uniform bool light_enabled[2];

uniform samplerCube cube_texture;

uniform Light lights[2];

void main(void)
{
    int light_count = 2;
    vec3 diffuse_color_ = diffuse_color;

    if (texture_enabled) {
        diffuse_color_ = vec3(texture(object_texture, texture_coord));
    }

    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    float bias = 0.999;

    for (int i = 0; i < light_count; ++i)
    {
        vec4 shadow_coord2 = shadow_coord[i];
        shadow_coord2.z *= bias;

        float shadow = 1;
        float shadow_coeff = textureProj(shadow_text[i] , shadow_coord2);
        if (shadow_coeff < 1.0)
            shadow = 0.5;

        vec3 lightPos = lights[i].position;
        vec3 diffuseColor = lights[i].diffuse_color;
        vec3 specColor = lights[i].specular_color;

        lightPos = vec3(view_matrix * vec4(lightPos,1));
        vec3 normal = normalize(frag_normal);
        vec3 lightDir = normalize(lightPos - frag_position);

        if (!shadow_enabled)
            shadow = 1.f;

        float lambertian = max(dot(lightDir,normal), 0.0);
        diffuse += shadow * lambertian * diffuse_color_;

        if(lambertian > 0.0) {

            vec3 viewDir = normalize(-frag_position);
            vec3 halfDir = normalize(lightDir + viewDir);
            float specAngle = max(dot(halfDir, normal), 0.0);
            specular += shadow * pow(specAngle, 16.0) * specColor;
        }
    }

    //float bias = 1-(0.001*tan(acos(dot(normal, lightDir))));

    vec3 ambient = vec3(0.0);
    
    // EFFETS
    vec3 incident_eye = normalize (frag_position);
    vec3 normal_eye = normalize (frag_normal);
    //REFLECTION
    vec3 reflected = reflect (incident_eye, normal_eye);
    reflected = vec3 (inv_view_matrix * vec4 (reflected, 0.0));
    //REFRACTION
    float ratio = 1.0 /1.3333;
    vec3 refracted = refract (incident_eye, normal_eye, ratio);
    refracted = vec3 (inv_view_matrix * vec4 (refracted, 0.0));

    if (skybox_enabled) {
        outputColor = vec4(texture (cube_texture, skybox_texcoords));
    } else if (texture_enabled) {
        int x_row = int((texture_coord.x - 0.703) / 0.036);
        int y_row = int((texture_coord.y - 0.709) / 0.0353);
        if((x_row <8 && x_row >=0 && y_row <8 && y_row >=0)
                &&(((x_row %2 == 0)&&( y_row %2 ==0))
                ||((x_row %2 == 1)&&( y_row %2 ==1)))){
            outputColor = vec4(ambient + diffuse + specular, 1.0) + 0.6*texture (cube_texture, reflected);
        }else{
            outputColor = vec4(ambient + diffuse + 0.7*specular, 1.0);
        }
    } else {
        //outputColor = vec4(ambient + diffuse + specular, 1.0) + 0.9*texture (cube_texture, refracted);
        outputColor = vec4(ambient + diffuse + specular, 1.0);
    }


}
