#include "color.hpp"

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
}