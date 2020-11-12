#pragma once

#include "guiObject.hpp"

class GuiWindow : public GuiObject{
public:
    GuiWindow();
    GuiWindow(int w, int h);

    void setDrawableChildArr(std::vector<Drawable*>& drawableChildArr);
    std::vector<Drawable*>& getDrawableChildArr(); 
    void __leftMouseBtnDown(int x, int y) override;
    void __mouseMove(int x, int y) override;
private:
    std::vector<Drawable*> drawableChildArr;
};