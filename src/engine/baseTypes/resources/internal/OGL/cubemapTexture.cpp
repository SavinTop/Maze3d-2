#include "cubemapTexture.hpp"

namespace res::ogl
{

    CubemapTexture::CubemapTexture()
    {
    }

    CubemapTexture::CubemapTexture(const std::vector<std::string> &faces)
    {
        setParams(faces);
    }

    void CubemapTexture::bind(unsigned int imgIndex)
    {
        glActiveTexture(GL_TEXTURE0 + imgIndex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    }

    void CubemapTexture::unbind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void CubemapTexture::setParams(const std::vector<std::string> &faces)
    {
        this->faces = faces;
        textureId = 0;
    }

    void CubemapTexture::load()
    {
        if(loaded) return;
        loadCubemap();
        loaded = true;
    }

    void CubemapTexture::unload()
    {
        if(!loaded) return;
        glDeleteTextures(1, &textureId);
        loaded = false;
    }

    void CubemapTexture::InitializeSubResources(std::string groupName)
    {
    }

    void CubemapTexture::loadCubemap()
    {
        unsigned int tempTextureId = 0;
        glGenTextures(1, &tempTextureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tempTextureId);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false);
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        this->textureId = tempTextureId;
    }
} // namespace res::ogl