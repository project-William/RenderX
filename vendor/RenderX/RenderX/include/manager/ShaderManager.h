#pragma once
#include "..//..//Common.h"
#include "..//graphics/Shader.h"

namespace renderx::manager
{
	class REN_API ShaderManager
	{
	public:
		ShaderManager() {}
		~ShaderManager() {}

		ShaderManager(const ShaderManager&) = delete;
		ShaderManager& operator=(const ShaderManager&) = delete;

		void SubmitShader(std::shared_ptr<graphics::Shader> shader);

		std::shared_ptr<graphics::Shader>& GetPBRShaderRef() { return m_PbrShader; }
		std::shared_ptr<graphics::Shader>& GetCubemapShaderRef() { return m_EquirectangularToCubemapShader; }
		std::shared_ptr<graphics::Shader>& GetIrrdianceShaderRef() { return m_IrradianceShader; }
		std::shared_ptr<graphics::Shader>& GetPrefilterShaderRef() { return m_PrefilterShader; }
		std::shared_ptr<graphics::Shader>& GetBRDFShaderRef() { return m_BrdfShader; }
		std::shared_ptr<graphics::Shader>& GetBackgroundShaderRef() { return m_BackgroundShader; }

	private:

		std::shared_ptr<graphics::Shader> m_PbrShader;
		std::shared_ptr<graphics::Shader> m_EquirectangularToCubemapShader;
		std::shared_ptr<graphics::Shader> m_IrradianceShader;
		std::shared_ptr<graphics::Shader> m_PrefilterShader;
		std::shared_ptr<graphics::Shader> m_BrdfShader;
		std::shared_ptr<graphics::Shader> m_BackgroundShader;
	};
}