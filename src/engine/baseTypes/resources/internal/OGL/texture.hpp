#pragma once

#include "stb/stb_image.h"
#include "glad/glad.h"
#include "baseTypes/resources/external/Image.hpp"
#include "baseTypes/resource/resourceManager.hpp"

#include <string>

namespace res::ogl{

struct TextureInfo
{
	unsigned int internalType;
	unsigned int min_filter;
	unsigned int mag_filter;
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int anisotropy_val;
	unsigned int channelCount;

	TextureInfo() {};

	TextureInfo(unsigned int type, unsigned int min, unsigned int mag, unsigned int wraps, unsigned int wrapt, unsigned int aniso, unsigned int channelC)
		:min_filter(min), mag_filter(mag), wrap_s(wraps), wrap_t(wrapt), anisotropy_val(aniso), internalType(type),channelCount(channelCount)
	{}
    
};

static TextureInfo DefaultTextureInfo{GL_RGBA, GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, 8, 4};

enum class TextureType{
	Diffuse, Specular, Normal, Height
};

class Texture : public OpenGLResource
{
public:
	Texture(const std::string& path, TextureType tt = TextureType::Diffuse, const TextureInfo& texInfo = DefaultTextureInfo, const std::string& name = "");
	Texture();

	void bind(unsigned int imgIndex);
	void unbind();
	void setParams(const std::string& path, TextureType tt = TextureType::Diffuse, const TextureInfo& texInfo = DefaultTextureInfo, const std::string& name = "");

    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;

	TextureType getType();

	res::ex::Image& getImage();

private:
    std::string path;
	std::shared_ptr<res::ex::Image> image;

	TextureInfo m_texinfo;
	unsigned int m_resourceId;
	TextureType tt;
};

}