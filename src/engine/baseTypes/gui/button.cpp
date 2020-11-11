#include "button.hpp"

Button::Button():GuiObject(nullptr)
{
    
}

Button::Button(res::ogl::Texture* idleTexture, res::ogl::Texture* mouseHoverTexture):GuiObject(nullptr)
{
    this->idleTexture = idleTexture;
    this->mouseHoverTexture = mouseHoverTexture;
    this->currentTexture = idleTexture;
}

void Button::__draw(res::ogl::ShaderProgram &program) 
{
    if(currentTexture)
        this->currentTexture->bind(0);
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
