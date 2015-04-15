#ifndef __vao_h_
#define __vao_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/gl3.h>
#endif

#include <glm/glm.hpp>

class Vao
{
public:
    GLuint getId() const { return vao; }
    
private:
    GLuint vao;
    glm::mat4 model_matrix;
    
};


#endif