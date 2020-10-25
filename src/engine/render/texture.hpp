#pragma once

#include "stb/stb_image.h"
#include "glad/glad.h"
#include "baseTypes/resource.hpp"

#include <string>

struct TextureInfo
{
	unsigned int internalType;
	unsigned int min_filter;
	unsigned int mag_filter;
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int anisotropy_val;

	TextureInfo() {};

	TextureInfo(unsigned int type, unsigned int min, unsigned int mag, unsigned int wraps, unsigned int wrapt, unsigned int aniso)
		:min_filter(min), mag_filter(mag), wrap_s(wraps), wrap_t(wrapt), anisotropy_val(aniso), internalType(type)
	{}
    
};

static TextureInfo DefaultTextureInfo{GL_RGB, GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, 8};

class Texture : public Resource
{
public:
	Texture(const std::string path, TextureInfo texInfo, const std::string name);

	void bind(unsigned int imgIndex);
	void unbind();

    void load() override;
    void unload() override;

private:
    std::string path;
	unsigned char* m_data;
	
	int m_width;
	int m_heigth;

	TextureInfo m_texinfo;
	unsigned int m_resourceId;
};