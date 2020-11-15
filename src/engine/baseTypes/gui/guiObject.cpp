#include "guiObject.hpp"


void GuiObject::setPosition(int x, int y) 
{
    this->x = x;
    this->y = y;
    this->position = glm::vec3(x,y,0);
}

void GuiObject::setPosition(float x_coof, float y_coof) 
{
    if(!parent) return;
    this->x = parent->x+(int)(parent->w/2*x_coof);
    this->y = parent->y+(int)(parent->h/2*y_coof);
    this->position = glm::vec3(x,y,0);
}

void GuiObject::setSize(int w, int h) 
{
    this->w = w;
    this->h = h;
    this->scale = glm::vec3(w,h,1);
}

void GuiObject::setSize(float w_coof, float h_coof) 
{
    if(!parent) return;
    this->w = (int)(parent->w*w_coof);
    this->h = (int)(parent->h*h_coof);
    this->scale = glm::vec3(w,h,1);
}

void GuiObject::setParent(GuiObject* parent) 
{
    this->parent = parent;
    if(this->parent)
    {
        parent->__addChild(this);
    }
}

void GuiObject::setClickCallback(std::function<void(void)> click) 
{
    this->click = click;
}

int GuiObject::width() 
{
    return w;
}

int GuiObject::height() 
{
    return h;
}

guiShaderType GuiObject::getShaderType() 
{
    return shaderType;
}

std::vector<GuiObject*>& GuiObject::getChildArr() 
{
    return childArr;
}

GuiObject::GuiObject(GuiObject* parent, int x, int y, int w, int h) 
{
    setPosition(x,y);
    setSize(w,h);
    setParent(parent);
    shaderType = guiShaderType::textureShader;
}

void GuiObject::__addChild(GuiObject* child) 
{
    childArr.push_back(child);
}
