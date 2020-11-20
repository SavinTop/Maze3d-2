#include "drawable.hpp"

void Drawable::draw(oglw::Shader& program) 
{
    updateModelMatrix();
    unsigned id = program.getUniformLocation("model");
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(this->model));
    this->__draw(program);
}

void Drawable::updateModelMatrix() 
{
    if(!changed) return;
    model = glm::mat4{1.0};
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), rotation);
    changed = false;
}

glm::mat4& Drawable::getModelMatrix() 
{
    return model;
}

void Drawable::setPosition(glm::vec3 position) 
{
    changed = true;
    this->position = position;
}

void Drawable::setRotation(float angle, glm::vec3 vector) 
{
    changed = true;
    rotation = vector;
    this->angle = angle;
}

void Drawable::setScale(glm::vec3 scale) 
{
    changed = true;
    this->scale = scale;
}

void Drawable::addPosition(glm::vec3 offset) 
{
    changed = true;
    this->position+=offset;
}

glm::vec3 Drawable::getPosition() 
{
    return position;
}

Drawable::Drawable() 
{
    model = glm::mat4(1.0);
    position = glm::vec3(0);
    rotation = glm::vec3(1);
    scale = glm::vec3(1);
    changed = true;
    angle = 0;
}
