#include "menuGui.hpp"

void MenuGui::initEndless() 
{
    endless = GuiWindow(w,h);
    endless_fbox = FullscreenBox(nullptr, w, h);
    endless_fbox.setParent(&endless);
    endless_back_button = Button(nullptr, back_idle.get(), back_active.get());
    endless_leftArrow = Button(nullptr, leftArrow_idle.get(), leftArrow_active.get());
    endless_rightArrow = Button(nullptr, rightArrow_idle.get(), rightArrow_active.get());
    endless_start_button = Button(nullptr, start_idle.get(), start_active.get());
    endless_startLevel = Label();

    endless_back_button.setParent(&endless_fbox);
    endless_back_button.setSize(0.3f,0.09f);
    endless_back_button.setPosition(-1.0f+0.3f,1.0f-0.09f);
    endless_back_button.setClickCallback(std::bind(&MenuGui::back_click, this));

    endless_leftArrow.setParent(&endless_fbox);
    endless_leftArrow.setSize(0.1f,0.1f);
    endless_leftArrow.setPosition(-0.33f,0.0f);
    endless_leftArrow.setClickCallback(std::bind(&MenuGui::endless_leftArrowClick, this));

    endless_rightArrow.setParent(&endless_fbox);
    endless_rightArrow.setSize(0.1f,0.1f);
    endless_rightArrow.setPosition(+0.33f,0.0f);
    endless_rightArrow.setClickCallback(std::bind(&MenuGui::endless_rightArrowClick, this));

    endless_startLevel.setParent(&endless_fbox);
    endless_startLevel.setSize(0.66f,0.1f);
    endless_startLevel.setPosition(0.0f,0.0f);
    endless_startLevel.setTextAlign(textAlign::Center);
    endless_startLevel.setText("5");

    endless_startLevel_value = 5;

    endless_start_button.setParent(&endless_fbox);
    endless_start_button.setSize(0.3f,0.09f);
    endless_start_button.setPosition(0.0f,-0.6f);

    auto temp = getChildrenRecurs(&endless);
    endless.setDrawableChildArr(temp);
}

void MenuGui::endless_leftArrowClick() 
{
    if(endless_startLevel_value<=5) return;
    endless_startLevel_value-=5;
    endless_startLevel.setText(std::to_string(endless_startLevel_value));
}

void MenuGui::endless_rightArrowClick() 
{
    if(endless_startLevel_value>=100) return;
    endless_startLevel_value+=5;
    endless_startLevel.setText(std::to_string(endless_startLevel_value));
}