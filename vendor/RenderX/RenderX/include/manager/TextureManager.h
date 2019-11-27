#pragma once

#include "..//..//Common.h"
#include "..//graphics/Texture.h"

namespace renderx::manager
{
	class REN_API TextureManager
	{
	public:
		TextureManager() {}
		~TextureManager() {}

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		void SubmitTexture(graphics::Texture& texture, graphics::TexType type);

		static void BindTexture(uint32_t tex, uint8_t slot, graphics::TexType type);
		static void UpdateTexture(graphics::Texture& tex, graphics::TexType type);

		graphics::Texture GetHDRTexture()const { return m_Hdrtexture; }
		graphics::Texture GetCubeMAP()const { return m_Cubemap; }
		graphics::Texture GetPrefTexture()const { return m_Prefilter; }
		graphics::Texture GetBRDFTexture()const { return m_Brdftexture; }
		graphics::Texture GetIrrdiTexture()const { return m_IrradianceMap; }

		void SetHDRTexture(const std::string& filepath);


	private:
		graphics::Texture m_Hdrtexture;
		graphics::Texture m_Cubemap;
		graphics::Texture m_Prefilter;
		graphics::Texture m_Brdftexture;
		graphics::Texture m_IrradianceMap;


	};
}