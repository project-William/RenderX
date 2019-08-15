#include "entity/Flatboard.h"

namespace renderx {
	namespace entity {

		Flatboard::Flatboard(const std::string& vsfile, const std::string& ffile)
			:m_RenderData(nullptr)
		{
			m_RenderData = std::shared_ptr<graphics::RenderData>(new graphics::RenderData());
			m_RenderData->m_VAO = std::shared_ptr<graphics::VertexArray>
			(
				new graphics::VertexArray(sizeof(float) * m_VertexData.size(), &m_VertexData[0])
			);
			m_RenderData->m_Shader = std::shared_ptr<graphics::Shader>(new graphics::Shader(vsfile, ffile));
			m_RenderData->m_Layout =
			{
				{ graphics::ShaderDataType::FLOAT3, "a_VertexPos" },
				{ graphics::ShaderDataType::FLOAT2, "a_TexCoords" },
				{ graphics::ShaderDataType::FLOAT3, "a_Normals" }
			};
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_Trans.model = glm::translate(m_Trans.model, glm::vec3(0.0f, 0.5f, 0.0f));


			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("albedo", "texture/pbr/ion/albedo.png"));
			m_AOTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("ao","texture/pbr/ion/ao.png"));
			m_MetallicTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("metallic", "texture/pbr/ion/height.png"));
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("normal", "texture/pbr/ion/normal.png"));
			m_RoughnessTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("roughness", "texture/pbr/ion/roughness.png"));
			

			m_RenderData->m_Shader->SetInt("u_albedoMap", 0);
			m_RenderData->m_Shader->SetInt("u_normalMap", 1);
			m_RenderData->m_Shader->SetInt("u_metallicMap", 2);
			m_RenderData->m_Shader->SetInt("u_roughnessMap", 3);
			m_RenderData->m_Shader->SetInt("u_aoMap", 4);
		}

		Flatboard::~Flatboard()
		{

		}

		void Flatboard::EnableObject()
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
		}

		void Flatboard::DisableObject()
		{
			m_RenderData->m_Shader->UnbindShaderProgram();
			m_RenderData->m_VAO->UnbindVertexArray();
		}


		void Flatboard::Draw(const graphics::WinData& windata, FPSCamera* camera)
		{
			
			//set view matrix
			m_RenderData->m_Shader->SetMat4("u_view", m_Trans.view);
			//set model matrix
			m_Trans.model = glm::scale(m_Trans.model, m_Trans.scale);
			m_Trans.model = glm::scale(m_Trans.model, glm::vec3(m_Trans.s_scale));
			m_RenderData->m_Shader->SetMat4("u_model", m_Trans.model);
			//set projection matrix
			m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_AlbedoTex->GetTexture());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_NormalTex->GetTexture());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_MetallicTex->GetTexture());
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, m_RoughnessTex->GetTexture());
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, m_AOTex->GetTexture());

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	}
}