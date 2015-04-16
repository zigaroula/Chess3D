#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    static const float TO_RADS;

    bool holdingForward;
    bool holdingBackward;
    bool holdingLeftStrafe;
    bool holdingRightStrafe;

    Camera();
    Camera(float, float);
    ~Camera();

    void handleMouseMove(int, int);
    const float toRads(const float &) const;
    void move(int);

    float getPitchSensitivity() { return pitchSensitivity; }
    void setPitchSensitivity(float value) { pitchSensitivity = value; }
    float getYawSensitivity() { return yawSensitivity; }
    void setYawSensitivity(float value) { yawSensitivity = value; }

    glm::vec3 getPosition() const { return position; }
    float getXPos() const { return position[0]; }
    float getYPos() const { return position[1]; }
    float getZPos() const { return position[2]; }

    glm::vec4 getRotation() const { return rotation; }
    float getXRot() const { return rotation[0]; }
    float getYRot() const { return rotation[1]; }
    float getZRot() const { return rotation[2]; }

    glm::vec3 getDirection() const { return direction; }
    void setDirection(glm::vec3 _direction) { direction = _direction; }


private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec4 rotation;
    glm::vec4 speed;

    float movementSpeedFactor;
    float pitchSensitivity;
    float yawSensitivity;

    int windowWidth;
    int windowHeight;
    int windowMidX;
    int windowMidY;

    void initCamera();
};

#endif // CAMERA_H
 // see http://r3dux.org/2012/12/a-c-camera-class-for-simple-opengl-fps-controls/
