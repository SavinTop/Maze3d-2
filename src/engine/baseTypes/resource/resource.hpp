#pragma once

#include <vector>
#include <string>

class Resource;
class ResourceManager;

enum class LifeTime;

class ResourcePack{
    public:
        ResourcePack();
        ResourcePack(const std::vector<Resource*> resources);
        void setResources(const std::vector<Resource*>& resources);
        void load();
        void unload();
        bool isLoaded();
        unsigned count();
        std::vector<Resource*>& getRes();
    private:
        bool loaded = false;
        std::vector<Resource*> resources_;
};

class Resource{
    public:
    ResourcePack subResources_;
    std::string resName_;
    Resource(){ this->rm = nullptr;};
    virtual ~Resource(){}
    Resource(const std::string& name, ResourceManager* rm = nullptr){this->resName_ = name; this->rm = rm;}
    virtual void load() {};
    virtual void unload() {};
    void reload(){
        unload();
        load();
    }
    virtual void InitializeSubResources(std::string groupName) {};
    void setLoaded(bool val){loaded = val;}
    bool isLoaded(){return loaded;}

    ResourceManager* rm;
    protected:
        bool loaded = false;
        
};

class OpenGLResource : public Resource{
public:
    OpenGLResource() : Resource(){};
    OpenGLResource(const std::string& name, ResourceManager* rm = nullptr){this->resName_ = name; this->rm = rm;}
};

ResourcePack getResourcesRecursively(Resource* res);