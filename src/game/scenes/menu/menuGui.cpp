#include "menuGui.hpp"


void MenuGui::load() 
{
    r_pack.load();
}

void MenuGui::unload() 
{
    r_pack.unload();
}

void MenuGui::mouseInput(int x, int y, bool lb) 
{
    if(!currentWindow) return;
    currentWindow->__mouseMove(x,h-y);
    if(lb)
        currentWindow->__leftMouseBtnDown(x,h-y);
}

std::vector<Drawable*> MenuGui::getElements() 
{
    if(!currentWindow) return {};
    return currentWindow->getDrawableChildArr();
}

std::vector<Drawable*> MenuGui::getDrawableChildrenRecurs(GuiObject* curr) 
{
    if(!curr) return {};
    std::vector<Drawable*> temp;
    temp.push_back(curr);
    for(auto el:curr->getChildArr())
    {
        auto conc = getDrawableChildrenRecurs(el);
        temp.reserve(temp.size()+conc.size());
        temp.insert(temp.end(), conc.begin(), conc.end());
    }
    return temp;
}

void MenuGui::back_click() 
{
    currentWindow = &main;
}

MenuGui::MenuGui(int w, int h, ResourceManager* rm) 
{
    this->w = w;
    this->h = h;
    this->rm = rm;
    currentWindow = nullptr;
}

void MenuGui::start() 
{
    initMain();
    initEndless();
    currentWindow = &main;
}

MenuGui::MenuGui() 
{
    this->w = 0;
    this->h = 0;
    this->rm = 0;
    currentWindow = nullptr;
}
