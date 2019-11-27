#pragma once
#include "..//..//Common.h"

namespace renderx::graphics
{
	class REN_API Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		uint32_t GetFBO()const { return m_FBO; }
		uint32_t GetRBO()const { return m_RBO; }

		void BindFramebuffer()const { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }
		void UnbindFramebuffer()const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

		void FramebufferTexture2D(uint32_t texture, int32_t index, int32_t level);
		void FramebufferTexture2D(uint32_t texture, int32_t level);

		void BindRenderbuffer();
		void RenderbufferStorage(int32_t width, int32_t height);

		void SetupFramebuffer();

	private:
		uint32_t m_FBO;
		uint32_t m_RBO;

	};
}