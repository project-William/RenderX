#pragma once
#include "..//..//Core.h"
#include "RenderBuffer.h"

namespace renderx {
	namespace graphics {

		class REN_API FrameBuffer
		{
		private:
			GLuint m_FrameBufferID;
			RenderBuffer* m_RenderBuffer;
		public:
			FrameBuffer();
			FrameBuffer(unsigned int width,unsigned int height);
			~FrameBuffer();

			void BindFrameBuffer();
			void UnbindFrameBuffer();

			inline const GLuint& GetFrameBufferID()const { return m_FrameBufferID; }
		private:

			bool CheckInit();
		};

	}
}