#include "resource.hpp"

ResourcePack::ResourcePack(){};

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

void ResourcePack::free() {
    for(auto res:this->resources_){
        res->free();
    }
    loaded = false;
};

bool ResourcePack::isLoaded() 
{
    return loaded;
}