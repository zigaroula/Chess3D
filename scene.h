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


#define ZNEAR 10.0f
#define ZFAR 10000.0f
#define FOV 0.785f

class Scene
{
public:
    void initScene(int, int);
    size_t size() const { return vao_list.size(); }
    Vao& operator[](size_t index) { return vao_list[index]; }
    ///Créer un vao, l'ajoute à la liste des vao et retourne son index dans la liste
    int addVaoPiece(std::string model, int team, glm::vec3 pos);
    ///Créer une liste de vao sans avoir à recharger plusieurs fois le meme modèle
    std::vector<int> addVaoPieces(std::vector<std::string> model, std::vector<int> team, std::vector<glm::vec3> pos);

    void slideVAOTo(int vao, glm::vec3 newPos);

    const Light& getLight(int index) const { return lights[index]; }
    size_t getLightCount() const { return lights.size(); }
    
    void setPerspective(int width, int height);
    GLfloat* getProjectionMatrixArray() { return glm::value_ptr(projection_matrix); }
    const glm::mat4& getProjectionMatrix() const { return projection_matrix; }
    const glm::mat4& getShadowProjectionMatrix() const { return shadow_projection_matrix; }
    const glm::mat4& getBiasMatrix() const { return bias_matrix; }

    GLuint getShadowBufferId() { return shadow_buffer; }
    GLuint getShadowTexureId() { return shadow_texture; }
    int getShadowSize() const { return shadow_size; }

    const GLuint& getSkyBox(){ return skyBox;}
    const GLuint& getTexCube() { return texCube; }


    // CAMERA
    void setView();
    GLfloat *getNormalMatrixArray(unsigned int vao_index);
    GLfloat* getViewMatrixArray() { return glm::value_ptr(view_matrix); }
    
    const glm::mat4& getViewMatrix() const { return view_matrix; }
    
    Camera getCamera() { return camera; }
    void setCamFW(bool fw) { camera.setFW(fw); }
    void setCamBW(bool bw) { camera.setBW(bw); }
    void setCamLS(bool ls) { camera.setLS(ls); }
    void setCamRS(bool rs) { camera.setRS(rs); }
    void setCamZP(bool zp) { camera.setZP(zp); }
    void setCamZN(bool zn) { camera.setZN(zn); }
    void move(int);
    
    void selectModel(int index);
    void unselected();
    inline int getSelected() const { return selected_model; }
    inline bool selected() const { return vao_selected; }
    inline GLfloat* getSelectectionColor() { return glm::value_ptr(selection_color); }
    
private:
    void initShadow();
    void initModels();
    void initLights();
    
    //Creation de la SkyBox
    ///Créer le cube sous la forme d'un vba
    void initSkyBox();
    void create_cube_map (const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube );
    ///Charge les faces de la SkyBox
    bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);
    std::vector<Vao> vao_list;
    glm::mat4 view_matrix, projection_matrix, normal_matrix;
    Camera camera;
    GLuint shadow_texture, shadow_buffer;
    glm::mat4 shadow_projection_matrix, bias_matrix;
    int shadow_size;
    std::vector<Light> lights;
    
    int selected_model;
    glm::vec3 selection_color;
    bool vao_selected = false;
    

    GLuint skyBox;
    GLuint texCube;
};


#endif
