#pragma once
#include "..//..//Common.h"

namespace renderx::graphics
{

	enum class REN_API TexType
	{
		HDR_TEXTURE,
		ENVCUBEMAP,
		IRRADIANCEMAP,
		PREFILTERMAP,
		BRDFLUT_TEXTURE,
		TEXTURE2D
	};



	class REN_API Texture
	{
	public:
		Texture();
		~Texture();

		static void GenerateMipMap(uint32_t map)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, map);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		}

		void LoadTexture(TexType type, const std::string& filepath);
		uint32_t GetTexture()const { return m_Texture; }

		//static void BindTexture(uint32_t texture, uint8_t slot, TexType type);
		void GenerateMipmap() { glGenerateMipmap(GL_TEXTURE_CUBE_MAP); }
		static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
		static glm::mat4 captureProjection;
		static glm::mat4 captureViews[6];
	private:

		uint32_t m_Texture;
		int32_t m_Width;
		int32_t m_Height;
		int32_t m_Channels;
		TexType m_Type;

	};
}