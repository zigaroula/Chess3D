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
    GLuint getId() const { return id; }
    GLsizei getVertexCount() const { return vertex_count; }
    const GLfloat* getModelMatrixArray() const { return glm::value_ptr(model_matrix); }
    const glm::mat4 getModelMatrix() const { return model_matrix; }
    static Vao getCube();
    static Vao loadObj(std::string, glm::vec3);
    
    void translate(const glm::vec3& vector);
    void rotate(float angle, const glm::vec3 &vector);
    void scale(const glm::vec3 &vector);

    void setModelMatrix(glm::mat4 modelMatrix) { model_matrix = modelMatrix; }

private:
    GLuint id;
    GLsizei vertex_count;
    glm::mat4 model_matrix;

};


#endif
