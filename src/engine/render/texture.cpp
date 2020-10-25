#include "texture.hpp"

Texture::Texture(const std::string path, TextureInfo texInfo, const std::string name) 
:Resource(name)
{
    this->path = path;
    this->m_texinfo = texInfo;
}

void Texture::bind(unsigned int imgIndex) 
{
    
}

void Texture::unbind() 
{
    
}

void Texture::load() 
{
    stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(path.c_str(), &m_width, &m_heigth, NULL, STBI_rgb_alpha);


	glGenTextures(1, &m_resourceId);
	glBindTexture(GL_TEXTURE_2D, m_resourceId);

	if (m_data)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texinfo.min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texinfo.mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texinfo.wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texinfo.wrap_t);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_texinfo.anisotropy_val);

		glTexImage2D(GL_TEXTURE_2D, 0, m_texinfo.internalType, m_width, m_heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		glGenerateMipmap(GL_TEXTURE_2D);
        loaded = true;
        stbi_image_free(m_data);
	} else loaded = false;
}

void Texture::unload() 
{
    if(m_resourceId)
	glDeleteTextures(1, &m_resourceId);
    loaded = false;
}
