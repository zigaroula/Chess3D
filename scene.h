#ifndef __scene_h_
#define __scene_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/gl3.h>
#endif

#include <glm/glm.hpp>

class Scene
{
public:
    Scene();
    
    
private:
    GLuint shader_program;
    glm::mat4 view_matrix, projection_matrix;
    
};


#endif