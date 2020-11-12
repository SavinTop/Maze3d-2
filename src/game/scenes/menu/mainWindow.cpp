#include "menuGui.hpp"

void MenuGui::initMain() 
{
    main = GuiWindow(w,h);
    main_fbox = FullscreenBox(nullptr, w, h);
    main_exit_button = Button(nullptr, exit_idle.get(), exit_active.get());
    main_endless_button = Button(nullptr, endless_idle.get(), endless_active.get());
    main_timed_button = Button(nullptr, timed_idle.get(), timed_active.get());

    main_fbox.setParent(&main);
    main_exit_button.setParent(&main_fbox);
    main_endless_button.setParent(&main_fbox);
    main_timed_button.setParent(&main_fbox);

    main_exit_button.setSize(0.3f,0.09f);
    main_exit_button.setPosition(0.0f,-0.5f);

    main_endless_button.setSize(0.3f,0.09f);
    main_endless_button.setPosition(0.0f,0.5f);
    main_endless_button.setClickCallback(std::bind(&MenuGui::endlessClick, this));

    main_timed_button.setSize(0.3f,0.09f);
    main_timed_button.setPosition(0.0f,0.0f);
    main_timed_button.setClickCallback(std::bind(&MenuGui::timedClick, this));

    auto temp = getDrawableChildrenRecurs(&main);
    main.setDrawableChildArr(temp);
}

void MenuGui::setExitButtonClickCallBack(std::function<void(void)> click) 
{
    main_exit_button.setClickCallback(click);
}

void MenuGui::endlessClick() 
{
    currentWindow = &endless;
}

void MenuGui::timedClick() 
{
    
}