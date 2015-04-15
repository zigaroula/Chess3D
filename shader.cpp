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
    ifstream in (filename.c_str()); //wtf
    if (!in)
        throw Exception ("Error loading shader source file: " + _filename);
    string source;
    char c[2];
    c[1]='\0';
    while (in.get (c[0]))
        source.append (c);
    in.close ();
    setSource (source);
}
