#include "loadingBar.hpp"

LoadingBar::LoadingBar() : GuiObject(nullptr) 
{
    progress = 0;
    shaderType = guiShaderType::justColorShader;
}

float LoadingBar::getProgress() 
{
    return progress;
}

void LoadingBar::setProgress(float val) 
{
    progress = val;
    setScale(glm::vec3(w*progress,h,1));
    this->position = glm::vec3(x+w*progress/2 - w/2,y,0);
}

void LoadingBar::setColor(int32_t color) 
{
    this->color = color;
}

void LoadingBar::__draw(oglw::Shader &program) 
{
    glUniform4fv(program.getUniformLocation("color"), 1, glm::value_ptr(Color::getOglColor(color)));
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
