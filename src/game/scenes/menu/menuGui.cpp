#include "menuGui.hpp"


void MenuGui::load() 
{
    this->exit_active->unload();
    this->exit_idle->unload();
}

void MenuGui::unload() 
{
    this->exit_active->load();
    this->exit_idle->load();
}

void MenuGui::mouseInput(int x, int y, bool lb) 
{
    if(!currentWindow) return;
    currentWindow->__mouseMove(x,h-y);
    if(lb)
        currentWindow->__leftMouseBtnDown(x,h-y);
}

void MenuGui::InitializeSubResources(std::string groupName) 
{
    this->exit_idle = rm->createResource(res::ogl::Texture(spriteDirectory+"buttons\\exit_idle.png"));
    this->exit_active = rm->createResource(res::ogl::Texture(spriteDirectory+"buttons\\exit_active.png"));
}

ResourcePack MenuGui::getResources() 
{
    return ResourcePack({exit_active.get(), exit_idle.get()});
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

void MenuGui::initMain() 
{
    main = GuiWindow(w,h);
    main_fbox = FullscreenBox(nullptr, w, h);
    main_exit_button = Button(nullptr, exit_idle.get(), exit_active.get());

    main_fbox.setParent(&main);
    main_exit_button.setParent(&main_fbox);

    main_exit_button.setSize(0.3f,0.09f);
    main_exit_button.setPosition(0.0f,-0.5f);
    auto temp = getDrawableChildrenRecurs(&main);
    main.setDrawableChildArr(temp);
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
    currentWindow = &main;
}

MenuGui::MenuGui() 
{
    this->w = 0;
    this->h = 0;
    this->rm = 0;
    currentWindow = nullptr;
}
