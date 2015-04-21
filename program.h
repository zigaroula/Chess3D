#ifndef PROGRAM_H
#define PROGRAM_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#include "shader.h"

class Program {
public:
    void init();
    void initForShadowMap();
    void initForSelection();
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
