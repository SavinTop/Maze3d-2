#include "label.hpp"

void Label::setText(std::string text) 
{
    this->text = text;
    textCharacters = guiText_getCharacters(text);
    maxHeight = calculateHeight();
    textWidth = calculateWidth()>>6;
}

void Label::setTextAlign(textAlign ta) 
{
    this->ta = ta;
}

void Label::__draw(oglw::Shader &program) 
{
    float scaleH = (float)this->h/maxHeight;
    float scaleW = (float)this->w/textWidth;
    float scale = glm::min(scaleH,scaleW);
    float tx = x-(float)w/2, ty = y-maxHeight*scale/2;

    if(ta == textAlign::Right){
        tx = tx+w-textWidth*scale;
    } else if(ta == textAlign::Center)
    {
        tx = tx+(w-textWidth*scale)/2.0f;
    }

    guiText_renderText(program, text, tx,ty,scale,glm::vec3(0.0));
}

int Label::calculateWidth() 
{
    int tempWidth = 0;
    for(auto& el:textCharacters)
        tempWidth+=el.Advance;
    return tempWidth;
}

int Label::calculateHeight() 
{   if(textCharacters.empty()) return 0;
    return (*std::max_element(textCharacters.begin(), textCharacters.end(),[](Character el1, Character el2){return el1.Size.y<el2.Size.y;})).Size.y;
}

Label::Label() : GuiObject(nullptr)
{
    ta = textAlign::Center;
    shaderType = guiShaderType::textShader;
}
