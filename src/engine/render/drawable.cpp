#include "drawable.hpp"

void Drawable::draw(res::ogl::ShaderProgram& program) 
{
    updateModelMatrix();
    unsigned id = program.getUniformLocation("model");
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(this->model));
    this->__draw(program);
}

void Drawable::updateModelMatrix() 
{
    if(!changed) return;
    model = glm::mat4(1);
    model = glm::scale(model, this->scale);
    model = glm::rotate(model, 1.0f, rotation);
    model = glm::translate(model, position);
}

glm::mat4& Drawable::getModelMatrix() 
{
    return model;
}

void Drawable::setPosition(glm::vec3 position) 
{
    position = position;
}

void Drawable::setRotation(glm::vec3 rotation) 
{
    rotation = rotation;
}

void Drawable::setScale(glm::vec3 scale) 
{
    scale = scale;
}

void Drawable::addPosition(glm::vec3 offset) 
{
    position+=offset;
}

void Drawable::addRotation(glm::vec3 rotation) 
{
    rotation+=rotation;
}
