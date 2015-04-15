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
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Scene
{
public:
    Scene();
    void initScene();
    size_t size() const { return vao_list.size(); }
    const Vao& operator[](size_t index) const { return vao_list[index]; }
    
    void setPerspective(int width, int height);
    GLfloat* getProjectionMatrixArray() { return glm::value_ptr(projection_matrix); }
    
private:
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix;
    
    static constexpr float zNear = 0.1f;
    static constexpr float zFar = 100.f;
    static constexpr float fov = 0.785f;
    
    
};


#endif