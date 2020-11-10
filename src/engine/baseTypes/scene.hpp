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
virtual ResourcePack getResources() = 0;
virtual void initResources() = 0;
protected:
    GameProcess* proc;
    ResourceManager* rm;
    std::string sceneName;
};