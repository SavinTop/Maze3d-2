#include "model.hpp"

namespace res::ogl{

    Model::Model() 
    {
        
    }
    
    Model::Model(const std::string& path) 
    {
        setParams(path);
    }
    
    void Model::setParams(const std::string& path) 
    {
        this->path = path;
    }
    
    void Model::load() 
    {
        if(loaded) return;
        //this->model->load();
        auto& temp = this->model->getMeshes();
        this->meshes.reserve(temp.size());
        for(auto& el:temp)
        {
            for(auto& subElement:el.textures)
            {
                if(!subElement.get())
                {
                    //std::cout<<__LINE__<<" nullptr texture lol?"<<'\n';
                    continue;
                }
                subElement->load();
                //std::cout<<__LINE__<<subElement->resName_<<'\n';
            }
                
            this->meshes.push_back(el);
            this->meshes.back().load();
        }
    }
    
    void Model::unload() 
    {
        //TODO unload
    }
    
    void Model::InitializeSubResources(std::string groupName) 
    {
        this->model = rm->createResource(res::ex::Model(path), groupName);
        subResources_.setResources({this->model.get()});
    }
    
    void Model::__draw(oglw::Shader& shader) 
    {
        for(auto& el:this->meshes)
        {
            el.draw(shader);
        }
    }

}