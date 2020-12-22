#include "button.hpp"
#include <glfw/glfw3.h>
#include <cmath>

Button::Button():GuiObject(nullptr)
{
    this->idleTexture = this->mouseHoverTexture = nullptr;
    click = nullptr;
    transValue = disTrans = 0;
    lastTime = glfwGetTime();
}

Button::Button(GuiObject* parent, res::ogl::Texture* idleTexture, res::ogl::Texture* mouseHoverTexture, float fadeSpeed):GuiObject(parent)
{
    this->idleTexture = idleTexture;
    this->mouseHoverTexture = mouseHoverTexture;
    this->fadeSpeed = fadeSpeed;
}

void Button::__draw(oglw::Shader &program) 
{
    float currTime = glfwGetTime();
    float deltaTime = currTime-lastTime;
    transValue+=(disTrans-transValue)*deltaTime*fadeSpeed;
    glUniform1i(program.getUniformLocation("texture_diffuse1"), 0);
    glUniform1i(program.getUniformLocation("texture_diffuse2"), 1);
    this->idleTexture->bind(0);
    this->mouseHoverTexture->bind(1);
    glUniform1f(program.getUniformLocation("delta"), transValue);
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    lastTime = currTime;
}

void Button::__leftMouseBtnDown(int x, int y) 
{
    if(click)
    {
        if(x>this->x-this->w/2 && x<this->x+this->w/2 && y>this->y-this->h/2 && y<this->y+this->h/2) 
            click();
    }
}

void Button::__mouseMove(int x, int y) 
{
    if(idleTexture && mouseHoverTexture)
    {
        if(x>this->x-w/2 && x<this->x+w/2 && y>this->y-h/2 && y<this->y+h/2)
        {
            disTrans = 1;
        }
        else
        {
            disTrans = 0;
        }
        
    }
}
