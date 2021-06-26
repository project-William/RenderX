#pragma once
#include "pch.h"
#include "Shader.h"

namespace renderx::Core
{
	class ShadowMap
	{
	public:

		ShadowMap();
		~ShadowMap();
		void Init();
		unsigned int GetDepthMap() { return m_DirDepthMap; }
		unsigned int GetPointDepthMap() { return m_PointDepthMap; }
		
		const unsigned int GetShadowWidth() { return m_ShadowWidth; }
		const unsigned int GetShadowHeight() { return m_ShadowHeight; }
		unsigned int GetDepthFBO() { return m_DepthMapFBO; }
		unsigned int GetPointDepthFBO() { return m_PointDepthMapFBO; }

		std::shared_ptr<Shader> GetDepthShader() { return m_DepthShader; }
		std::shared_ptr<Shader> GetPointDepthShader() { return m_PointDepthShader; }

	private:

		std::shared_ptr<Shader> m_DepthShader;
		std::shared_ptr<Shader> m_PointDepthShader;
		unsigned int m_DepthMapFBO;
		unsigned int m_PointDepthMapFBO;
		const unsigned int m_ShadowWidth;
		const unsigned int m_ShadowHeight;
		unsigned int m_DirDepthMap;
		unsigned int m_PointDepthMap;
	};
}