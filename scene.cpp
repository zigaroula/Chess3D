#include "scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <map>
#include <iostream>
#include "stb_image.h"

static const glm::vec3 color1(1.0f, 1.0f, 1.0f);
static const glm::vec3 color2(0.2f, 0.2f, 0.2f);

void Scene::selectModel(int index) {
    selected_model = index;
    vao_selected = true;
}

void Scene::unselect() {
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
    
    shadow_view_matrix = glm::lookAt(lights[0].getPos(), glm::vec3(0,0,0), glm::vec3(0,1,0));
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
    
    glm::mat4 rotation_180(1.f);
    rotation_180 = glm::rotate(rotation_180, (float)M_PI, glm::vec3(0.f, 1.f, 0.f));
    
    
    
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

    ///Créer un vao, l'ajoute à la liste des vao et retourne son index dans la liste

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

    ///Créer une liste de vao sans avoir à recharger plusieurs fois le meme modèle

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
            loadedModeles[model[i]] = (int)vao_list.size();
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

    vao_list[vao].requestMovement(newPos);
}
