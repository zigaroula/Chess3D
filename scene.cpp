#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

Scene::Scene()
{

}

void Scene::initScene()
{
    projection_matrix = glm::mat4(0.5f);
    vao_list.push_back(Vao::getCube());
    
    Vao::loadObj("models/cube2.obj");
}

void Scene::setPerspective(int width, int height)
{
    projection_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective(FOV, (float)width/height, ZNEAR, ZFAR);
}
