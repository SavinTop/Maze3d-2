#pragma once


#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Menu;

class StartLoadingScene : public Scene{
public:
StartLoadingScene(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
std::shared_ptr<res::ogl::ShaderProgram> loadingShader;
std::shared_ptr<res::ogl::Plane> loadingPlane;
Menu* nextScene;
std::vector<Resource*> resourcesToLoad;
unsigned currentIndex;
};