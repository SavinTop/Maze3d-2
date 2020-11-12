#pragma once

#include "baseTypes/gui/gui.hpp"
#include "baseTypes/resource/resource.hpp"

class MenuGui : public Resource{
public:
    MenuGui();
    MenuGui(int w, int h, ResourceManager* rm);

    void start();
    void load() override;
	void unload() override;
    void mouseInput(int x, int y, bool lb);

	virtual void InitializeSubResources(std::string groupName);
    ResourcePack getResources();
    std::vector<Drawable*> getElements();
    std::vector<Drawable*> getDrawableChildrenRecurs(GuiObject* curr);
    void initMain();

private:
    GuiWindow* currentWindow;
    GuiWindow main;
    int w,h;
    ResourceManager* rm;
    std::string spriteDirectory = "data\\scenes\\mainMenu\\sprites\\";
    
    FullscreenBox main_fbox;
    Button main_exit_button;

    std::shared_ptr<res::ogl::Texture> exit_idle;
    std::shared_ptr<res::ogl::Texture> exit_active;
    
};