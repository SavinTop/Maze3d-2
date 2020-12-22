#pragma once

#include "resource/resource.hpp"

class GameProcess;

class Scene{

public:
Scene(GameProcess* proc);
virtual ~Scene();
virtual void start() = 0;
virtual void update(float delta) = 0;
virtual void onDraw(float delta) = 0;
virtual void physTick(float delta){};
virtual ResourcePack getResources() = 0;
virtual void initResources() = 0;
virtual void mouseMove(double xpos, double ypos){};
virtual void mouseDown(double xpos, double ypos, int mb, int action){};
virtual void charInput(unsigned int character){};
std::string& getName(){return sceneName;};
protected:
    GameProcess* proc;
    ResourceManager* rm;
    std::string sceneName;
};