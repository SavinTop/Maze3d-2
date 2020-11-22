#pragma once

#include "render/drawable.hpp"
#include "baseTypes/resources/internal/OGL/mesh.hpp"

class FloorModel : public OpenGLResource, public Drawable{
public:
    FloorModel();
    FloorModel(glm::vec2 size, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures);

	void setParams(glm::vec2 size, const std::vector<std::shared_ptr<res::ogl::Texture>>& textures);

    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;
    void __draw(oglw::Shader& shader) override;
private:
    res::ogl::Mesh mesh;
};