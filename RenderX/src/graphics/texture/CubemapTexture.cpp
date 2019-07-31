#include "graphics/texture/CubemapTexture.h"
#include "graphics/texture/stb_image.h"

namespace renderx {
	namespace graphics {

		CubemapTexture::CubemapTexture(const std::vector<std::string>& textureName)
			:m_Width(0),m_Height(0),m_Nrchannels(0),m_Texture(0),m_Texture_Name(textureName)
		{
			glGenTextures(1, &m_Texture);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
			LoadCubeMaps();
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		}

		CubemapTexture::~CubemapTexture()
		{

		}

		void CubemapTexture::LoadCubeMaps()
		{
			for (int i = 0; i < m_Texture_Name.size(); ++i)
			{
				unsigned char* data = stbi_load(m_Texture_Name[i].c_str(), &m_Width, &m_Height, &m_Nrchannels, 0);
				stbi_set_flip_vertically_on_load(true);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
		}

		void CubemapTexture::BindCubemapTexture() const
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
		}
		void CubemapTexture::UnbindCubemapTexture() const
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
	}
}