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

#define ZNEAR 0.1f
#define ZFAR 100.f
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

    // CAMERA
    void setView();
    GLfloat *getNormalMatrixArray(unsigned int vao_index);
    GLfloat* getViewMatrixArray() { return glm::value_ptr(view_matrix); }
    Camera getCamera() { return camera; }
    void setCamFW(bool fw) { camera.holdingForward = fw; }
    void setCamBW(bool bw) { camera.holdingBackward = bw; }
    void setCamLS(bool ls) { camera.holdingLeftStrafe = ls; }
    void setCamRS(bool rs) { camera.holdingRightStrafe = rs; }
    void setCamZP(bool zp) { camera.holdingZoomPositive = zp; }
    void setCamZN(bool zn) { camera.holdingZoomNegative = zn; }
    void move(int);

private:
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix;
    Camera camera;

};


#endif
