#include "texture.hpp"

namespace res::ogl{

Texture::Texture(const std::string& path,TextureType tt, const TextureInfo& texInfo, const std::string& name) 
:OpenGLResource()
{
    setParams(path,tt, texInfo, name);
}

Texture::Texture(): OpenGLResource(){

}

void Texture::bind(unsigned int imgIndex) 
{
    glActiveTexture(GL_TEXTURE0 + imgIndex);
	glBindTexture(GL_TEXTURE_2D, m_resourceId);
}

void Texture::unbind() 
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureType Texture::getType(){
	return tt;
}

void Texture::load() 
{
	if (image->isLoaded())
	{
		glGenTextures(1, &m_resourceId);
		glBindTexture(GL_TEXTURE_2D, m_resourceId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texinfo.min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texinfo.mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texinfo.wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texinfo.wrap_t);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_texinfo.anisotropy_val);

		m_texinfo.channelCount = image->getChannelCount();

		unsigned arr[] = {GL_RED, GL_RG, GL_RGB, GL_RGBA};
		unsigned format = arr[m_texinfo.channelCount-1];

		glTexImage2D(GL_TEXTURE_2D, 0, m_texinfo.internalType, image->width(), image->height(), 0, format, GL_UNSIGNED_BYTE, image->data());
		glGenerateMipmap(GL_TEXTURE_2D);
        loaded = true;
	} else loaded = false;
}

void Texture::unload() 
{
    if(m_resourceId)
		glDeleteTextures(1, &m_resourceId);
	m_resourceId = 0;
    loaded = false;
}

void Texture::InitializeSubResources() 
{
	if(!rm) return;
	image = rm->createResource<res::ex::Image>(res::ex::Image(path,  m_texinfo.channelCount), lt);
}

void Texture::setParams(const std::string& path,TextureType tt, const TextureInfo& texInfo, const std::string& name){
	this->path = path;
	this->m_texinfo = texInfo;
	this->resName_ = name;
	this->tt = tt;
}

res::ex::Image& Texture::getImage(){
	return (*image);
}

}