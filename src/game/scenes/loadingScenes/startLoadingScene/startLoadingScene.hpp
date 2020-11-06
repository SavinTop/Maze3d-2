#pragma once


#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestScene;

class StartLoadingScene : public Scene{
public:
StartLoadingScene(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
res::ogl::ShaderProgram* loadingShader;
res::ogl::Plane* loadingPlane;
TestScene* nextScene;
std::vector<Resource*> resourcesToLoad;
unsigned currentIndex;
};