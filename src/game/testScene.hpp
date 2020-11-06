#pragma once

#include "baseTypes/scene.hpp"
#include "baseTypes/resources/internal/OGL/glresources.hpp"
#include "gameprocess.hpp"
#include "baseTypes/color.hpp"
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class TestScene : public Scene{
public:
TestScene(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
res::ogl::ShaderProgram* program;
res::ogl::Mesh* mesh;
res::ogl::Plane* testPlane;
res::ogl::Texture* test;
};

