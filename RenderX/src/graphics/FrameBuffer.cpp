#include "graphics/FrameBuffer.h"

namespace renderx {
	namespace graphics {

		FrameBuffer::FrameBuffer()
		{
			glGenFramebuffers(1, &m_FrameBufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
		}

		void FrameBuffer::BindFrameBuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
		}
		
		void FrameBuffer::UnbindFrameBuffer() 
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		}





	}
}