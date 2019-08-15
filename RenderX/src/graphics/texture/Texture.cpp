#include "graphics/texture/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "graphics/texture/stb_image.h"

namespace renderx {
	namespace graphics {

		Texture::Texture()
			:m_Width(0), m_Height(0), m_Filepath("NULL"),m_Bits(0),
			m_Texture(0)
		{

		}

		Texture::Texture(int width, int height)
			: m_Width(width), m_Height(height), m_Filepath("NULL"),m_Bits(0),
			m_Texture(0)
		{
			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_2D, m_Texture);
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_set_flip_vertically_on_load(true);
		}

		Texture::Texture(const std::string& name, const std::string& filepath)
			: m_Name(name), m_Filepath(filepath)
		{
			m_Texture = Load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_Texture);
		}

		GLuint Texture::Load()
		{
			GLuint texture;
			unsigned char* data = nullptr;
			if (m_Filepath == "NULL")
				m_Bits = 32;
			else
				data = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_Bits, 0);
			glGenTextures(1, &texture);
		

			if (data)
			{
				GLenum format = GL_RGB;
				if (m_Bits == 1)
					format = GL_RED;
				else if (m_Bits == 3)
					format = GL_RGB;
				else if (m_Bits == 4)
					format = GL_RGBA;

				stbi_set_flip_vertically_on_load(true);
				glBindTexture(GL_TEXTURE_2D, texture);

				if (m_Name == "radiance")
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, data);
					glGenerateMipmap(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
					glGenerateMipmap(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				}

				
				stbi_image_free(data);
			}
		
			return texture;
		}

		void Texture::BindTexture()const
		{
			glBindTexture(GL_TEXTURE_2D, m_Texture);
		}

		void Texture::UnbindTexture()const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}