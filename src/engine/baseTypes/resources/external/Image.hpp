#pragma once

#include <string>
#include "baseTypes/resource/resource.hpp"
#include "stb/stb_image.h"
#include "baseTypes/containers/Image.hpp"

namespace res::ex{

class Image : public Resource{
public:
    Image(const std::string& path, int channelCount = 0);
    Image();

    void load() override;
    void unload() override;
    void setParams(const std::string& path, int channelCount = 0);

    Containers::Image& getContainer();
    unsigned char* data();

    int width();
    int height();
    int getChannelCount(){return channelCount;}

private:
    Containers::Image image;
    int channelCount;
};

}