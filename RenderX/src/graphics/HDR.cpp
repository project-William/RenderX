#include "graphics/HDR.h"

namespace renderx {
	namespace graphics {
		HDR::HDR(const std::string& vfile, const std::string& ffile)
		{
			m_RenderData = std::shared_ptr<RenderData>(new RenderData());
			m_RenderData->m_Shader = std::shared_ptr<Shader>(new Shader(vfile, ffile));
			std::vector<float> quadVertices = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			m_RenderData->m_VAO = std::shared_ptr<VertexArray>(new VertexArray(sizeof(float) * quadVertices.size(), &quadVertices[0]));
			m_RenderData->m_Layout =
			{
				{ ShaderDataType::FLOAT3, "a_VertexPos" },
				{ ShaderDataType::FLOAT2, "a_Normals" }
			};
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_Shader->SetInt("hdrBuffer", 0);
		}

		HDR::~HDR()
		{

		}

		void HDR::EnableHDRProgram(unsigned int& tex)
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex); 
		}

		void HDR::EnableHDR(float exposure)
		{
			m_RenderData->m_Shader->SetFloat("exposure", exposure);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			m_RenderData->m_Shader->UnbindShaderProgram();
			m_RenderData->m_VAO->UnbindVertexArray();
		}
	}
}