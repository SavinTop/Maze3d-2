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
void debug_setDebugPlayerPos(float x, float y);

void setMazeMap(std::shared_ptr<res::ogl::Texture> mazeTexture);

virtual void InitializeSubResources(std::string groupName);
ResourcePack& getResources();
std::vector<GuiObject*> getElements();
std::vector<GuiObject*> getChildrenRecurs(GuiObject* curr);
private:
    int w,h;
    ResourceManager* rm;
    GuiWindow* currentWindow;
    FullscreenBox debug_fbox;

    GuiWindow debug;
    Label debug_playerX;
    Label debug_playerY;
    float debug_playerX_value;
    

    GuiWindow beg;
    FullscreenBox beg_fbox;
    Button beg_mazemap_test;
    std::shared_ptr<res::ogl::Texture> beg_mazemap_tex;

    ResourcePack r_pack;
    std::shared_ptr<res::ogl::ShaderProgram> guiShader;
};