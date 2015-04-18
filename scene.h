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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define ZNEAR 10.0f
#define ZFAR 10000.0f
#define FOV 0.785f

class Scene
{
public:
    void initScene(int, int);
    size_t size() const { return vao_list.size(); }
    const Vao& operator[](size_t index) const { return vao_list[index]; }

    void setPerspective(int width, int height);
    GLfloat* getProjectionMatrixArray() { return glm::value_ptr(projection_matrix); }
    const glm::mat4& getProjectionMatrix() const { return projection_matrix; }
    const glm::mat4& getShadowProjectionMatrix() const { return shadow_projection_matrix; }
    const glm::mat4& getBiasMatrix() const { return bias_matrix; }

    GLuint getShadowBufferId() { return shadow_buffer; }
    GLuint getShadowTexureId() { return shadow_texture; }
    int getShadowSize() const { return shadow_size; }

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
    
private:
    void initShadow();
    void initModels();
    void initSkyBox();
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix, normal_matrix;
    Camera camera;
    GLuint shadow_texture, shadow_buffer;
    glm::mat4 shadow_projection_matrix, bias_matrix;
    int shadow_size;

};


#endif
