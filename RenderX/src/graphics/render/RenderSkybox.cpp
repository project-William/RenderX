#include "graphics/render/RenderSkybox.h"

namespace renderx {
	namespace graphics {

		RenderSkybox::RenderSkybox(const std::string& vsfile,const std::string& fsfile)
			:m_Cubemap(nullptr)
		{
			m_Cubemap = std::unique_ptr<CubemapTexture>(new CubemapTexture(m_Faces.m_faces));
			m_RenderData = new RenderData();
			m_RenderData->m_VAO = std::shared_ptr<VertexArray>
			(
				new VertexArray(sizeof(float)*m_SkyboxVertices.size(), &m_SkyboxVertices[0])
			);

			m_RenderData->m_Layout =
			{
				{ ShaderDataType::FLOAT3,"VertexPos" }
			};

			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData->m_Shader = std::shared_ptr<Shader>(new Shader(vsfile, fsfile));
			m_RenderData->m_Shader->SetInt("u_Skybox", 0);
		}

		RenderSkybox::~RenderSkybox()
		{
			delete m_RenderData;
		}


		void RenderSkybox::BindObject() const
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
		}

		void RenderSkybox::UnbindObject() const
		{
			m_RenderData->m_Shader->UnbindShaderProgram();
			m_RenderData->m_VAO->UnbindVertexArray();
		}


		void RenderSkybox::Draw(const WinData& windata)
		{
			glDepthMask(GL_FALSE);
			BindObject();
			
			m_RenderData->m_Shader->SetMat4("u_view", m_Trans.view);

			m_Trans.projection = glm::perspective(glm::radians(45.0f), 
				(float)windata.win_Width / (float)windata.win_Height,
				0.1f, 100.0f);
			m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);

			m_Cubemap->BindCubemapTexture();
			glDrawArrays(GL_TRIANGLES, 0, 36);

			UnbindObject();
			glDepthMask(GL_TRUE);
		}

		void RenderSkybox::RenderProperties()
		{

		}

		void RenderSkybox::Position(const glm::vec3& position)
		{

		}

		void RenderSkybox::Rotation(const float radians, const glm::vec3& axis)
		{

		}

		void RenderSkybox::Scale(const float scale)
		{

		}

	


	}
}