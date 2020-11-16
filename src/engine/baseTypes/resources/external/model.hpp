#pragma once

#include "baseTypes/resources/internal/OGL/mesh.hpp"
#include "baseTypes/resources/internal/OGL/texture.hpp"
#include "baseTypes/containers/mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <utilities/debug.hpp>

namespace res::ex{

class Model : public Resource{
public:
    Model();
    Model(const std::string& path);
    void load() override;
    void unload() override;
	void InitializeSubResources(std::string groupName) override;
    void setParams(const std::string& path);

    std::vector<Containers::Mesh>& getMeshes(){return meshes;}

private:
    std::vector<Containers::Mesh> meshes;
    std::string directory;
    std::string path;
    std::string groupName;

    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Containers::Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<std::shared_ptr<res::ogl::Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, res::ogl::TextureType tt);
};

}