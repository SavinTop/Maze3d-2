#include "resource.hpp"

ResourcePack::ResourcePack(){};

ResourcePack::ResourcePack(const std::vector<Resource*> resources) 
{
    setResources(resources);
}

void ResourcePack::setResources(const std::vector<Resource*>& resources)
{
    this->resources_ = resources;
}

void ResourcePack::load() {
    bool allGood = true;
    for(auto res:this->resources_){
        res->load();
        if(!res->isLoaded()){
            allGood = false;
            break;
        }
    }
    loaded = allGood;
};

void ResourcePack::unload() {
    for(auto res:this->resources_){
        res->unload();
    }
    loaded = false;
};

bool ResourcePack::isLoaded() 
{
    return loaded;
}

unsigned ResourcePack::count() 
{
    return this->resources_.size();
}

std::vector<Resource*>& ResourcePack::getRes() 
{
    return this->resources_;
}