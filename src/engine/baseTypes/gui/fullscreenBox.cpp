#include "fullscreenBox.hpp"


FullscreenBox::FullscreenBox(int window_w, int window_h):GuiObject(nullptr)
{
    setPosition(window_w/2, window_h/2);
    int size = window_w>window_h?window_h:window_w;
    setSize(size,size);
}
