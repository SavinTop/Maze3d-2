#pragma once

#include "baseTypes/scene.hpp"
#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//TODO temp
#include "baseTypes/gui/basicTextRender.hpp"
#include "baseTypes/gui/gui.hpp"

class GameProcess;

class BelarusScene : public Scene{
public:
BelarusScene(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
std::shared_ptr<res::ogl::ShaderProgram> program;

int window_w;
int window_h;
};