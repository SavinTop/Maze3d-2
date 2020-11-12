#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <render/drawable.hpp>
#include <functional>

class GuiObject:public Drawable{
public:
    GuiObject(GuiObject* parent, int x = 0, int y = 0, int w = 0, int h = 0);

    virtual void __leftMouseBtnDown(int x, int y) {};
    virtual void __mouseMove(int x, int y) {};
    virtual void __addChild(GuiObject* child);

    void setPosition(int x, int y);
    void setPosition(float x_coof, float y_coof);

    void setSize(int w, int h);
    void setSize(float w_coof, float h_coof);
    void setParent(GuiObject* parent);
    void setClickCallback(std::function<void(void)> click);
    int width();
    int height();
    std::vector<GuiObject*>& getChildArr();
protected:
    int x,y;
    int w,h;
    GuiObject* parent;
    std::vector<GuiObject*> childArr;
    //callbacks
    std::function<void(void)> click;
};