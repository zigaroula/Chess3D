#include "camera.h"

const float Camera::TO_RADS = 3.141592654 / 180.0;

Camera::Camera(float _windowWidth, float _windowHeight) {
    initCamera();

    windowWidth = _windowWidth;
    windowHeight = _windowHeight;

    windowMidX = windowWidth / 2.0f;
    windowMidY = windowHeight / 2.0f;

   // glfwSetMousePos(windowMidX, windowMidY); // a voir
}

Camera::~Camera() {

}

void Camera::initCamera() {
    position = glm::vec3(2.f, 1.f, 3.f);
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
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

   // glfwSetMousePos(windowMidX, windowMidY); // a voir
}

void Camera::move() {
    if (holdingForward) {
        position[0] -= 0.0001*fabs(position[0]-direction[0]) + 0.0001;
        position[1] -= 0.0001*fabs(position[1]-direction[1]) + 0.0001;
        position[2] -= 0.0001*fabs(position[2]-direction[2]) + 0.0001;
    }
    if (holdingBackward) {
        position[0] += 0.0001*fabs(position[0]-direction[0]) + 0.0001;
        position[1] += 0.0001*(position[1]-direction[1]) + 0.0001;
        position[2] += 0.0001*(position[2]-direction[2]) + 0.0001;
    }
    if (holdingLeftStrafe) {
        position[0] -= 0.0001*fabs(position[0]-direction[0]) + 0.0001;
    }

    if (holdingRightStrafe) {
        position[0] += 0.0001*fabs(position[0]-direction[0]) + 0.0001;
    }
}
