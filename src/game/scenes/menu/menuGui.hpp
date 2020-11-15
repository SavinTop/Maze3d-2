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
    std::vector<GuiObject*> getElements();
    std::vector<GuiObject*> getChildrenRecurs(GuiObject* curr);
    void initMain();
    void initEndless();
    void setExitButtonClickCallBack(std::function<void(void)> click);
    
    void endlessClick();
    void timedClick();

    void back_click();

    void endless_leftArrowClick();
    void endless_rightArrowClick();

private:
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
    Button endless_leftArrow;
    Button endless_rightArrow;
    Label endless_startLevel;
    int endless_startLevel_value;
    
    Button timed_back_button;

    std::shared_ptr<res::ogl::Texture> exit_idle;
    std::shared_ptr<res::ogl::Texture> exit_active;
    std::shared_ptr<res::ogl::Texture> timed_idle;
    std::shared_ptr<res::ogl::Texture> timed_active;
    std::shared_ptr<res::ogl::Texture> endless_idle;
    std::shared_ptr<res::ogl::Texture> endless_active;
    std::shared_ptr<res::ogl::Texture> back_idle;
    std::shared_ptr<res::ogl::Texture> back_active;

    //arrows

    std::shared_ptr<res::ogl::Texture> leftArrow_idle;
    std::shared_ptr<res::ogl::Texture> leftArrow_active;
    std::shared_ptr<res::ogl::Texture> rightArrow_idle;
    std::shared_ptr<res::ogl::Texture> rightArrow_active;

    std::shared_ptr<res::ogl::ShaderProgram> guiShader;

    bool lastMouseLeftButton;
};