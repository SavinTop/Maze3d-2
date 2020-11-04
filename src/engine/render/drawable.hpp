#pragma once 

#include "baseTypes/resources/internal/OGL/shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Drawable{
public:
    void draw(res::ogl::ShaderProgram& program);

    virtual void __draw(res::ogl::ShaderProgram& program){};
    void updateModelMatrix();
    glm::mat4& getModelMatrix();

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);

    void addPosition(glm::vec3 offset);
    void addRotation(glm::vec3 rotation);
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 model;
    bool changed = true;
};