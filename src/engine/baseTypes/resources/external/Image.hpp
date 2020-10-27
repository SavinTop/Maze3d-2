#pragma once

#include <string>
#include "baseTypes/resource.hpp"
#include "stb/stb_image.h"

namespace Resources{
namespace External{

class Image : public Resource{
public:
    Image(const std::string& path);
    Image();

    void load() override;
    void unload() override;
    void setParams(const std::string& path);

    unsigned char* data();

    int width();
    int height();

private:
    unsigned char* d_;
    int width_;
    int height_;
};

}}