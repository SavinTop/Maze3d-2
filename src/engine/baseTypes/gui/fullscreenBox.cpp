#include "fullscreenBox.hpp"


FullscreenBox::FullscreenBox(GuiObject* parent, int window_w, int window_h):GuiObject(parent)
{
    setPosition(window_w/2, window_h/2);
    int size = window_w>window_h?window_h:window_w;
    setSize(size,size);
}

FullscreenBox::FullscreenBox():GuiObject(nullptr) 
{
    setPosition(0,0);
    setSize(0,0);
}

void FullscreenBox::__leftMouseBtnDown(int x, int y) 
{
    for(auto el:childArr)
        el->__leftMouseBtnDown(x, y);
}

void FullscreenBox::__mouseMove(int x, int y) 
{
    for(auto el:childArr)
        el->__mouseMove(x, y);
}
