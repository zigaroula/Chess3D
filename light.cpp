#include "light.h"

Light::Light()
{
    lightPos = glm::vec3(100.0,-100.0,0.0);
    diffuseColor = glm::vec3(0.5, 0.5, 0.5);
    specColor = glm::vec3(1.0, 1.0, 1.0);

}
