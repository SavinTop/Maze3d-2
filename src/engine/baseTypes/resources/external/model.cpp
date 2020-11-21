#include "model.hpp"

namespace res::ex{

Model::Model(const std::string& path):Resource() 
{
    setParams(path);
}

void Model::load() 
{
    loadModel(path);
}

void Model::unload() 
{
    
}

void Model::InitializeSubResources(std::string groupName) 
{
    this->groupName = groupName;
}

void Model::setParams(const std::string& path) 
{
    this->path = path;
}

void Model::loadModel(const std::string& path) 
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    this->directory = path.substr(0,path.find_last_of('\\'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) 
{
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }    
    
    for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
}

Containers::Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) 
{
    using namespace res::ogl;

    std::vector<Containers::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;
    
    for(unsigned int i=0;i<mesh->mNumVertices;i++)
    {
        Containers::Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;

        if(mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if(mesh->HasTangentsAndBitangents()){
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
        }

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
            
        } else vertex.texCoords = glm::vec2(0.0f,0.0f);

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
            
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
    std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
    std::vector<std::shared_ptr<Texture>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::Normal);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
    std::vector<std::shared_ptr<Texture>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::Height);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Containers::Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<res::ogl::Texture>> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, res::ogl::TextureType tt) 
{
    std::vector<std::shared_ptr<res::ogl::Texture>> textures;
    textures.reserve(mat->GetTextureCount(type));
    for(unsigned i=0;i<mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string texturePath(str.C_Str());
        texturePath = directory+"\\"+texturePath;
        
        textures.emplace_back(rm->createResource(res::ogl::Texture(texturePath, tt,res::ogl::DefaultTextureInfo, "TextureIn::"+texturePath), groupName));
    }
    return textures;
}

Model::Model() : Resource()
{
    
}

}