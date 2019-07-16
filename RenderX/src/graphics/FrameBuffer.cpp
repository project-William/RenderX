#include "graphics/FrameBuffer.h"

namespace renderx {
	namespace graphics {

		FrameBuffer::FrameBuffer()
			:m_FrameBufferID(0),m_RenderBuffer(nullptr)
		{

		}


		FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
			:m_FrameBufferID(0),m_RenderBuffer(nullptr)
		{
			glGenFramebuffers(1, &m_FrameBufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			m_RenderBuffer = new RenderBuffer();
			m_RenderBuffer->BufferStorage(width, height);

			unsigned int texColorBuffer;
			glGenTextures(1, &texColorBuffer);
			glBindTexture(GL_TEXTURE_2D, texColorBuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
									  GL_DEPTH_ATTACHMENT, 
									  GL_RENDERBUFFER, 
									  m_RenderBuffer->GetRenderBuffer());

			if (CheckInit())
				RDX_INIT_SUCCESS(CheckInit(), "Framebuffer initialized successfully!");
			else RDX_INIT_ERROR(CheckInit(), "Failed to initialize framebuffer!");
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			delete m_RenderBuffer;
		}

		void FrameBuffer::BindFrameBuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
		
		void FrameBuffer::UnbindFrameBuffer() 
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		bool FrameBuffer::CheckInit()
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}



	}
}