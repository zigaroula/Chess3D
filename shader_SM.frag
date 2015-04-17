#version 400

// Profondeur en sortie
out float fragmentdepth;

void main(){
    fragmentdepth = gl_FragCoord.z;
}
