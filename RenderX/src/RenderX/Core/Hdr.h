#pragma once
#include "pch.h"
#include "../Core/Shader.h"

namespace renderx::Core
{
	class Hdr
	{
	public:
		static std::shared_ptr<Hdr> Get();
		~Hdr();

		void UpdateColorAttachment(int x,int y);
		unsigned int GetColorAttachment();
		void BindHdrFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, m_HdrFBO); }
		void UnbindHdrFramebuffer() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
		std::shared_ptr<Shader> GetShader() { return m_Shader; }
		float& GetExposureRef() { return m_Exposure; }
	
	private:

		static std::shared_ptr<Hdr> s_Instance;
		Hdr();
		unsigned int m_ColorAttachment;
		unsigned int m_HdrFBO;

		std::shared_ptr<Shader> m_Shader;
		float m_Exposure;

	};
}