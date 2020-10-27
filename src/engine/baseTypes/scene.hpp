#pragma once

#include "resource.hpp"

class GameProcess;

class Scene{

public:
Scene(GameProcess* proc){proc_ = proc;};
virtual void start() = 0;
virtual void update(float delta) = 0;
virtual ResourcePack getResources() = 0;

protected:
    GameProcess* proc_;
};