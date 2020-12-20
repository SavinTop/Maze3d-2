#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"

class ShadowHandler{
public:
    void gl_init(int m_size, float m_size_mul);
    void begin();
    void end(int wnd_w, int wnd_h);
    void clear();
    unsigned int depthMapFBO_;
    unsigned int depthMapTex_;
    int s_w,s_h;
private:
};