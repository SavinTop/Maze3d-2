#pragma once

#include <vector>
#include <cstdint>

namespace Containers{

class Image{
public:

Image();
Image(unsigned w, unsigned h);
void setSize(unsigned w, unsigned h);

unsigned char* getPixel(unsigned x, unsigned y);
void setPixel(unsigned x, unsigned y, int32_t color);

std::vector<unsigned char>& getData();
void setData(const std::vector<unsigned char>& data, unsigned w, unsigned h, int channelCount);

unsigned getWidth();
unsigned getHeight();
int getChannelCount();

void clear();

private:
    std::vector<unsigned char> data;
    unsigned width;
    unsigned height;
    int channelCount = 4;
};

}