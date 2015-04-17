#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>



Scene::Scene() {

}

void Scene::initScene(int width, int height)
{
    projection_matrix = glm::mat4(0.5f);
    //vao_list.push_back(Vao::getCube());
    vao_list.push_back(Vao::loadObj("models/cavalier.obj", glm::vec3(0.5f, 0.f, 0.f)));
    
    camera = Camera(width, height);
    //Ajout de la lumiere par défaut à la scène
    addLight(Light());

    initShadow();
    

}

void Scene::initShadow()
{
    int SHADOWSIZE = 512;
    
    glGenTextures(1, &shadow_texture);
    glBindTexture(GL_TEXTURE_2D , shadow_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D , 0, GL_DEPTH_COMPONENT,  SHADOWSIZE , SHADOWSIZE , 0, GL_DEPTH_COMPONENT , GL_FLOAT , NULL);
    
    glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_COMPARE_MODE , GL_COMPARE_REF_TO_TEXTURE);
    glBindTexture(GL_TEXTURE_2D , 0);
    
    glGenFramebuffers(1, &shadow_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER , shadow_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D , shadow_texture, 0);
    glDrawBuffer(GL_NONE);
    
    glBindFramebuffer(GL_FRAMEBUFFER , 0);
    
    
    
}

void Scene::setPerspective(int width, int height)
{
    projection_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective(FOV, (float)width/height, ZNEAR, ZFAR);
}

void Scene::setView() {
    view_matrix = glm::mat4 (1.0f);
    view_matrix = glm::lookAt(camera.getPosition(), glm::vec3(0.f, 0.f, -10.f), glm::vec3(0.f, 1.f, 0.f));
}

void Scene::move(int fps) {
    camera.move(fps);
}

GLfloat* Scene::getNormalMatrixArray(unsigned int vao_index)
{
    const glm::mat4 &model_matrix = vao_list[vao_index].getModelMatrix();
    //(1.0f);
    
    normal_matrix = glm::transpose(glm::inverse(view_matrix * model_matrix));
    
    return glm::value_ptr(normal_matrix);
}
