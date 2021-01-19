#include "texturePack.hpp"

namespace res::ogl
{
    TexturePack::TexturePack(const std::vector<std::string> paths, TextureType tt, const TextureInfo& texInfo, const std::string& name) 
    {
        setParams(paths, tt, texInfo,name);
    }
    
    void TexturePack::setParams(const std::vector<std::string> paths, TextureType tt, const TextureInfo& texInfo, const std::string& name) 
    {
        this->paths = paths;
        this->m_texinfo = texInfo;
	    this->resName_ = name;
	    this->tt = tt;
    }
    
    void TexturePack::load() 
    {
        for(auto& el:textures)
            if(!el->isLoaded())
                el->load();
        loaded = true;
    }
    
    void TexturePack::unload() 
    {
        for(auto& el:textures)
            if(el->isLoaded())
                el->unload();
        loaded = false;
    }
    
    void TexturePack::InitializeSubResources(std::string groupName) 
    {
        if(!rm) return;
        for(int i=0;i<paths.size();i++)
        {
            std::shared_ptr<Texture> temp = rm->createResource(res::ogl::Texture(paths[i],tt,m_texinfo), groupName);
            textures.push_back(temp);
	        subResources_.getRes().push_back(temp.get());
        }
    }
    
    void TexturePack::bind(int index,unsigned int imgIndex) 
    {
        textures[index]->bind(imgIndex);
    }
    
    void TexturePack::unbind(int index) 
    {
        textures[index]->unbind();
    }
}