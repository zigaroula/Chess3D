#ifndef LIGHT_H
#define LIGHT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#define __gl_h_
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


/**
 * \class Light
 * \brief Classe qui représente une lumière (position, couleur diffuse et spéculaire)
 */
class Light
{
public:
    ///Constructeur vide qui crée une lumière par défaut.
    Light();
    Light(glm::vec3 pos, glm::vec3 dcolor, glm::vec3 scolor) : lightPos(pos), diffuseColor(dcolor), specColor(scolor) { view_matrix = glm::lookAt(pos, glm::vec3(0,0,0), glm::vec3(0,1,0));}

    inline const glm::vec3& getPos() const{ return lightPos;}
    inline const glm::vec3& getDiffuseColor() const{ return diffuseColor;}
    inline const glm::vec3& getSpecColor() const{ return specColor;}

    inline void setPos(glm::vec3 pos){ lightPos = pos;}
    inline void setDiffuseColor(glm::vec3 c){ diffuseColor = c;}
    inline void setSpecColor(glm::vec3 c){ specColor= c;}
    
    inline const glm::mat4& getViewMatrix() const { return view_matrix; }
    
    inline GLuint& getShadowTextureId() { return shadow_texture; }
    inline GLuint& getShadowBufferId() { return shadow_buffer; }
    

private:
    glm::vec3 lightPos;
    glm::vec3 diffuseColor;
    glm::vec3 specColor;
    
    glm::mat4 view_matrix;
    
    GLuint shadow_texture = 0, shadow_buffer = 0;
};

#endif // LIGHT_H
