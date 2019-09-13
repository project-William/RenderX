#include "graphics/FrameBuffer.h"

namespace renderx {
	namespace graphics {

		FrameBuffer::FrameBuffer()
			:m_FrameBufferID(0),m_RenderBuffer(nullptr), m_BaseTexture(nullptr)
		{

		}


		FrameBuffer::FrameBuffer(const WinData& windata)
			:m_FrameBufferID(0),m_RenderBuffer(nullptr),m_BaseTexture(nullptr)
		{
			glGenFramebuffers(1, &m_FrameBufferID);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
			UnbindFrameBuffer();
		}

		FrameBuffer::~FrameBuffer()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			delete m_BaseTexture;
			delete m_RenderBuffer;
		}

		void FrameBuffer::InitFramebuffer(const WinData& windata)
		{
			BindFrameBuffer();

			CreateBaseTexture(windata);
			AttachTexture(m_BaseTexture->GetTexRef(), FBTexAttachType::COLOR_ATTACH_0);
			UpdateRenderBuffer(windata);
			
			UnbindFrameBuffer();
		}

		void FrameBuffer::AttachTexture(const GLuint& texture, FBTexAttachType type)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER,
				GetFBTexAttachType(type),
				GL_TEXTURE_2D,
				texture, 0);
		}


		void FrameBuffer::CreateBaseTexture(const graphics::WinData& windata)
		{
			m_BaseTexture = new Texture(windata.win_Width, windata.win_Height);
		}


		void FrameBuffer::UpdateRenderBuffer(const graphics::WinData& windata)
		{
			m_RenderBuffer = new RenderBuffer();
			m_RenderBuffer->BufferStorage(windata.win_Width, windata.win_Height,GL_DEPTH24_STENCIL8);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER,
				GL_DEPTH_STENCIL_ATTACHMENT,
				GL_RENDERBUFFER,
				m_RenderBuffer->GetRenderBuffer());

			m_RenderBuffer->Unbind();
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
				delete m_BaseTexture;
				delete m_RenderBuffer;
				CreateBaseTexture(windata);
				std::cout << flag << std::endl;
				auto texture = m_BaseTexture->GetTexture();

				AttachTexture(m_BaseTexture->GetTexRef(), FBTexAttachType::COLOR_ATTACH_0);
			
				UpdateRenderBuffer(windata);
			
				flag = false;
			}

			
		}


		bool FrameBuffer::CheckInit()
		{
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}

	}
}