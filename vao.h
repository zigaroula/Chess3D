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

#include <iostream>

class Vao
{
public:
    Vao() { }
    Vao(const Vao& vao, const glm::vec3& color) { id = vao.id; model_matrix = vao.model_matrix; vertex_count = vao.vertex_count; ambient_color = color; texture_enabled = vao.texture_enabled;}
    GLuint getId() const { return id; }
    GLsizei getVertexCount() const { return vertex_count; }
    
    const GLfloat* getModelMatrixArray() const { return glm::value_ptr(model_matrix); }
    const GLfloat* getAmbientColorArray() const { return glm::value_ptr(ambient_color); }
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
    
    inline bool isMovementRequested() const { return movement_requested; }
    inline const glm::vec3& getMovementDirection() const { return movement_direction; }
    inline double getMovementStartTime() const { return movement_start_time; }
    inline float getMovementLength() const { return movement_length; }
    void updateMovement();
    void endMovement();

private:
    GLuint id;
    GLuint texture_id = 0;
    GLsizei vertex_count;
    glm::mat4 model_matrix;
    glm::vec3 ambient_color;
    GLboolean texture_enabled;
    
    bool movement_requested = false;
    float movement_length;
    glm::vec3 position_start, position_end, movement_direction;
    double movement_start_time;
    glm::mat4 model_matrix_before_movement;
    

};


#endif
