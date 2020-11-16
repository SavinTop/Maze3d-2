#pragma once

#include "baseTypes/resources/external/model.hpp"
#include "render/drawable.hpp"
#include "mesh.hpp"

namespace res::ogl{

class Model : public OpenGLResource, public Drawable{
public:
    Model();
    Model(const std::string& path);

	void setParams(const std::string& path);

    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;
    void __draw(oglw::Shader& shader) override;
private:
    std::shared_ptr<res::ex::Model> model;
    std::vector<Mesh> meshes;
    std::string path;
};


}