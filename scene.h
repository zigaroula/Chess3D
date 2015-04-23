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
#include <string>
#include <map>


#define ZNEAR 10.0f
#define ZFAR 10000.0f
#define FOV 0.785f

class Scene
{
public:
    void initScene(int, int);
    size_t size() const { return vao_list.size(); }
    Vao& operator[](size_t index) { return vao_list[index]; }
    int addVaoPiece(std::string model, int team, glm::vec3 pos);
    
    std::vector<int> addVaoPieces(std::vector<std::string> model, std::vector<int> team, std::vector<glm::vec3> pos);

    void slideVAOTo(int vao, glm::vec3 newPos);
    void jumpVAOTo(int vao, glm::vec3 newPos);
    void ejectVAO(int vao);

    void deleteVAO(int vao);

    inline Light& getLight(int index) { return lights[index]; }
    size_t getLightCount() const { return lights.size(); }
    
    void setPerspective(int width, int height);
    inline GLfloat* getProjectionMatrixArray() { return glm::value_ptr(projection_matrix); }
    inline const glm::mat4& getProjectionMatrix() const { return projection_matrix; }
    inline const glm::mat4& getShadowProjectionMatrix() const { return shadow_projection_matrix; }
    inline const glm::mat4& getBiasMatrix() const { return bias_matrix; }

    inline int getShadowSize() const { return shadow_size; }

    inline const GLuint& getSkyBox(){ return skyBox;}
    const GLuint& getTexCube();
    void setSelectTex(int value) { selectTex = value; }
    const int getSelectTex() { return selectTex; }

    // CAMERA
    void setView();
    GLfloat *getNormalMatrixArray(unsigned int vao_index);
    inline GLfloat* getViewMatrixArray() { return glm::value_ptr(view_matrix); }
    
    inline const glm::mat4& getViewMatrix() const { return view_matrix; }
    
    Camera getCamera() { return camera; }
    void setCamFW(bool fw) { camera.setFW(fw); }
    void setCamBW(bool bw) { camera.setBW(bw); }
    void setCamLS(bool ls) { camera.setLS(ls); }
    void setCamRS(bool rs) { camera.setRS(rs); }
    void setCamZP(bool zp) { camera.setZP(zp); }
    void setCamZN(bool zn) { camera.setZN(zn); }
    void move(int);
    
    void selectModel(int index);
    void unselect();
    inline int getSelected() const { return selected_model; }
    inline bool selected() const { return vao_selected; }
    inline GLfloat* getSelectectionColor() { return glm::value_ptr(selection_color); }
    
private:
    void initShadow(int light_index);
    void initModels();
    void initLights();
    
    //Creation de la SkyBox
    ///Créer le cube sous la forme d'un vba
    void initSkyBox();
    GLuint loadCubemap(std::vector<const GLchar*> faces);
    ///Charge les faces de la SkyBox
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix, normal_matrix;
    Camera camera;
    glm::mat4 shadow_projection_matrix, bias_matrix;
    int shadow_size;
    std::vector<Light> lights;
    
    int selected_model;
    glm::vec3 selection_color;
    bool vao_selected = false;
    
    
    std::map<std::string, Vao> loadedModeles;

    GLuint skyBox;
    GLuint texCube;
    GLuint texCubeYellow;
    GLuint texCubeRed;
    int selectTex;
};


#endif
