#pragma once

#include "baseTypes/gui/gui.hpp"
#include "baseTypes/resource/resource.hpp"


class MazeGui : public Resource{
public:
MazeGui();
~MazeGui();
MazeGui(int w, int h, ResourceManager* rm);

void start();
void draw();
void load() override;
void unload() override;
void mouseInput(int x, int y, bool lb);

void initDebug();
void initBeg();
void initTimer();
void debug_setDebugPlayerPos(float x, float y);
void timer_setTime(float t);

void setMazeMap(std::shared_ptr<res::ogl::Texture> mazeTexture);
void setOkCallback(std::function<void(void)> click);

virtual void InitializeSubResources(std::string groupName);
ResourcePack& getResources();
std::vector<GuiObject*> getElements();
std::vector<GuiObject*> getChildrenRecurs(GuiObject* curr);

GuiWindow* currentWindow;
GuiWindow debug;
GuiWindow timer;
GuiWindow beg;
private:
    int w,h;
    ResourceManager* rm;
    FullscreenBox debug_fbox;

    
    Label debug_playerX;
    Label debug_playerY;
    float debug_playerX_value;
    
    
    FullscreenBox timer_fbox;
    Label timer_time;
    float time_value;

    FullscreenBox beg_fbox;
    Button beg_mazemap_test;
    Button beg_ok;
    std::shared_ptr<res::ogl::Texture> beg_ok_active;
    std::shared_ptr<res::ogl::Texture> beg_ok_idle;
    std::shared_ptr<res::ogl::Texture> beg_mazemap_tex;
    std::shared_ptr<res::ogl::Texture> beg_mazemap_savin_tex;


    ResourcePack r_pack;
    std::shared_ptr<res::ogl::ShaderProgram> guiShader;
    std::string spriteDirectory = "data\\scenes\\mainMenu\\sprites\\";
};