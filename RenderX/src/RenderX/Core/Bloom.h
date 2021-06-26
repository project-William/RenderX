#pragma once
#include "pch.h"
#include "Shader.h"

namespace renderx::Core
{
	class Bloom
	{
	public:
		static std::shared_ptr<Bloom> Get();
		~Bloom();

		std::shared_ptr<Shader> GetBloomShader() { return m_BloomShader; }
		std::shared_ptr<Shader> GetBlurShader() { return m_BlurShader; }
		std::shared_ptr<Shader> GetBloomFinalShader() { return m_BloomFinalShader; }
		std::shared_ptr<Shader> GetLightShader() { return m_LightShader; }

		unsigned int* GetColorAttachments() { return m_ColorAttachment; }
		unsigned int GetBloomFBO() { return m_FBO; }
		unsigned int* GetPingpongFBO() { return m_PingpongFBO; }
		unsigned int* GetPingpongColorBuffers() { return m_PingpongColorbuffers; }

	private:
		static std::shared_ptr<Bloom> s_Instance;
		Bloom();
		unsigned int m_FBO;
		unsigned int m_ColorAttachment[2];

		unsigned int m_PingpongFBO[2];
		unsigned int m_PingpongColorbuffers[2];

		std::shared_ptr<Shader> m_BloomShader;
		std::shared_ptr<Shader> m_BlurShader;
		std::shared_ptr<Shader> m_BloomFinalShader;
		std::shared_ptr<Shader> m_LightShader;
	};
}