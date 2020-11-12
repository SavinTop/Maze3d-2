#include "menuGui.hpp"

void MenuGui::initEndless() 
{
    endless = GuiWindow(w,h);
    endless_fbox = FullscreenBox(nullptr, w, h);
    endless_fbox.setParent(&endless);
    endless_back_button = Button(nullptr, back_idle.get(), back_active.get());

    endless_back_button.setParent(&endless_fbox);
    endless_back_button.setSize(0.3f,0.09f);
    endless_back_button.setPosition(-1.0f+0.3f,1.0f-0.09f);
    endless_back_button.setClickCallback(std::bind(&MenuGui::back_click, this));

    auto temp = getDrawableChildrenRecurs(&endless);
    endless.setDrawableChildArr(temp);
}