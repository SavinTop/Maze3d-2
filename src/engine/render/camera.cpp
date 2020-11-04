#include "camera.hpp"


glm::mat4 Camera::getViewMatrix() 
{
    return glm::lookAt(position, position + front, up);
}

void Camera::moveStraight(float coof) 
{
    this->position += this->front*coof;
}

void Camera::moveSideways(float coof) 
{
    this->position += this->right*coof;
}

void Camera::addRotation(float yaw, float pitch, bool constrainPitch) 
{
        Yaw   += yaw;
        Pitch += pitch;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
}

void Camera::updateCameraVectors() 
{
    glm::vec3 _front;
    _front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    _front.y = sin(glm::radians(this->Pitch));
    _front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->front = glm::normalize(_front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
{
    this->position = position;
    this->worldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    updateCameraVectors();
}
