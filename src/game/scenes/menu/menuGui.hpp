#pragma once

#include "baseTypes/gui/gui.hpp"
#include "baseTypes/resource/resource.hpp"

class MenuGui : public Resource{
public:
    MenuGui();
    MenuGui(int w, int h, ResourceManager* rm);

    void start();
    void draw();
    void load() override;
	void unload() override;
    void mouseInput(int x, int y, bool lb);

	virtual void InitializeSubResources(std::string groupName);
    ResourcePack& getResources();
    std::vector<Drawable*> getElements();
    std::vector<Drawable*> getDrawableChildrenRecurs(GuiObject* curr);
    void initMain();
    void initEndless();
    void setExitButtonClickCallBack(std::function<void(void)> click);
    
    void endlessClick();
    void timedClick();

    void back_click();

private:
    Label testlabel;

    GuiWindow* currentWindow;
    GuiWindow main;
    GuiWindow endless;
    int w,h;
    ResourceManager* rm;
    std::string spriteDirectory = "data\\scenes\\mainMenu\\sprites\\";
    
    ResourcePack r_pack;

    FullscreenBox main_fbox;
    Button main_exit_button;
    Button main_timed_button;
    Button main_endless_button;

    FullscreenBox endless_fbox;
    Button endless_back_button;
    
    Button timed_back_button;

    std::shared_ptr<res::ogl::Texture> exit_idle;
    std::shared_ptr<res::ogl::Texture> exit_active;
    std::shared_ptr<res::ogl::Texture> timed_idle;
    std::shared_ptr<res::ogl::Texture> timed_active;
    std::shared_ptr<res::ogl::Texture> endless_idle;
    std::shared_ptr<res::ogl::Texture> endless_active;
    std::shared_ptr<res::ogl::Texture> back_idle;
    std::shared_ptr<res::ogl::Texture> back_active;

    std::shared_ptr<res::ogl::ShaderProgram> guiShader;
};