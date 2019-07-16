#pragma once
#include "..//..//Core.h"


namespace renderx {
	namespace graphics {
		
		class REN_API RenderBuffer
		{
		private:
			GLuint m_RenderBufferID;
		public:
			RenderBuffer();
			~RenderBuffer();

			void Bind() const;
			void Unbind() const;

			void BufferStorage(unsigned int width,unsigned int height);

			inline const GLuint& GetRenderBuffer()const { return m_RenderBufferID; }

		};
	}
}