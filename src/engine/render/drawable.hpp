#pragma once 

#include "baseTypes/resources/internal/OGL/shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "baseTypes/oglWrappers/oglw.h"

class Drawable{
public:
    Drawable();
    void draw(oglw::Shader& program);

    virtual void __draw(oglw::Shader& program){};
    void updateModelMatrix();
    glm::mat4& getModelMatrix();

    void setPosition(glm::vec3 position);
    void setRotation(float angle, glm::vec3 vector);
    void setScale(glm::vec3 scale);

    void addPosition(glm::vec3 offset);
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 model;
    float angle;
    bool changed;
};