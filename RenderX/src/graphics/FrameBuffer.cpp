#include "graphics/FrameBuffer.h"

namespace renderx {
	namespace graphics {

		FrameBuffer::FrameBuffer()
			:m_FrameBufferID(0),m_RenderBuffer(nullptr), m_Texture(nullptr)
		{

		}


		FrameBuffer::FrameBuffer(const WinData& windata)
			:m_FrameBufferID(0),m_RenderBuffer(nullptr),m_Texture(nullptr)
		{
			glGenFramebuffers(1, &m_FrameBufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

			
			m_RenderBuffer = new RenderBuffer();
			m_RenderBuffer->BufferStorage(windata.win_Width, windata.win_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
									  GL_DEPTH_ATTACHMENT, 
									  GL_RENDERBUFFER, 
									  m_RenderBuffer->GetRenderBuffer());

			
			m_RenderBuffer->Unbind();
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			delete m_RenderBuffer;
		}

		void FrameBuffer::BindFrameBuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			glEnable(GL_DEPTH_TEST);
		}
		
		void FrameBuffer::UnbindFrameBuffer() 
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::UpdateFramebufferTex(const WinData& windata)
		{
			m_Texture = new Texture(windata.win_Width, windata.win_Height);

			auto texture = m_Texture->GetTexture();

			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				texture, 0);

		}

		void FrameBuffer::DelFramebufferTex()
		{
			delete m_Texture;
		}

		bool FrameBuffer::CheckInit()
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}



	}
}