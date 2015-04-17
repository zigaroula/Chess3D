#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec4 shadow_coord;

out vec4 outputColor;

uniform mat4 view_matrix;
uniform vec3 ambient_color;
uniform sampler2DShadow shadow_text;

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

    float visibility = 1.0; 
    
   /* if ( texture(shadow_text, shadow_coord.xy).z  <  shadow_coord.z){ 
        visibility = 0.0; 
    }*/

	float shadow = textureProj ( shadow_text , shadow_coord );
	//outputColor = texture(shadow_text, shadow_coord.xy);
    outputColor = shadow * vec4(ambient_color + visibility*lambertian * diffuseColor + visibility*specular * specColor, 1.0);

}
