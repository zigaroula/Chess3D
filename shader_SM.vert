#version 400

in vec3 vertexPosition_modelspace;

//  Matrice du point de vue de la source lumière
uniform mat4 MVP_matrix;

void main(){
    gl_Position =  MVP_matrix * vec4(vertexPosition_modelspace,1);
}
