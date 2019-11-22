#include "graphics/Framebuffer.h"

namespace renderx
{
	namespace graphics
	{
		Framebuffer::Framebuffer()
			:m_FBO(0),m_RBO(0)
		{

		}

		Framebuffer::~Framebuffer()
		{
			
		}


		void Framebuffer::SetupFramebuffer()
		{
			glGenFramebuffers(1, &m_FBO);
			glGenRenderbuffers(1, &m_RBO);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		}

		void Framebuffer::FramebufferTexture2D(uint32_t texture, int32_t index, int32_t level)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, texture, level);
		}

		void Framebuffer::FramebufferTexture2D(uint32_t texture, int32_t level)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, level);
		}

		void Framebuffer::BindRenderbuffer()
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		}

		void Framebuffer::RenderbufferStorage(int32_t width, int32_t height)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		}


	}
}