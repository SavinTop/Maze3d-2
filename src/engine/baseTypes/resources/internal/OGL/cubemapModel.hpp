#pragma once

#include "glad/glad.h"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/resource/resourceManager.hpp"
#include "render/Drawable.hpp"
#include "cubemapTexture.hpp"

namespace res::ogl{

class CubemapModel : public OpenGLResource, public Drawable{
public:
    CubemapModel();
    CubemapModel(std::shared_ptr<CubemapTexture> cmt);

	void setParams(std::shared_ptr<CubemapTexture> cmt);

    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;
    void __draw(oglw::Shader& shader) override;
private:
    std::shared_ptr<CubemapTexture> cmt;
    unsigned vao,vbo;
};

}