#include "menuGui.hpp"

void MenuGui::initTimed() 
{
    timed_dh.load();
    timed = GuiWindow(w,h);
    timed_fbox = FullscreenBox(nullptr, w, h);
    timed_fbox.setParent(&timed);
    timed_back_button = Button(nullptr, back_idle.get(), back_active.get());
    timed_leftArrow = Button(nullptr, leftArrow_idle.get(), leftArrow_active.get());
    timed_rightArrow = Button(nullptr, rightArrow_idle.get(), rightArrow_active.get());
    timed_start_button = Button(nullptr, start_idle.get(), start_active.get());
    timed_startLevel = Label();
    timed_min_text = Label();
    timed_avg_text = Label();
    timed_max_text = Label();

    timed_back_button.setParent(&timed_fbox);
    timed_back_button.setSize(0.3f,0.09f);
    timed_back_button.setPosition(-1.0f+0.3f,1.0f-0.09f);
    timed_back_button.setClickCallback(std::bind(&MenuGui::back_click, this));

    timed_leftArrow.setParent(&timed_fbox);
    timed_leftArrow.setSize(0.1f,0.1f);
    timed_leftArrow.setPosition(-0.33f,0.5f);
    timed_leftArrow.setClickCallback(std::bind(&MenuGui::timed_leftArrowClick, this));

    timed_rightArrow.setParent(&timed_fbox);
    timed_rightArrow.setSize(0.1f,0.1f);
    timed_rightArrow.setPosition(+0.33f,0.5f);
    timed_rightArrow.setClickCallback(std::bind(&MenuGui::timed_rightArrowClick, this));

    timed_startLevel.setParent(&timed_fbox);
    timed_startLevel.setSize(0.66f,0.1f);
    timed_startLevel.setPosition(0.0f,0.5f);
    timed_startLevel.setTextAlign(textAlign::Center);
    timed_startLevel.setText("5");

    timed_startLevel_value = 5;

    timed_start_button.setParent(&timed_fbox);
    timed_start_button.setSize(0.3f,0.09f);
    timed_start_button.setPosition(0.0f,-0.6f);

    //timed res text

    timed_min_text.setParent(&timed_fbox);
    timed_min_text.setSize(0.33f,0.1f);
    timed_min_text.setPosition(-0.1f,0.2f);
    timed_min_text.setTextAlign(textAlign::Left);
    timed_min_text.setText("Min:");

    timed_avg_text.setParent(&timed_fbox);
    timed_avg_text.setSize(0.33f,0.1f);
    timed_avg_text.setPosition(-0.1f,-0.04f);
    timed_avg_text.setTextAlign(textAlign::Left);
    timed_avg_text.setText("Avg:");

    timed_max_text.setParent(&timed_fbox);
    timed_max_text.setSize(0.33f,0.1f);
    timed_max_text.setPosition(-0.1f,-0.28f);
    timed_max_text.setTextAlign(textAlign::Left);
    timed_max_text.setText("Max:");

    //res values

    timed_min_value.setParent(&timed_fbox);
    timed_min_value.setSize(0.25f,0.1f);
    timed_min_value.setPosition(0.15f,0.2f);
    timed_min_value.setTextAlign(textAlign::Left);
    timed_min_value.setText("0.0");

    timed_avg_value.setParent(&timed_fbox);
    timed_avg_value.setSize(0.25f,0.1f);
    timed_avg_value.setPosition(0.15f,-0.04f);
    timed_avg_value.setTextAlign(textAlign::Left);
    timed_avg_value.setText("0.0");

    timed_max_value.setParent(&timed_fbox);
    timed_max_value.setSize(0.25f,0.1f);
    timed_max_value.setPosition(0.15f,-0.28f);
    timed_max_value.setTextAlign(textAlign::Left);
    timed_max_value.setText("0.0");

    auto temp = getChildrenRecurs(&timed);
    timed.setDrawableChildArr(temp);

    timed_update_res();
}

void MenuGui::timed_leftArrowClick() 
{
    if(timed_startLevel_value<=5) return;
    timed_startLevel_value-=5;
    timed_startLevel.setText(std::to_string(timed_startLevel_value));
    timed_update_res();
}

void MenuGui::timed_rightArrowClick() 
{
    if(timed_startLevel_value>=100) return;
    timed_startLevel_value+=5;
    timed_startLevel.setText(std::to_string(timed_startLevel_value));
    timed_update_res();
}

void MenuGui::timed_update_res() 
{
    auto& el = timed_dh.getData()[timed_startLevel_value/5-1];

    auto timeStr = [](float time){
       unsigned secs = floor(time);
       unsigned mills = (time-secs)*1000;
       unsigned mins = secs/60;
       return std::to_string(mins)+"m "+std::to_string(secs%60)+"s "+std::to_string(mills)+"ms"; 
    };

    if(!el.valid_info)
    {
        timed_min_value.setText("no data");
        timed_avg_value.setText("no data");
        timed_max_value.setText("no data");
    }else{
        timed_min_value.setText(timeStr(el.min));
        timed_avg_value.setText(timeStr(el.sum/el.count));
        timed_max_value.setText(timeStr(el.max));
    }
}