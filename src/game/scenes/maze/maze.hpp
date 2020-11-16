#pragma once

#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "baseTypes/resources/internal/OGL/glresources.hpp"

class mazeScene : public Scene{
    public:
    mazeScene(GameProcess* proc);
    void start() override;
    void update(float delta) override;
    void onDraw(float delta) override;
    ResourcePack getResources() override;
    void initResources() override;
    private:
    std::shared_ptr<res::ogl::Model> model;
    std::shared_ptr<res::ogl::ShaderProgram> program;

    int window_w;
    int window_h;
};
