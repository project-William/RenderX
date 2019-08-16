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

			m_Texture = new Texture(windata.win_Width, windata.win_Height);

			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D,
				m_Texture->GetTexRef(), 0);

			
			m_RenderBuffer = new RenderBuffer();
			m_RenderBuffer->BufferStorage(windata.win_Width, windata.win_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
									  GL_DEPTH_ATTACHMENT, 
									  GL_RENDERBUFFER, 
									  m_RenderBuffer->GetRenderBuffer());

			m_RenderBuffer->Unbind();
			UnbindFrameBuffer();
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			delete m_Texture;
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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void FrameBuffer::UpdateFramebufferData(const WinData& windata, bool& flag)
		{
			if (flag)
			{
				delete m_Texture;
				delete m_RenderBuffer;
				m_Texture = new Texture(windata.win_Width, windata.win_Height);
				std::cout << flag << std::endl;
				auto texture = m_Texture->GetTexture();

				glFramebufferTexture2D(GL_FRAMEBUFFER,
					GL_COLOR_ATTACHMENT0,
					GL_TEXTURE_2D,
					m_Texture->GetTexRef(), 0);

				m_RenderBuffer = new RenderBuffer();
				m_RenderBuffer->BufferStorage(windata.win_Width, windata.win_Height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER,
					GL_DEPTH_ATTACHMENT,
					GL_RENDERBUFFER,
					m_RenderBuffer->GetRenderBuffer());
				flag = false;
			}
			
		}

		bool FrameBuffer::CheckInit()
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}



	}
}