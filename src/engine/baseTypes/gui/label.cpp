#include "label.hpp"

void Label::setText(std::string text) 
{
    this->text = text;
    textCharacters = guiText_getCharacters(text);
}

void Label::__draw(oglw::Shader &program) 
{
    float maxheight = guiText_getFaceHeight();
    float scaleH = (float)this->h/maxheight;
    float scaleW = (float)this->w/(calculateWidth()>>6);
    guiText_renderText(program, text, x,y,glm::min(scaleH,scaleW),glm::vec3(1.0));
}

int Label::calculateWidth() 
{
    int tempWidth = 0;
    for(auto& el:textCharacters)
        tempWidth+=el.Advance;
    return tempWidth;
}

Label::Label() : GuiObject(nullptr)
{
    
}
