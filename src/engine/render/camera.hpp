#pragma once 

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90, float pitch = 0);

glm::mat4 getViewMatrix();

void moveStraight(float coof);
void moveSideways(float coof);

void addRotation(float yaw, float pitch, bool constrainPitch = true);
void setRotation(float yaw, float pitch);
void setPos(glm::vec3 position);
void setFront(glm::vec3 front);
glm::vec3 getPos(){return position;}
glm::vec3 getFront(){return front;}

bool fixed_z = true;

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