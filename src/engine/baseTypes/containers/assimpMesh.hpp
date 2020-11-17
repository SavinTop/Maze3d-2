#pragma once

#include "mesh.hpp"
#include "baseType/resources/internal/OGL/texture.hpp"

namespace Containers{

struct AssimpTextureData{
    std::string path;
    res::ogl::TextureType tt;
}

struct AssimpMesh{
    std::vector<Containers::Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<AssimpTextureData> textures;
}

}