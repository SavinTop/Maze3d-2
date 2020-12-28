#pragma once

#include "guiObject.hpp"
#include "basicTextRender.hpp"
#include "textAlign.hpp"
#include <algorithm>

class Label : public GuiObject{
public:
    Label();
    void setText(std::string text);
    void setTextAlign(textAlign ta);
    void __draw(oglw::Shader &program) override;
    void setColor(glm::vec3 clr){color = clr;}
private:
    std::string text;
    std::vector<Character> textCharacters;
    glm::vec4 textBox;
    glm::vec3 color;
    textAlign ta;
    float maxHeight;
    float textWidth;
    int calculateWidth();
    int calculateHeight();
};