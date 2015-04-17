#version 400

// Profondeur en sortie
layout(location = 0) out float fragmentdepth;

void main(){
    fragmentdepth = gl_FragCoord.z;
}
