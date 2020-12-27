#pragma once

#include "texture.hpp"

namespace res::ogl{

class TexturePack : public OpenGLResource{
public:
    TexturePack(){};
    TexturePack(const std::vector<std::string> paths, TextureType tt = TextureType::Diffuse, const TextureInfo& texInfo = DefaultTextureInfo, const std::string& name = "");
    void setParams(const std::vector<std::string> paths, TextureType tt = TextureType::Diffuse, const TextureInfo& texInfo = DefaultTextureInfo, const std::string& name = "");
    void load() override;
    void unload() override;
    void InitializeSubResources(std::string groupName) override;
    unsigned getId(int index){return textures[index]->getId();};
    void bind(int index,unsigned int imgIndex);
	void unbind(int index);
private:
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<std::string> paths;

    TextureType tt;
    TextureInfo m_texinfo;
};

}

