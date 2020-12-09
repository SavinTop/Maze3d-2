#include "color.hpp"
#include <iostream>

namespace Color{

    struct ColorStruct{
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        ColorStruct(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

    };

    ColorStruct fromInt(int32_t color){
        unsigned char* p = (unsigned char*)&color;
        return ColorStruct(p[0], p[1], p[2], p[3]);
    };

    int32_t rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a){
        return (r << 24) + (g << 16) + (b << 8) + (a);
    };

    int32_t rgba(const ColorStruct& clr){
        return *((int32_t*)&clr);
    };
    
    glm::vec4 getOglColor(int32_t color) 
    {
        float R = ((unsigned char*)&color)[3] / 255.0f;
        float G = ((unsigned char*)&color)[2] / 255.0f;
        float B = ((unsigned char*)&color)[1] / 255.0f;
        float A = ((unsigned char*)&color)[0] / 255.0f;
        std::cout<<R<<G<<B<<A<<std::endl;
        return glm::vec4(R,G,B,A);
    }
}