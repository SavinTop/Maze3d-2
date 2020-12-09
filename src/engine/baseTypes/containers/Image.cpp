#include "Image.hpp"

Containers::Image::Image() {
}

Containers::Image::Image(unsigned w, unsigned h) {
    setSize(w,h);
}

void Containers::Image::setSize(unsigned w, unsigned h) {
    this->width = w;
    this->height = h;
    data.resize(w*h*channelCount);
}

unsigned char* Containers::Image::getPixel(unsigned x, unsigned y) {
    return &data[((height-y)*width+x)*channelCount];
}

void Containers::Image::setPixel(unsigned x, unsigned y, int32_t color) {
    auto start = ((height-y)*width+x)*channelCount;
    for(auto i = start;i<start+channelCount;i++)
        data[i] = ((unsigned char*)&color)[i];
}

std::vector<unsigned char>& Containers::Image::getData() {
    return data;
}

void Containers::Image::setData(const std::vector<unsigned char>& data, unsigned w, unsigned h, int channelCount) {
    width = w;
    height = h;
    this->data = data;
    this->channelCount = channelCount;
}

unsigned Containers::Image::getWidth() {
    return width;
}

unsigned Containers::Image::getHeight() {
    return height;
}

int Containers::Image::getChannelCount() 
{
    return this->channelCount;
}

void Containers::Image::clear() {
    data.clear();    
}
