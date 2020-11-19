#pragma once

#include "baseTypes/gui/gui.hpp"
#include "baseTypes/resource/resource.hpp"


class MazeGui : public Resource{
public:
MazeGui();
MazeGui(int w, int h, ResourceManager* rm);

void start();
void draw();
void load() override;
void unload() override;
void mouseInput(int x, int y, bool lb);

void initDebug();
void debug_setDebugPlayerPos(float x, float y);

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

    ResourcePack r_pack;
    std::shared_ptr<res::ogl::ShaderProgram> guiShader;
};