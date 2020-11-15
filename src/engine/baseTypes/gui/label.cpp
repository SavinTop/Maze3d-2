#include "label.hpp"

void Label::setText(std::string text) 
{
    this->text = text;
    textCharacters = guiText_getCharacters(text);
}

void Label::setTextAlign(textAlign ta) 
{
    this->ta = ta;
}

void Label::__draw(oglw::Shader &program) 
{
    float maxheight = guiText_getFaceHeight();
    float textWidth = calculateWidth()>>6;
    float scaleH = (float)this->h/maxheight;
    float scaleW = (float)this->w/textWidth;
    float scale = glm::min(scaleH,scaleW);
    float tx = x-(float)w/2, ty = y-(float)h/2;

    if(ta == textAlign::Right){
        tx = tx+w-textWidth*scale;
    } else if(ta == textAlign::Center)
    {
        tx = tx+(w-textWidth*scale)/2.0f;
    }

    guiText_renderText(program, text, tx,ty,scale,glm::vec3(1.0));
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
    ta = textAlign::Center;
}
