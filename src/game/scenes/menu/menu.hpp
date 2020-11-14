#pragma once

#include "baseTypes/scene.hpp"
#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "baseTypes/gui/button.hpp"
#include "baseTypes/gui/fullscreenBox.hpp"

#include "menuGui.hpp"
#include "baseTypes/gui/basicTextRender.hpp"

class Menu : public Scene{
public:
Menu(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;

void exitClicked();

private:
std::shared_ptr<res::ogl::ShaderProgram> program;
std::shared_ptr<res::ogl::ShaderProgram> rectProgram;
std::shared_ptr<res::ogl::Mesh> mesh;
std::shared_ptr<res::ogl::Plane> testPlane;

std::shared_ptr<MenuGui> menu;

int window_w;
int window_h;

};

