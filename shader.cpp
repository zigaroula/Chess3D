#include "shader.h"

using namespace std;

Shader::Shader(const string & _name, GLuint _type) {
    id = glCreateShader (_type);
    name = _name;
    type = _type;
    filename = "";
    source = "";
}

void Shader::loadFromFile (const string & _filename) {
    filename = _filename;
    ifstream in (filename.c_str());
    if (!in)
        cout << "Error loading shader source file" << endl;
    string source;
    char c[2];
    c[1]='\0';
    while (in.get (c[0])) {
        source.append (c);
    }
    in.close ();
    setSource (source);
}

void Shader::compile () {
    const GLchar * tmp = source.c_str();
    glShaderSource (id, 1, &tmp, NULL);
    glCompileShader (id);
    GLint shaderCompiled;
    glGetShaderiv (id, GL_COMPILE_STATUS, &shaderCompiled);
    if (!shaderCompiled)
        cout << "Error: shader not compiled." << endl;
}

void Shader::reload () {
    if (filename != "") {
        loadFromFile (std::string (filename));
        compile ();
    }
}
