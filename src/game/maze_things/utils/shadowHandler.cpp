#include "shadowHandler.hpp"

#include "utilities/debug.hpp"

void ShadowHandler::gl_init(int m_size, float m_size_mul) 
{
    s_w = (int)(m_size*m_size_mul);
    s_w = 2048*m_size/5;
    s_h = s_w;

    glGenFramebuffers(1, &depthMapFBO_);
    glGenTextures(1, &depthMapTex_);
    glBindTexture(GL_TEXTURE_2D, depthMapTex_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
             s_w, s_h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTex_, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

void ShadowHandler::begin() 
{
    glViewport(0, 0, s_w, s_h);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO_);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowHandler::end(int wnd_w, int wnd_h) 
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, wnd_w, wnd_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowHandler::clear() 
{
    glDeleteTextures(1, &depthMapTex_);
    glDeleteFramebuffers(1, &depthMapFBO_);
}
