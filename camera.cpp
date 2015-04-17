#include "camera.h"

const float Camera::TO_RADS = 3.141592654 / 180.0;

Camera::Camera() {

}

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
    position = glm::vec3(0.f, 200.f, 0.f);
    direction = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    speed = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    movementSpeedFactor = 100.0;
    glm::vec3 initialPosition = cartesian2Polar(position);
    angleH = initialPosition[0];
    angleV = initialPosition[1];
    distance = initialPosition[2];

    pitchSensitivity = 0.2;
    yawSensitivity = 0.2;

    holdingForward = false;
    holdingBackward = false;
    holdingLeftStrafe = false;
    holdingRightStrafe = false;
    holdingZoomNegative = false;
    holdingZoomPositive = false;
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

glm::vec3 Camera::polar2Cartesian (float phi, float theta, float d) {
    glm::vec3 tmpPosition;
    tmpPosition[0] = d*sin (theta) * cos (phi);
    tmpPosition[1] = d*cos (theta);
    tmpPosition[2] = d*sin (theta) * sin (phi);
    return tmpPosition;
}

glm::vec3 Camera::cartesian2Polar(glm::vec3 initPos) {
    float x = initPos[0];
    float y = initPos[1];
    float z = initPos[2];
    float phi = atan(y/x);
    float r = sqrt(x*x + y*y + z*z);
    float theta = acos(z/r);
    glm::vec3 tmpPosition = glm::vec3(phi, theta, r);
    return tmpPosition;
}

void Camera::move(int fps) {
    //std::cout << angleH << " " << angleV << " " << distance << std::endl;
    if (holdingForward) {
        angleV -= toRads(90) / fps;
        if (angleV < toRads(0.001)) {
            angleV = toRads(0.001);
        }
    }
    if (holdingBackward) {
        angleV += toRads(90) / fps;
        if (angleV > toRads(179.999)) {
            angleV = toRads(179.999);
        }
    }
    if (holdingLeftStrafe) {
        angleH += toRads(90) / fps;
        if (angleH > toRads(360)) {
            angleH = toRads(0);
        }
    }
    if (holdingRightStrafe) {
        angleH -= toRads(90) / fps;
        if (angleH < toRads(0)) {
            angleH = toRads(360);
        }
    }
    if (holdingZoomNegative) {
        distance += (float)200/fps;
    }
    if (holdingZoomPositive) {
        distance -= (float)200/fps;
        if (distance <0.001) {
            distance += (float)200/fps;
        }
    }
    position = polar2Cartesian(angleH, angleV, distance);
}
