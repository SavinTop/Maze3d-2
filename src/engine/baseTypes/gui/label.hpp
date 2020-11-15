#pragma once

#include "guiObject.hpp"
#include "basicTextRender.hpp"
#include "textAlign.hpp"

class Label : public GuiObject{
public:
    Label();
    void setText(std::string text);
    void setTextAlign(textAlign ta);
    void __draw(oglw::Shader &program) override;
private:
    std::string text;
    std::vector<Character> textCharacters;
    glm::vec4 textBox;
    textAlign ta;
    float maxHeight;
    float textWidth;
    int calculateWidth();
    int calculateHeight();
};