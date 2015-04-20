#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <map>
#include <iostream>
#include "stb_image.h"

static const glm::vec3 color1(0.7f, 0.7f, 0.7f);
static const glm::vec3 color2(0.1f, 0.1f, 0.1f);

void Scene::selectModel(int index) {
    selected_model = index;
    vao_selected = true;
}

void Scene::unselected() {
    vao_selected = false;
}

void Scene::initScene(int width, int height)
{
    initShadow();
    initSkyBox();
    initModels();

    initLights();
    
    selection_color = glm::vec3(1.0, 1.0, 0.0);

    projection_matrix = glm::mat4(1.0f);
    camera = Camera(width, height);
}

void Scene::initLights()
{
    lights.push_back(Light(glm::vec3(400.f, 400.f, 400.f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f)));
}

void Scene::initShadow()
{
    shadow_size = 4096;
    
    // shadow map
    glGenTextures(1, &shadow_texture);
    glBindTexture(GL_TEXTURE_2D , shadow_texture);
    glTexImage2D(GL_TEXTURE_2D , 0, GL_DEPTH_COMPONENT,  shadow_size, shadow_size, 0, GL_DEPTH_COMPONENT , GL_FLOAT , NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D , 0);

    // shadow frame buffer

    glGenFramebuffers(1, &shadow_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER , shadow_buffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER , GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D , shadow_texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(FBOstatus != GL_FRAMEBUFFER_COMPLETE)
        printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");
    
    glBindFramebuffer(GL_FRAMEBUFFER , 0);
    
    shadow_projection_matrix = glm::perspective<float>(1.4f, 1.f, 20.f, 10000.f);
    
    bias_matrix = glm::mat4(
                         0.5, 0.0, 0.0, 0.0,
                         0.0, 0.5, 0.0, 0.0,
                         0.0, 0.0, 0.5, 0.0,
                         0.5, 0.5, 0.5, 1.0);
    
}

void Scene::initModels()
{
    //###########A COMMENTER SI INITIALISATION PAR LE MODULE DE JEU
    float x_shift = 76.f;
    
    float z_offset1 = 265.f;
    float z_offset2 = -z_offset1;
    
    float x_offset = -265.f;
    
    float pion1_z_translate = 80.f;
    
    glm::mat4 rotation_180(1.f);
    rotation_180 = glm::rotate(rotation_180, (float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    
    Vao roi1, roi2, dame1, dame2, tour11, tour12, tour21, tour22, cavalier11, cavalier12, cavalier21, cavalier22, fou11, fou12, fou21, fou22;
    
    Vao pion;
    
    roi1 = Vao::loadObj("models/roi.obj", color1);
    roi1.translate(glm::vec3(x_offset + 3*x_shift, 0.f, z_offset1));
    roi2 = Vao(roi1, color2);
    roi2.translate(glm::vec3(0.f, 0.f, z_offset2));

    dame1 = Vao::loadObj("models/dame.obj", color1);
    dame1.translate(glm::vec3(x_offset + 4*x_shift, 0.f, z_offset1));
    dame2 = Vao(dame1, color2);
    dame2.translate(glm::vec3(0.f, 0.f, z_offset2));
    
    tour11 = Vao::loadObj("models/tour.obj", color1);
    tour12 = Vao(tour11, color1);
    tour11.translate(glm::vec3(x_offset, 0.f, z_offset1));
    tour12.translate(glm::vec3(x_offset+7*x_shift, 0.f, z_offset1));
    tour21 = Vao(tour11, color2);
    tour22 = Vao(tour12, color2);
    tour21.translate(glm::vec3(0.f, 0.f, z_offset2));
    tour22.translate(glm::vec3(0.f, 0.f, z_offset2));
    
    fou11 = Vao::loadObj("models/fou.obj", color1);
    fou12 = Vao(fou11, color1);
    fou11.translate(glm::vec3(x_offset + 2*x_shift, 0.f, z_offset1));
    fou12.translate(glm::vec3(x_offset + 5*x_shift, 0.f, z_offset1));
    fou21 = Vao(fou11, color2);
    fou22 = Vao(fou12, color2);
    fou21.translate(glm::vec3(0.f, 0.f, 2*z_offset2));
    fou22.translate(glm::vec3(0.f, 0.f, 2*z_offset2));
    fou21.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    fou22.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    
    cavalier11 = Vao::loadObj("models/cavalier.obj", color1);
    cavalier12 = Vao(cavalier11, color1);
    cavalier11.translate(glm::vec3(x_offset + x_shift, 0.f, z_offset1));
    cavalier12.translate(glm::vec3(x_offset + 6*x_shift, 0.f, z_offset1));
    cavalier21 = Vao(cavalier11, color2);
    cavalier22 = Vao(cavalier12, color2);
    cavalier21.translate(glm::vec3(0.f, 0.f, 2*z_offset2));
    cavalier22.translate(glm::vec3(0.f, 0.f, 2*z_offset2));
    
    cavalier21.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    cavalier22.rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    tour21.translate(glm::vec3(0.f, 0.f, z_offset2));
    tour22.translate(glm::vec3(0.f, 0.f, z_offset2));
    roi2.translate(glm::vec3(0.f, 0.f, z_offset2));
    dame2.translate(glm::vec3(0.f, 0.f, z_offset2));
    
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

    
    pion = Vao::loadObj("models/pion.obj", color1);

    for (int i = 0; i < 8; ++i)
    {
        Vao pion_current(pion, color1);
        pion_current.translate(glm::vec3(x_offset + i*x_shift, 0.f, z_offset1 - pion1_z_translate));
        
        vao_list.push_back(pion_current);
        
        pion_current = Vao(pion, color2);
        pion_current.translate(glm::vec3(x_offset + i*x_shift, 0.f, z_offset2 + pion1_z_translate));
        
        vao_list.push_back(pion_current);
    }
    
    Vao plateau = Vao::loadObj("models/plane.obj", glm::vec3(0.f, 0.f, 0.f), "textures/board.tga");
    
    vao_list.push_back(plateau);
    
}

void Scene::setPerspective(int width, int height)
{
    projection_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective(FOV, (float)width/height, ZNEAR, ZFAR);
}

void Scene::setView() {
    view_matrix = glm::mat4 (1.0f);
    view_matrix = glm::lookAt(camera.getPosition(), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
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

void Scene::initSkyBox(){
    float points[] = {
      -100.0f,  100.0f, -100.0f,
      -100.0f, -100.0f, -100.0f,
       100.0f, -100.0f, -100.0f,
       100.0f, -100.0f, -100.0f,
       100.0f,  100.0f, -100.0f,
      -100.0f,  100.0f, -100.0f,

      -100.0f, -100.0f,  100.0f,
      -100.0f, -100.0f, -100.0f,
      -100.0f,  100.0f, -100.0f,
      -100.0f,  100.0f, -100.0f,
      -100.0f,  100.0f,  100.0f,
      -100.0f, -100.0f,  100.0f,

       100.0f, -100.0f, -100.0f,
       100.0f, -100.0f,  100.0f,
       100.0f,  100.0f,  100.0f,
       100.0f,  100.0f,  100.0f,
       100.0f,  100.0f, -100.0f,
       100.0f, -100.0f, -100.0f,

      -100.0f, -100.0f,  100.0f,
      -100.0f,  100.0f,  100.0f,
       100.0f,  100.0f,  100.0f,
       100.0f,  100.0f,  100.0f,
       100.0f, -100.0f,  100.0f,
      -100.0f, -100.0f,  100.0f,

      -100.0f,  100.0f, -100.0f,
       100.0f,  100.0f, -100.0f,
       100.0f,  100.0f,  100.0f,
       100.0f,  100.0f,  100.0f,
      -100.0f,  100.0f,  100.0f,
      -100.0f,  100.0f, -100.0f,

      -100.0f, -100.0f, -100.0f,
      -100.0f, -100.0f,  100.0f,
       100.0f, -100.0f, -100.0f,
       100.0f, -100.0f, -100.0f,
      -100.0f, -100.0f,  100.0f,
       100.0f, -100.0f,  100.0f
    };
    GLuint vbo;
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);

    glGenVertexArrays (1, &skyBox);
    glBindVertexArray (skyBox);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    std::string textName = "comawhite";

    std::string path = "textures/" + textName + "_";

    create_cube_map((path +"front.jpg").c_str(), (path +"back.jpg").c_str(), (path +"top.jpg").c_str(), (path +"bottom.jpg").c_str(), (path +"left.jpg").c_str(), (path +"right.jpg").c_str(), &texCube);
}

void Scene::create_cube_map (const char* front, const char* back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube ) {
  // generate a cube-map texture to hold all the sides
  glActiveTexture (GL_TEXTURE5);
  glGenTextures (1, tex_cube);

  // load each image and copy into a side of the cube-map texture
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front));
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back));
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top));
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom));
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left));
  assert (load_cube_map_side (*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right));

  // format cube map texture
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool Scene::load_cube_map_side (GLuint texture, GLenum side_target, const char* file_name) {
  glBindTexture (GL_TEXTURE_CUBE_MAP, texture);

  int x, y, n;
  int force_channels = 4;
  unsigned char*  image_data = stbi_load (
    file_name, &x, &y, &n, force_channels);
  if (!image_data) {
    fprintf (stderr, "ERROR: could not load %s\n", file_name);
    return false;
  }
  // non-power-of-2 dimensions check
  if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
    fprintf (
      stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name
    );
  }

  // copy image data into 'target' side of cube map
  glTexImage2D (
    side_target,
    0,
    GL_RGBA,
    x,
    y,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    image_data
  );
  free (image_data);
  return true;
}

int Scene::addVaoPiece(std::string model, int team, glm::vec3 pos){

    Vao piece ;
    if(team==1) {
        piece = Vao::loadObj(model, color1);
    }else{
        piece = Vao::loadObj(model, color2);
    }
    piece.translate(pos);
    vao_list.push_back(piece);
    return ((int)vao_list.size());

}

std::vector<int> Scene::addVaoPieces(std::vector<std::string> model, std::vector<int> team, std::vector<glm::vec3> pos){

    std::map<std::string, int> loadedModeles;
    std::vector<int> indices;

    for (int i = 0 ; i < (int) model.size() ; i++){
        Vao piece;
        std::map<std::string, int>::iterator it = loadedModeles.find(model[i]);
        if(it ==loadedModeles.end() ){
            if(team[i]==1) {
                piece = Vao::loadObj(model[i],color1);
            }else{
                piece = Vao::loadObj(model[i],color2);
            }
            loadedModeles[model[i]] = vao_list.size();
        }else{
            if(team[i]==1) {
                piece = Vao(vao_list[it->second], color1);
            }else{
                piece = Vao(vao_list[it->second], color2);
            }
        }
        piece.translate(pos[i]);
        vao_list.push_back(piece);
        indices.push_back((int) vao_list.size());
    }

    return indices;

}


void Scene::slideVAOTo(int vao, glm::vec3 newPos){

}
