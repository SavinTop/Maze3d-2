#pragma once

#include "guiObject.hpp"
#include "render/drawable.hpp"
#include "justRect.hpp"
#include "baseTypes/resources/internal/OGL/texture.hpp"

static void drawBasicTexturedRect(glm::vec4 r, unsigned int texture_id, oglw::Shader program)
{
    glDisable(GL_DEPTH_TEST);
    Drawable d;
    d.setPosition(glm::vec3(r.x, r.y, 0.0));
    d.setScale(glm::vec3(r.z,r.w,1));
    d.draw(program);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindVertexArray(gui_getVAOid());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
}