#include "scene.hpp"
#include "game/gameprocess.hpp"

Scene::~Scene() 
{
    //TODO no need, memory fine, just dont delete, little lick, but fuck it:ddddd
    
    //rm->clearGroup(sceneName);
}


Scene::Scene(GameProcess* proc) 
{
    this->proc = proc;
    this->rm = proc->rm;
}
