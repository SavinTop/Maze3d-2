#pragma once

#include "resource.hpp"

class GameProcess;

class Scene{

public:
Scene(GameProcess* proc){proc_ = proc;};
virtual void Start() = 0;
virtual void Update(float delta) = 0;
virtual ResourcePack getResources() = 0;

private:
    GameProcess* proc_;
};