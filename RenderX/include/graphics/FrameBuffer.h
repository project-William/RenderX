#pragma once
#include "..//..//Core.h"
#include "RenderBuffer.h"
#include "texture/Texture.h"
#include "Window.h"

namespace renderx {
	namespace graphics {

		class REN_API FrameBuffer
		{
		private:
			GLuint m_FrameBufferID;
			RenderBuffer* m_RenderBuffer;
			Texture *m_Texture;
		public:
			FrameBuffer();
			FrameBuffer(const WinData& windata);
			~FrameBuffer();

			void BindFrameBuffer();
			void UnbindFrameBuffer();
			void DelFramebufferTex();
			void UpdateFramebufferTex(const WinData& windata);

			inline const GLuint& GetRendered()const { return m_Texture->GetTexRef(); }
			inline const GLuint& GetFrameBufferID()const { return m_FrameBufferID; }
		private:

			bool CheckInit();
		};

	}
}