#include "Image.hpp"


Resources::External::Image::Image():Resource() {
    
}

Resources::External::Image::Image(const std::string& path):Resource() {
    setParams(path);
}

void Resources::External::Image::load() {
    stbi_set_flip_vertically_on_load(true);
	d_ = stbi_load(this->resName_.c_str(), &width_, &height_, NULL, STBI_rgb_alpha);
    loaded = (bool)d_;
}

void Resources::External::Image::unload() {
    if(d_)
        stbi_image_free(d_);
    d_ = 0;
}

void Resources::External::Image::setParams(const std::string& path) {
    this->resName_ = path;
}

unsigned char* Resources::External::Image::data() {
    return d_;
}

int Resources::External::Image::width() {
    return width_;
}

int Resources::External::Image::height() {
    return height_;
}

