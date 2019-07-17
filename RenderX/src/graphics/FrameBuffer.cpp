#include "graphics/FrameBuffer.h"

namespace renderx {
	namespace graphics {

		FrameBuffer::FrameBuffer()
			:m_FrameBufferID(0),m_RenderBuffer(nullptr),m_Texture(nullptr)
		{

		}


		FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
			:m_FrameBufferID(0),m_RenderBuffer(nullptr), m_Texture(nullptr)
		{
			glGenFramebuffers(1, &m_FrameBufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			m_RenderBuffer = new RenderBuffer();
			m_RenderBuffer->BufferStorage(width, height);

			m_Texture = new Texture(width, height);
			auto texColorBuffer = m_Texture->GetTexRef();
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
									  GL_DEPTH_ATTACHMENT, 
									  GL_RENDERBUFFER, 
									  m_RenderBuffer->GetRenderBuffer());

			if (CheckInit())
				RDX_INIT_SUCCESS(CheckInit(), "Framebuffer initialized successfully!");
			else RDX_INIT_ERROR(CheckInit(), "Failed to initialize framebuffer!");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
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