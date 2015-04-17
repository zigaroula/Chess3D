#ifndef __scene_h_
#define __scene_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#include "camera.h"
#include "vao.h"
#include "light.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define ZNEAR 100.0f
#define ZFAR 1000.0f
#define FOV 0.785f

class Scene
{
public:
    Scene();
    void initScene(int, int);
    size_t size() const { return vao_list.size(); }
    const Vao& operator[](size_t index) const { return vao_list[index]; }

    void setPerspective(int width, int height);
    GLfloat* getProjectionMatrixArray() { return glm::value_ptr(projection_matrix); }
    glm::mat4 getProjectionMatrix() { return projection_matrix;}
    GLuint getShadowBufferId() { return shadow_buffer; }

    // CAMERA
    void setView();
    GLfloat *getNormalMatrixArray(unsigned int vao_index);
    GLfloat* getViewMatrixArray() { return glm::value_ptr(view_matrix); }
    Camera getCamera() { return camera; }
    void setCamFW(bool fw) { camera.setFW(fw); }
    void setCamBW(bool bw) { camera.setBW(bw); }
    void setCamLS(bool ls) { camera.setLS(ls); }
    void setCamRS(bool rs) { camera.setRS(rs); }
    void setCamZP(bool zp) { camera.setZP(zp); }
    void setCamZN(bool zn) { camera.setZN(zn); }
    void move(int);

    // LUMIERE
    inline Light getLight(size_t index) const{return light_list[index];}
    inline void setLight(size_t index, Light light){light_list[index] = light;}
    inline void addLight( Light light){light_list.push_back(light);}

private:
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix, normal_matrix;
    Camera camera;
    std::vector<Light> light_list;
    GLuint shadow_texture, shadow_buffer;
    
    void initShadow();

};


#endif
