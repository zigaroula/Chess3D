#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include <iostream>

Scene::Scene() {

}

void Scene::initScene(int width, int height)
{
    projection_matrix = glm::mat4(1.0f);
    
    glm::vec3 color1(0.5f, 0.f, 0.f);
    glm::vec3 color2(0.0f, 0.5f, 0.f);
    float x_shift = 80.f;
    float z_shift = -300.f;
    float dame_y_translate = -12.5f;
    float fou_y_translate = -43.f;
    float cavalier_y_translate = -33.f;
    float tour_y_translate = -45.f;
    float pion_y_translate = -60.f;
    
    float pion1_z_translate = -80.f;
    
    glm::mat4 rotation_180(1.f);
    rotation_180 = glm::rotate(rotation_180, (float)M_PI, glm::vec3(0.f, 1.f, 0.f));

    Vao roi1, roi2, dame1, dame2, tour11, tour12, tour21, tour22, cavalier11, cavalier12, cavalier21, cavalier22, fou11, fou12, fou21, fou22;
    
    Vao pion = Vao::loadObj("models/pion.obj", color1);
    
    roi1 = Vao::loadObj("models/roi.obj", color1);
    roi1.translate(glm::vec3(-1*x_shift, 0.f, 0.f));
    roi2 = Vao(roi1, color2);
    
    dame1 = Vao::loadObj("models/dame.obj", color1);
    dame1.translate(glm::vec3(0.f, dame_y_translate, 0.f));
    dame2 = Vao(dame1, color2);
    
    pion = Vao::loadObj("models/pion.obj", color1);
    tour11 = Vao::loadObj("models/tour.obj", color1);
    tour12 = Vao(tour11, color1);
    tour11.translate(glm::vec3(-4*x_shift, tour_y_translate, 0.f));
    tour12.translate(glm::vec3(3*x_shift, tour_y_translate, 0.f));
    tour21 = Vao(tour11, color2);
    tour22 = Vao(tour12, color2);
    
    fou11 = Vao::loadObj("models/fou.obj", color1);
    fou12 = Vao(fou11, color1);
    fou11.translate(glm::vec3(-2*x_shift, fou_y_translate, 0.f));
    fou12.translate(glm::vec3(1*x_shift, fou_y_translate, 0.f));
    fou21 = Vao(fou11, color2);
    fou22 = Vao(fou12, color2);
    fou21.translate(glm::vec3(0.f, 0.f, z_shift));
    fou22.translate(glm::vec3(0.f, 0.f, z_shift));
    fou21.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    fou22.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    
    cavalier11 = Vao::loadObj("models/cavalier.obj", color1);
    cavalier12 = Vao(cavalier11, color1);
    cavalier11.translate(glm::vec3(-3*x_shift, cavalier_y_translate, 0.f));
    cavalier12.translate(glm::vec3(2*x_shift, cavalier_y_translate, 0.f));
    cavalier21 = Vao(cavalier11, color2);
    cavalier22 = Vao(cavalier12, color2);
    cavalier21.translate(glm::vec3(0.f, 0.f, z_shift));
    cavalier22.translate(glm::vec3(0.f, 0.f, z_shift));
    
    cavalier21.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    cavalier22.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    tour21.translate(glm::vec3(0.f, 0.f, z_shift));
    tour22.translate(glm::vec3(0.f, 0.f, z_shift));
    roi2.translate(glm::vec3(0.f, 0.f, z_shift));
    dame2.translate(glm::vec3(0.f, 0.f, z_shift));
    
    vao_list.push_back(roi1);
    vao_list.push_back(dame1);
    vao_list.push_back(roi2);
    vao_list.push_back(dame2);
    vao_list.push_back(tour11);
    vao_list.push_back(tour12);
    vao_list.push_back(tour21);
    vao_list.push_back(tour22);
    vao_list.push_back(cavalier11);
    vao_list.push_back(cavalier12);
    vao_list.push_back(cavalier21);
    vao_list.push_back(cavalier22);
    vao_list.push_back(fou11);
    vao_list.push_back(fou12);
    vao_list.push_back(fou21);
    vao_list.push_back(fou22);
    
    for (int i = 0; i < 8; ++i)
    {
        int shift = i - 4;
        Vao pion_current(pion, color1);
        pion_current.translate(glm::vec3(shift*x_shift, pion_y_translate, pion1_z_translate));
        
        vao_list.push_back(pion_current);
        
        pion_current = Vao(pion, color2);
        pion_current.translate(glm::vec3(shift*x_shift, pion_y_translate, z_shift - pion1_z_translate));
        
        vao_list.push_back(pion_current);
    }
    
    Vao plateau = Vao::loadObj("models/plane.obj", glm::vec3(0.f, 0.f, 0.5f));
    plateau.translate(glm::vec3(0.f, -100.f, 0.f));
    
    vao_list.push_back(plateau);

    camera = Camera(width, height);
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
