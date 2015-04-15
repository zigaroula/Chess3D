#include "program.h"

using namespace std;

Program::Program(const string & _name, const string & _vertexShaderFilename, const string & _fragmentShaderFilename) {
    id = glCreateProgram();
    name = _name;
    Shader * vs = new Shader (_name + " Vertex Shader", GL_VERTEX_SHADER);
    Shader * fs = new Shader (_name + " Fragment Shader",GL_FRAGMENT_SHADER);
    vs->loadFromFile (_vertexShaderFilename);
    vs->compile ();
    attach(vs);
    fs->loadFromFile (_fragmentShaderFilename);
    fs->compile ();
    attach(fs);
    link();
}

void Program::attach (Shader * shader) {
    glAttachShader (id, shader->getId());
    shaders.push_back (shader);
}

void Program::link () {
    glLinkProgram (id);
    GLint linked;
    glGetProgramiv (id, GL_LINK_STATUS, &linked);
    if (!linked)
        cout << "Shaders not linked" << endl;
}
