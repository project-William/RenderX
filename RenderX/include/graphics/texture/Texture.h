#pragma once
#include "..//..//..//Core.h"


namespace renderx {
	namespace graphics {

		enum REN_API TexWrap
		{
			REPEAT				= GL_REPEAT,
			MIRRORED_REPEAT		= GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE		= GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER		= GL_CLAMP_TO_BORDER
		};

		class REN_API Texture
		{
		private:
			TexWrap m_TexWrapMode;
			GLuint m_Texture;
			std::string m_Name;
			std::string m_Filepath;
			int m_Height;
			int m_Width;
			int m_Bits;
		public:
			Texture();
			Texture(int width, int height);
			Texture(const std::string& name, std::string& filepath);
			~Texture();

			inline const GLuint& GetTexRef()const { return m_Texture; }
			inline GLuint GetTexture()const { return m_Texture; }
			inline int GetTextureWidth()const { return m_Width; }
			inline int GetTextureHeight()const { return m_Height; }
			inline std::string GetTextureName()const { return m_Name; }

			void BindTexture()const;
			void UnbindTexture()const;

			void SetFrameBufferTexture(int width, int height);


		private:
			GLuint Load();
		};
	}
}