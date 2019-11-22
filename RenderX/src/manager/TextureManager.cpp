#include "manager/TextureManager.h"

namespace renderx
{
	namespace manager
	{

		void TextureManager::BindTexture(uint32_t tex, uint8_t slot, graphics::TexType type)
		{
			switch (type)
			{
			case graphics::TexType::HDR_TEXTURE:
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_2D, tex);
				break;
			case graphics::TexType::ENVCUBEMAP:
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
				break;
			case graphics::TexType::IRRADIANCEMAP:
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
				break;
			case graphics::TexType::PREFILTERMAP:
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
				break;
			case graphics::TexType::BRDFLUT_TEXTURE:
				glActiveTexture(GL_TEXTURE0 + slot);
				glBindTexture(GL_TEXTURE_2D, tex);
				break;
			default:
				break;
			}
		}

		void TextureManager::SetHDRTexture(const std::string& filepath)
		{

		}

		void TextureManager::UpdateTexture(graphics::Texture& tex, graphics::TexType type)
		{
			
		}

		void TextureManager::SubmitTexture(graphics::Texture& texture, graphics::TexType type)
		{
			switch (type)
			{
			case graphics::TexType::HDR_TEXTURE:
				m_Hdrtexture = texture;
				break;
			case graphics::TexType::ENVCUBEMAP:
				m_Cubemap = texture;
				break;
			case graphics::TexType::IRRADIANCEMAP:
				m_IrradianceMap = texture;
				break;
			case graphics::TexType::PREFILTERMAP:
				m_Prefilter = texture;
				break;
			case graphics::TexType::BRDFLUT_TEXTURE:
				m_Brdftexture = texture;
				break;
			default:
				break;
			}
		}

	}
}