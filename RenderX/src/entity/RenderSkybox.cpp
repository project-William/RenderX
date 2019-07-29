#include "entity/RenderSkybox.h"

namespace renderx {
	namespace entity {

		RenderSkybox::RenderSkybox(const std::string& vsfile,const std::string& fsfile)
			:m_Cubemap(nullptr)
		{
			m_Cubemap = std::unique_ptr<graphics::CubemapTexture>(new graphics::CubemapTexture(m_Faces.m_faces));
			m_RenderData = new graphics::RenderData();
			m_RenderData->m_VAO = std::shared_ptr<graphics::VertexArray>
			(
				new graphics::VertexArray(sizeof(float)*m_SkyboxVertices.size(), &m_SkyboxVertices[0])
			);

			m_RenderData->m_Layout =
			{
				{ graphics::ShaderDataType::FLOAT3,"VertexPos" }
			};

			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData->m_Shader = std::shared_ptr<graphics::Shader>(new graphics::Shader(vsfile, fsfile));
			m_RenderData->m_Shader->SetInt("u_Skybox", 0);
		}

		RenderSkybox::~RenderSkybox()
		{
			delete m_RenderData;
		}


		void RenderSkybox::EnableObject() const
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
		}

		void RenderSkybox::DisableObject() const
		{
			m_RenderData->m_Shader->UnbindShaderProgram();
			m_RenderData->m_VAO->UnbindVertexArray();
		}

		void RenderSkybox::OnUpdate()
		{

		}


		void RenderSkybox::Draw(const graphics::WinData& windata)
		{
			glDepthMask(GL_FALSE);
			EnableObject();
			
			m_RenderData->m_Shader->SetMat4("u_view", m_Trans.view);

			m_Trans.projection = glm::perspective(glm::radians(45.0f), 
				(float)windata.win_Width / (float)windata.win_Height,
				0.1f, 100.0f);
			m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);

			m_Cubemap->BindCubemapTexture();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			DisableObject();
			glDepthMask(GL_TRUE);
		}


	}
}