#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{

Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90, float pitch = 0);

glm::mat4 getViewMatrix();

void moveStraight(float coof);
void moveSideways(float coof);

void addRotation(float yaw, float pitch, bool constrainPitch = true);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float Yaw;
    float Pitch;

    void updateCameraVectors();
};