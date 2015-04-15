#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "shader.h"

class Program {
public:
    Program(const std::string & , const std::string & , const std::string &);
    ~Program();
private:
    GLuint id;
    std::string name;
    std::vector<Shader*>_shaders;
};

#endif // PROGRAM_H
