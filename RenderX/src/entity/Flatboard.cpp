#include "entity/Flatboard.h"

namespace renderx {
	namespace entity {

		Flatboard::Flatboard(const std::string& vsfile, const std::string& ffile)
			:m_RenderData(nullptr)
		{
			PositionTexCoordNormal();
			m_RenderData = std::shared_ptr<graphics::RenderData>(new graphics::RenderData());
			m_RenderData->m_VAO = std::shared_ptr<graphics::VertexArray>
			(
				new graphics::VertexArray(sizeof(float) * m_VertexData.size(), &m_VertexData[0])
			);
			m_RenderData->m_Shader = std::shared_ptr<graphics::Shader>(new graphics::Shader(vsfile, ffile));
			m_RenderData->m_Layout =
			{
				{ graphics::ShaderDataType::FLOAT3, "a_VertexPos" },
				{ graphics::ShaderDataType::FLOAT3, "a_Normals" },
				{ graphics::ShaderDataType::FLOAT2, "a_TexCoords" },
				{ graphics::ShaderDataType::FLOAT3, "a_Tangent" },
				{ graphics::ShaderDataType::FLOAT3, "a_BiTengent" },


			};
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_Trans.model = glm::translate(m_Trans.model, glm::vec3(0.0f, 1.0f, 0.0f));
			m_Trans.model = glm::rotate(m_Trans.model, glm::radians(3*90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("albedo", "texture/diffuse_wall.jpg"));
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("normal", "texture/normal_wall.png"));

			m_RenderData->m_Shader->SetInt("u_diffuseMap", 0);
			m_RenderData->m_Shader->SetInt("u_normalMap", 1);
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
			m_RenderData->m_Shader->SetMat4("u_model", m_Trans.model);
			//set projection matrix
			m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_AlbedoTex->GetTexture());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_NormalTex->GetTexture());

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	}
}