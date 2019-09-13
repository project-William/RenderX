#pragma once
#include "..//..//..//Core.h"

namespace renderx {
	namespace graphics {
		
		class REN_API HDRTexture
		{
		public:
			HDRTexture(const std::string& filepath);
			~HDRTexture();

			inline GLuint& GetHDRTextureRef() { return m_Texture; }
			inline GLuint GetHDRTextureVal() const { return m_Texture; }

		private:
			void Load();
			const std::string& m_FilePath;
			int m_TexWidth, m_TexHeight, m_Channels;
			GLuint m_Texture;
		};

	}
}