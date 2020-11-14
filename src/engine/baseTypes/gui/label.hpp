#pragma once

#include "guiObject.hpp"
#include "basicTextRender.hpp"

class Label : public GuiObject{
public:
    Label();
    void setText(std::string text);
    void __draw(oglw::Shader &program) override;
private:
    std::string text;
    std::vector<Character> textCharacters;
    glm::vec4 textBox;
    float maxHeight;
    float realHeight;
    int calculateWidth();
};