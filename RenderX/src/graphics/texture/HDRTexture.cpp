#include "graphics/texture/HDRTexture.h"
#include "graphics/texture/stb_image.h"

namespace renderx {
	namespace graphics {


		HDRTexture::HDRTexture(const std::string& filepath)
			:m_Texture(0),m_TexWidth(0),m_TexHeight(0),m_FilePath(filepath),m_Channels(0)
		{
			Load();
		}

		HDRTexture::~HDRTexture()
		{
			glDeleteTextures(1, &m_Texture);
		}

		void HDRTexture::Load()
		{
			float* data = stbi_loadf(m_FilePath.c_str(), &m_TexWidth, &m_TexHeight, &m_Channels, 0);
			if (data)
			{
				glGenTextures(1, &m_Texture);
				glBindTexture(GL_TEXTURE_2D, m_Texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_TexWidth, m_TexHeight, 0, GL_RGB, GL_FLOAT, data);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_set_flip_vertically_on_load(true);

				stbi_image_free(data);
			}
			else
			{
				std::cout << "Failed to load hdr texture" << std::endl;
			}

		}

	}
}