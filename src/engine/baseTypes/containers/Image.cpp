#include "Image.hpp"


Containers::Image::Image(unsigned w, unsigned h) {
    setSize(w,h);
}

void Containers::Image::setSize(unsigned w, unsigned h) {
    data.resize(w*h*4);
}

int32_t Containers::Image::getPixel(unsigned x, unsigned y) {
    return *((int32_t*)&data[y*width+x]);
}

void Containers::Image::setPixel(unsigned x, unsigned y, int32_t color) {
    *((int32_t*)&data[y*width+x]) = color;
}

std::vector<unsigned char>& Containers::Image::getData() {
    
}

void Containers::Image::setData(const std::vector<unsigned char>& data, unsigned w, unsigned h) {
    width = w;
    height = h;
    this->data = data;
}

unsigned Containers::Image::getWidth() {
    return width;
}

unsigned Containers::Image::getHeight() {
    return height;
}
