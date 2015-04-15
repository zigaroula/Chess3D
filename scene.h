#ifndef __scene_h_
#define __scene_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#include "vao.h"
#include <glm/glm.hpp>
#include <vector>

class Scene
{
public:
    Scene();
    void initScene();
    size_t size() const { return vao_list.size(); }
    const Vao& operator[](size_t index) const { return vao_list[index]; }
    
private:
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix;
    
};


#endif