#ifndef PROGRAM_H
#define PROGRAM_H

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

#include "shader.h"

class Program {
public:
    Program(const std::string & , const std::string & , const std::string &);
    ~Program();
    void attach (Shader *);
    void link ();
    GLuint getId() const { return id; }

    void detach(Shader *);
    void use();
    void stop();
    void reload();
private:
    GLuint id;
    std::string name;
    std::vector<Shader*> shaders;
};

#endif // PROGRAM_H
