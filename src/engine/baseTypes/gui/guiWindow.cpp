#include "guiWindow.hpp"

GuiWindow::GuiWindow():GuiObject(nullptr)
{
    
}

GuiWindow::GuiWindow(int w, int h):GuiObject(nullptr) 
{
    setSize(w,h);
}

void GuiWindow::setDrawableChildArr(std::vector<GuiObject*>& drawableChildArr) 
{
    this->drawableChildArr = drawableChildArr;
}

std::vector<GuiObject*>& GuiWindow::getDrawableChildArr() 
{
    return this->drawableChildArr;
}

void GuiWindow::__leftMouseBtnDown(int x, int y) 
{
    for(auto el:childArr)
        el->__leftMouseBtnDown(x, y);
}

void GuiWindow::__mouseMove(int x, int y) 
{
    for(auto el:childArr)
        el->__mouseMove(x, y);
}