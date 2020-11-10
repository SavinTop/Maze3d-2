#include "scene.hpp"
#include "game/gameprocess.hpp"

Scene::~Scene() 
{
    rm->clearGroup(sceneName);
}


Scene::Scene(GameProcess* proc) 
{
    this->proc = proc;
    this->rm = proc->rm;
}
