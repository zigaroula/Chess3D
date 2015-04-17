#version 400

// Profondeur en sortie
out float fragmentdepth;

void main(){
    fragmentdepth = gl_FragCoord.z;
    //fragmentdepth = vec4(gl_FragCoord.z,gl_FragCoord.z,gl_FragCoord.z, 1.0);

}
