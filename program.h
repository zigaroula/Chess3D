#ifndef PROGRAM_H
#define PROGRAM_H

#include "shader.h"

class Program {
public:
    Program(const std::string & , const std::string & , const std::string &);
    ~Program();
    void attach(Shader *);
    void detach(Shader *);
    void link();
    void use();
    void stop();
    void reload();
private:
    GLuint id;
    std::string name;
    std::vector<Shader*> shaders;
};

#endif // PROGRAM_H
