#include "graphics/RenderBuffer.h"


namespace renderx {
	namespace graphics {
		
		RenderBuffer::RenderBuffer()
		{
			glGenRenderbuffers(1, &m_RenderBufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
		}
		
		RenderBuffer::~RenderBuffer()
		{
			glDeleteRenderbuffers(1, &m_RenderBufferID);
		}

		void RenderBuffer::Bind()const
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
		}

		void RenderBuffer::Unbind()const
		{
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		void RenderBuffer::BufferStorage(unsigned int width,unsigned int height)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		}

	}
}