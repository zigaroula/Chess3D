#ifndef SHADER_H
#define SHADER_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/gl3.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Shader {
public:
    Shader (const std::string & , GLuint);
    ~Shader();
    void loadFromFile(const std::string &);
    void setSource (const std::string & _source) { source = _source; }
    GLuint getId() { return id; }
    void compile ();
private:
    GLuint id;
    std::string name;
    GLuint type;
    std::string filename;
    std::string source;
};

#endif // SHADER_H
