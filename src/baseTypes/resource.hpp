#pragma once

#include <vector>
#include <string>

class Resource;

class ResourcePack{
    std::vector<Resource*> resources_;
    public:
        ResourcePack();
        void setResources(const std::vector<Resource*>& resources);
        void load();
        void free();
        bool isLoaded();
    private:
        bool loaded = false;
};

class Resource{
    public:
    ResourcePack subResources;
    std::string _resName;
    Resource(const std::string& name){this->_resName = name;}
    virtual void load() = 0;
    virtual void free() = 0;
    bool isLoaded(){return loaded;}

    protected:
        bool loaded = false;
};
