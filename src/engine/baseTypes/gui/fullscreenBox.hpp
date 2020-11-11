#pragma once

#include "guiObject.hpp"
#include "baseTypes/resources/internal/OGL/glresources.hpp"

class FullscreenBox : public GuiObject{
public:
    FullscreenBox(int window_w, int window_h);
    FullscreenBox();

    void __leftMouseBtnDown(int x, int y) override;
    void __mouseMove(int x, int y) override;
private:
    
};