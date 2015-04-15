#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
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
    void reload();
private:
    GLuint id;
    std::string name;
    GLuint type;
    std::string filename;
    std::string source;
};

#endif // SHADER_H
