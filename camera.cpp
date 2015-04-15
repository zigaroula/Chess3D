#include "camera.h"

const float Camera::TO_RADS = 3.141592654 / 180.0;

Camera::Camera(float _windowWidth, float _windowHeight) {
    initCamera();

    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    windowMidX = windowWidth / 2.0f;
    windowMidY = windowHeight / 2.0f;

    glfwSetMousePos(windowMidX, windowMidY); // a voir
}

Camera::~Camera() {

}

void Camera::initCamera() {
    position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    speed = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

    movementSpeedFactor = 100.0;

    pitchSensitivity = 0.2;
    yawSensitivity = 0.2;

    holdingForward = false;
    holdingBackward = false;
    holdingLeftStrafe = false;
    holdingRightStrafe = false;
}

const float Camera::toRads(const float & _angleInDegrees) const {
    return _angleInDegrees * TO_RADS;
}

void Camera::handleMouseMove(int mouseX, int mouseY) {
    float horizMovement = (mouseX - windowMidX+1) * yawSensitivity;
    float vertMovement = (mouseY - windowMidY) * pitchSensitivity;

    rotation[0] += vertMovement;
    rotation[1] += horizMovement;

    if (rotation[0] < -90) {
        rotation[0] = -90;
    }

    if (rotation[0] > 90) {
        rotation[0] = 90;
    }

    if (rotation[1] < 0) {
        rotation[1] += 360;
    }

    if (rotation[1] > 360) {
        rotation[1] -= 360;
    }

    glfwSetMousePos(windowMidX, windowMidY); // a voir
}

void Camera::move() {
    glm::vec4 movement;

    float sinXRot = sin(toRads(rotation[0]));
    float cosXRot = cos(toRads(rotation[0]));

    float sinYRot = sin(toRads(rotation[1]));
    float cosYRot = cos(toRads(rotation[1]));

    float pitchLimitFactor = cosXRot;

    if (holdingForward) {
        movement[0] += sinYRot * pitchLimitFactor;
        movement[1] += -sinXRot;
        movement[2] += -cosYRot * pitchLimitFactor;
    }

    if (holdingBackward) {
        movement[0] += -sinYRot * pitchLimitFactor;
        movement[1] += sinXRot;
        movement[2] += -cosYRot * pitchLimitFactor;
    }

    if (holdingLeftStrafe) {
        movement[0] += -cosYRot;
        movement[2] += -sinYRot;
    }

    if (holdingRightStrafe) {
        movement[0] += cosYRot;
        movement[2] += sinYRot;
    }

    float norm = sqrt(movement[0]*movement[0] + movement[1]*movement[1] + movement[2]*movement[2]);
    movement[0] = movement[0]/norm;
    movement[1] = movement[1]/norm;
    movement[2] = movement[2]/norm;

    position += movement;
}
