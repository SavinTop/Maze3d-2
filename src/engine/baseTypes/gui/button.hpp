#pragma once

#include "guiObject.hpp"
#include "render/drawable.hpp"
#include "justRect.hpp"
#include "baseTypes/resources/internal/OGL/texture.hpp"

class Button : public GuiObject{
public:
    Button();
    Button(GuiObject* parent, res::ogl::Texture* idleTexture, res::ogl::Texture* mouseHoverTexture, float fadeSpeed=3);
    void __draw(oglw::Shader &program) override;

    void __leftMouseBtnDown(int x, int y) override;
    void __mouseMove(int x, int y) override;
    
private:
    res::ogl::Texture* idleTexture;
    res::ogl::Texture* mouseHoverTexture;
    float transValue;
    float disTrans;
    float lastTime;
    float fadeSpeed;
};