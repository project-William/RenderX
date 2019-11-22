#include "manager/ShaderManager.h"


namespace renderx
{
	namespace manager
	{

		void ShaderManager::SubmitShader(std::shared_ptr<graphics::Shader> shader)
		{
			switch (shader->GetShaderType())
			{
			case graphics::ShaderType::PBRSHADER:
				m_PbrShader = shader;
				break;
			case graphics::ShaderType::BRDFSHADER:
				m_BrdfShader = shader;
				break;
			case graphics::ShaderType::BACKGROUNDSHADER:
				m_BackgroundShader = shader;
				break;
			case graphics::ShaderType::CUBEMAPSHADER:
				m_EquirectangularToCubemapShader = shader;
				break;
			case graphics::ShaderType::IRRDIANCESHADER:
				m_IrradianceShader = shader;
				break;
			case graphics::ShaderType::PREFILTERSHADER:
				m_PrefilterShader = shader;
				break;
			default:
				break;
			}
		}

	}
}