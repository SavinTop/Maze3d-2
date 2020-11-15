#pragma once

#include "guiObject.hpp"

class GuiWindow : public GuiObject{
public:
    GuiWindow();
    GuiWindow(int w, int h);

    void setDrawableChildArr(std::vector<GuiObject*>& drawableChildArr);
    std::vector<GuiObject*>& getDrawableChildArr(); 
    void __leftMouseBtnDown(int x, int y) override;
    void __mouseMove(int x, int y) override;
private:
    std::vector<GuiObject*> drawableChildArr;
};