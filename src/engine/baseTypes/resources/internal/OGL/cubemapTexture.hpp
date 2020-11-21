#pragma once

#include "stb/stb_image.h"
#include "glad/glad.h"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/resource/resourceManager.hpp"

namespace res::ogl{

class CubemapTexture : public OpenGLResource{
public:
    CubemapTexture();
    CubemapTexture(const std::vector<std::string>& faces);

    void bind(unsigned int imgIndex);
	void unbind();
	void setParams(const std::vector<std::string>& faces);

    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;
private:
    std::vector<std::string> faces;
    unsigned int textureId;

    void loadCubemap();
};

}