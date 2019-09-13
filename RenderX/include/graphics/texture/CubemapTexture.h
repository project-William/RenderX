#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace graphics {

		class REN_API CubemapTexture
		{
		public:
			CubemapTexture(int width, int height);
			CubemapTexture(const std::vector<std::string>& textureName);
			~CubemapTexture();
			
			void LoadCubeMaps();
			inline unsigned int GetTexture() const { return m_Texture; };
			inline unsigned int& GetTextureRef() { return m_Texture; }
			void BindCubemapTexture()const;
			void UnbindCubemapTexture()const;

		private:
			int m_Height, m_Width, m_Nrchannels;
			std::vector<std::string> m_Texture_Name;
			unsigned int m_Texture;
		};


	}
}