// ----------------------------------------------
// Informatique Graphique 3D & Réalité Virtuelle.
// Travaux Pratiques
// Shaders
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
// ----------------------------------------------

// Add here all the value you need to describe the light or the material.
// At first used const values.
// Then, use uniform variables and set them from the CPU program.

const vec3 lightPos = vec3 (5.0, 5.0, 5.0);
const vec3 matAlbedo = vec3 (0.6, 0.6, 0.6);

float diffuseRef = 0.5;
float specRef = 0.7;
float shininess = 5.0;

varying vec4 P; // fragment-wise position
varying vec3 N; // fragment-wise normal

void main (void) {
    gl_FragColor = vec4 (0.0, 0.0, 0.0, 1.0);

    vec3 p = vec3 (gl_ModelViewMatrix * P);
    vec3 n = normalize (gl_NormalMatrix * N);
    vec3 l = normalize (lightPos - p);
    vec3 v = normalize (-p);
    vec3 wh = normalize (l+v);

    for (int i = 0; i < 4; i++) {
        float diffuse = max (dot (l, n), 0.0);
        vec3 r = reflect (l, n);


        float spec = max(dot(n, wh), 0.0);
        spec = pow (spec, shininess);
        spec = max (0.0, spec);

        vec4 LightContribution = diffuseRef * diffuse * gl_LightSource[i].diffuse + specRef * spec * gl_LightSource[i].specular;
        gl_FragColor += vec4 (LightContribution.xyz, 1.0);
    }

}

