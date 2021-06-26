#include "pch.h"
#include "Texture.h"
#include "..//Vendor/stb_image.h"


namespace renderx::Core
{
	
	//unsigned int TextureLoader::LoadTexture(const std::string& filePath)
	//{
    //    unsigned int textureID;
    //    glGenTextures(1, &textureID);
    //
    //    int width, height, nrComponents;
    //    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    //    if (data)
    //    {
    //        GLenum format;
    //        if (nrComponents == 1)
    //            format = GL_RED;
    //        else if (nrComponents == 3)
    //            format = GL_RGB;
    //        else if (nrComponents == 4)
    //            format = GL_RGBA;
    //
    //        glBindTexture(GL_TEXTURE_2D, textureID);
    //        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    //        glGenerateMipmap(GL_TEXTURE_2D);
    //
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    //        stbi_image_free(data);
    //    }
    //    else
    //    {
    //        std::cout << "Texture failed to load at path: " << filePath << std::endl;
    //        stbi_image_free(data);
    //    }
    //
    //    return textureID;
	//}

    unsigned int TextureLoader::LoadTexture(const std::string& filePath, bool gammaCorrection)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum internalFormat;
            GLenum dataFormat;
            if (nrComponents == 1)
            {
                internalFormat = dataFormat = GL_RED;
            }
            else if (nrComponents == 3)
            {
                internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
                dataFormat = GL_RGB;
            }
            else if (nrComponents == 4)
            {
                internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
                dataFormat = GL_RGBA;
            }

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);


            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, dataFormat== GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, dataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << filePath << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }


    std::pair<unsigned int,unsigned int> TextureLoader::LoadEnvMap(const std::string& filepath)
    {
        // pbr: load the HDR environment map
        // ---------------------------------
        stbi_set_flip_vertically_on_load(true);
        int width, height, nrComponents;
        float* data = stbi_loadf(filepath.c_str(), &width, &height, &nrComponents, 0);
        unsigned int hdrTexture;
        if (data)
        {
            glGenTextures(1, &hdrTexture);
            glBindTexture(GL_TEXTURE_2D, hdrTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load HDR image." << std::endl;
        }

        // pbr: setup cubemap to render to and attach to framebuffer
        // ---------------------------------------------------------
        unsigned int envCubemap;
        glGenTextures(1, &envCubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);
        for (unsigned int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // enable pre-filter mipmap sampling (combatting visible dots artifact)
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return { hdrTexture,envCubemap };

    }


    void TextureLoader::UseTexture(int slot, unsigned int texture, TextureType type)
    {
        glActiveTexture(GL_TEXTURE0+slot);
        switch (type)
        {
        case TextureType::TEXTURE2D:glBindTexture(GL_TEXTURE_2D, texture); break;
        case TextureType::TEXTURE_CUBE:glBindTexture(GL_TEXTURE_CUBE_MAP, texture); break;
        }
    }

    void TextureLoader::CreateColorAttachment(int width, int height, unsigned int& ColorAttachment)
    {

        //stbi_set_flip_vertically_on_load(true);
        glGenTextures(1, &ColorAttachment);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, ColorAttachment);

        // Give an empty image to OpenGL ( the last "0" )
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        // Poor filtering. Needed !
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Set "renderedTexture" as our colour attachement #0
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment, 0);
    }

}
