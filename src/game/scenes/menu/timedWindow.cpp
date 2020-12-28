#include "menuGui.hpp"

void MenuGui::initTimed() 
{
    timed = GuiWindow(w,h);
    timed_fbox = FullscreenBox(nullptr, w, h);
    timed_fbox.setParent(&timed);
    timed_back_button = Button(nullptr, back_idle.get(), back_active.get());
    timed_leftArrow = Button(nullptr, leftArrow_idle.get(), leftArrow_active.get());
    timed_rightArrow = Button(nullptr, rightArrow_idle.get(), rightArrow_active.get());
    timed_start_button = Button(nullptr, start_idle.get(), start_active.get());
    timed_startLevel = Label();

    timed_back_button.setParent(&timed_fbox);
    timed_back_button.setSize(0.3f,0.09f);
    timed_back_button.setPosition(-1.0f+0.3f,1.0f-0.09f);
    timed_back_button.setClickCallback(std::bind(&MenuGui::back_click, this));

    timed_leftArrow.setParent(&timed_fbox);
    timed_leftArrow.setSize(0.1f,0.1f);
    timed_leftArrow.setPosition(-0.33f,0.0f);
    timed_leftArrow.setClickCallback(std::bind(&MenuGui::timed_leftArrowClick, this));

    timed_rightArrow.setParent(&timed_fbox);
    timed_rightArrow.setSize(0.1f,0.1f);
    timed_rightArrow.setPosition(+0.33f,0.0f);
    timed_rightArrow.setClickCallback(std::bind(&MenuGui::timed_rightArrowClick, this));

    timed_startLevel.setParent(&timed_fbox);
    timed_startLevel.setSize(0.66f,0.1f);
    timed_startLevel.setPosition(0.0f,0.0f);
    timed_startLevel.setTextAlign(textAlign::Center);
    timed_startLevel.setText("5");

    timed_startLevel_value = 5;

    timed_start_button.setParent(&timed_fbox);
    timed_start_button.setSize(0.3f,0.09f);
    timed_start_button.setPosition(0.0f,-0.6f);

    auto temp = getChildrenRecurs(&timed);
    timed.setDrawableChildArr(temp);
}

void MenuGui::timed_leftArrowClick() 
{
    if(timed_startLevel_value<=5) return;
    timed_startLevel_value-=5;
    timed_startLevel.setText(std::to_string(timed_startLevel_value));
}

void MenuGui::timed_rightArrowClick() 
{
    if(timed_startLevel_value>=100) return;
    timed_startLevel_value+=5;
    timed_startLevel.setText(std::to_string(timed_startLevel_value));
}