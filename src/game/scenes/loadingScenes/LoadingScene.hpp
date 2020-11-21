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

class LoadingScene : public Scene{
public:
LoadingScene(GameProcess* proc, Scene* nextScene);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
std::shared_ptr<res::ogl::ShaderProgram> loadingShader;
Scene* nextScene;
std::vector<Resource*> resourcesToLoad;

LoadingBar lb;
FullscreenBox fsb;
Label lbl;

int window_w;
int window_h;

unsigned currentIndex;
};