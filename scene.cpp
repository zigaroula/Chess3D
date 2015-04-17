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
    vao_list.push_back(Vao::loadObj("models/sphere2.obj", glm::vec3(0.5f, 0.f, 0.f)));
    
    camera = Camera(width, height);
    //Ajout de la lumiere par défaut à la scène
    addLight(Light());

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
