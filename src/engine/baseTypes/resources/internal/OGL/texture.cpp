#include "texture.hpp"

namespace res::ogl{

Texture::Texture(const Containers::Image& img, TextureType tt, const TextureInfo& texInfo, const std::string& name) 
:OpenGLResource()
{
	setParams(img, tt, texInfo, name);
}


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
	if(loaded) return;
	
	Containers::Image* tempImg;

	if(image.get() && image->isLoaded())
		tempImg = &image->getContainer();
	else
	{
		tempImg = &internalImage;
	}

	if(tempImg->getData().empty()) return;

	glGenTextures(1, &m_resourceId);
	glBindTexture(GL_TEXTURE_2D, m_resourceId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texinfo.min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texinfo.mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texinfo.wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texinfo.wrap_t);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_texinfo.anisotropy_val);

	m_texinfo.channelCount = tempImg->getChannelCount();

	unsigned arr[] = {GL_RED, GL_RG, GL_RGB, GL_RGBA};
	unsigned format = arr[m_texinfo.channelCount-1];

	glTexImage2D(GL_TEXTURE_2D, 0, m_texinfo.internalType, tempImg->getWidth(), tempImg->getHeight(), 0, format, GL_UNSIGNED_BYTE, tempImg->getData().data());
	glGenerateMipmap(GL_TEXTURE_2D);

	

    loaded = true;
	 
}

void Texture::unload() 
{
	if(!loaded) return;
    if(m_resourceId)
		glDeleteTextures(1, &m_resourceId);
	m_resourceId = 0;
    loaded = false;
}

void Texture::InitializeSubResources(std::string groupName) 
{
	if(!rm || path.empty()) return;
	image = rm->createResource<res::ex::Image>(res::ex::Image(path,  m_texinfo.channelCount),groupName);
	subResources_.setResources({image.get()});
}

void Texture::setParams(const std::string& path,TextureType tt, const TextureInfo& texInfo, const std::string& name){
	this->path = path;
	this->m_texinfo = texInfo;
	this->resName_ = name;
	this->tt = tt;
}

void Texture::setParams(const Containers::Image& img, TextureType tt, const TextureInfo& texInfo, const std::string& name) 
{
	internalImage = img;
	this->m_texinfo = texInfo;
	this->resName_ = name;
	this->tt = tt;
}

res::ex::Image& Texture::getImage(){
	return (*image);
}

}