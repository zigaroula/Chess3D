#ifndef __vao_h_
#define __vao_h_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <cmath>

class Vao
{
public:
    Vao() { }
    Vao(const Vao& vao, const glm::vec3& color) { id = vao.id; vertex_count = vao.vertex_count; diffuse_color = color; texture_enabled = vao.texture_enabled;}
    GLuint getId() const { return id; }
    GLsizei getVertexCount() const { return vertex_count; }
    
    const GLfloat* getModelMatrixArray() const { return glm::value_ptr(model_matrix); }
    const GLfloat* getDiffuseColorArray() const { return glm::value_ptr(diffuse_color); }
    const glm::mat4& getModelMatrix() const { return model_matrix; }
    
    static Vao getCube();
    ///Créer le cube englobant la scène sur lequel sera peint le "ciel"
    static Vao getSkyBoxCube();
    
    static Vao loadObj(std::string, glm::vec3);
    static Vao loadObj(std::string, glm::vec3, std::string);

    
    void translate(const glm::vec3& vector);
    void rotate(float angle, const glm::vec3 &vector);
    void scale(const glm::vec3 &vector);
    
    bool isTextureEnabled() const { return texture_enabled; }
    GLuint getTextureId() const { return texture_id; }
    
    void requestMovement(glm::vec3 pos_end);
    void requestJumpMovement(glm::vec3 pos_end);
    void requestEjectMovement();
    inline bool isMovementRequested() const { return movement_requested; }
    inline bool isJumpMovementRequested() const { return jump_movement_requested; }
    inline bool isEjectMovementRequested() const { return eject_movement_requested; }
    inline const glm::vec3& getMovementDirection() const { return movement_direction; }
    inline double getMovementStartTime() const { return movement_start_time; }
    inline float getMovementLength() const { return movement_length; }
    void updateMovement();
    void endMovement();
    
    inline bool isRotated90() { return rotated; }
    
    void rotate90() { rotate(M_PI, glm::vec3(0.f, 1.f, 0.f));  rotated = true;}

private:
    GLuint id;
    GLuint texture_id = 0;
    GLsizei vertex_count;
    glm::mat4 model_matrix;
    glm::vec3 diffuse_color;
    GLboolean texture_enabled;
    
    bool movement_requested = false;
    bool jump_movement_requested = false;
    bool eject_movement_requested = false;
    float a,b ; //variables utiles au calcul du saut
    float movement_length;
    glm::vec3 position_start, position_end, movement_direction;
    double movement_start_time;
    glm::mat4 model_matrix_before_movement;
    bool rotated = false;
    //bool visible = true;

};


#endif
