#include "button.hpp"

Button::Button():GuiObject(nullptr)
{
    this->currentTexture = this->idleTexture = this->mouseHoverTexture = nullptr;
    click = nullptr;
}

Button::Button(res::ogl::Texture* idleTexture, res::ogl::Texture* mouseHoverTexture):GuiObject(nullptr)
{
    this->idleTexture = idleTexture;
    this->mouseHoverTexture = mouseHoverTexture;
    this->currentTexture = idleTexture;
    click = nullptr;
}

void Button::__draw(res::ogl::ShaderProgram &program) 
{
    if(currentTexture)
        this->currentTexture->bind(0);
    glUniform1i(program.getUniformLocation("texture_diffuse1"),0);
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
        currentTexture = mouseHoverTexture;
        else
        currentTexture = idleTexture;
    }
}
