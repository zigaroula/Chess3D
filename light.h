#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>

/**
 * \class Light
 * \brief Classe qui représente une lumière (position, couleur diffuse et spéculaire)
 */
class Light
{
public:
    ///Constructeur vide qui crée une lumière par défaut.
    Light();
    Light(glm::vec3 pos, glm::vec3 dcolor, glm::vec3 scolor) : lightPos(pos), diffuseColor(dcolor), specColor(scolor){}

    inline glm::vec3 getPos() const{ return lightPos;}
    inline glm::vec3 getDiffuseColor() const{ return diffuseColor;}
    inline glm::vec3 getSpecColor() const{ return specColor;}

    inline void setPos(glm::vec3 pos){ lightPos = pos;}
    inline void setDiffuseColor(glm::vec3 c){ diffuseColor = c;}
    inline void setSpecColor(glm::vec3 c){ specColor= c;}

private:
    glm::vec3 lightPos;
    glm::vec3 diffuseColor;
    glm::vec3 specColor;
};

#endif // LIGHT_H
