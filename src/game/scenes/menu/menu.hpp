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


class Menu : public Scene{
public:
Menu(GameProcess* proc);
void start() override;
void update(float delta) override;
void onDraw(float delta) override;
ResourcePack getResources() override;
void initResources() override;
private:
std::shared_ptr<res::ogl::ShaderProgram> program;
std::shared_ptr<res::ogl::ShaderProgram> rectProgram;
std::shared_ptr<res::ogl::Mesh> mesh;
std::shared_ptr<res::ogl::Plane> testPlane;
std::shared_ptr<res::ogl::Texture> test;
};

