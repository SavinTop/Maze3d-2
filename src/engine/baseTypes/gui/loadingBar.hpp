#pragma once

#include "guiObject.hpp"
#include "baseTypes/color.hpp"
#include "justRect.hpp"

class LoadingBar : public GuiObject{
public:
    LoadingBar();
    float getProgress();
    void setProgress(float val);
    void setColor(int32_t color);
    void __draw(oglw::Shader &program) override;
private:
    float progress;
    int32_t color;
};