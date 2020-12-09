#pragma once

#include "baseTypes/scene.hpp"
#include "baseTypes/resources/internal/OGL/glresources.hpp"
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

#include "game/scenes/maze/maze.hpp"
#include "scenes/loadingScenes/LoadingScene.hpp"

class GameProcess;

class Menu : public Scene{
public:
Menu(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
void mouseDown(double xpos, double ypos, int mb, int action) override;
void mouseMove(double xpos, double ypos) override;
void exitClicked();
void endless_start_clicked();

private:
std::shared_ptr<MenuGui> menu;

int window_w;
int window_h;

Label testLabel;
};

