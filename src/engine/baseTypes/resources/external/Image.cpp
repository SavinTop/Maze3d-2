#include "Image.hpp"


namespace res::ex{

Image::Image():Resource() {
    channelCount = 0;
}

Image::Image(const std::string& path, int channelCount):Resource() {
    setParams(path, channelCount);
}

void Image::load() {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* d = 0;
    int width,height;
    if(channelCount)
	    d = stbi_load(this->resName_.c_str(), &width, &height, NULL, channelCount);
    else
        d = stbi_load(this->resName_.c_str(), &width, &height, &channelCount, NULL);
    
    if(d){
        std::vector<unsigned char> trans(d, d+width*height*channelCount);
        image.setData(trans, width, height, channelCount);
        stbi_image_free(d);
        loaded = true;
    }else
    loaded = false;
}

void Image::unload() {
    image.clear();
}

void Image::setParams(const std::string& path, int channelCount) {
    this->resName_ = path;
    this->channelCount = channelCount;
}

unsigned char* Image::data() {
    return image.getData().data();
}

int Image::width() {
    return image.getWidth();
}

int Image::height() {
    return image.getHeight();
}

Containers::Image& Image::getContainer() {
    return image;
}

}