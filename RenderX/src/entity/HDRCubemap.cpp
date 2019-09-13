#include "entity/HDRCubemap.h"

namespace renderx {
	namespace entity {



		HDRCubemap::HDRCubemap(const std::string& filepath, const std::string& vsfile,const std::string& ffile)
			:m_RenderData(nullptr),m_Cubemap(nullptr)
		{
			m_Cubemap = std::shared_ptr<graphics::HDRTexture>(new graphics::HDRTexture(filepath));

			m_RenderData = std::shared_ptr<graphics::RenderData>(new graphics::RenderData());
			m_RenderData->m_VAO = std::shared_ptr<graphics::VertexArray>
			(
				new graphics::VertexArray(sizeof(float) * m_CubeData.size(), &m_CubeData[0])
			);

			m_RenderData->m_Layout =
			{
				{ graphics::ShaderDataType::FLOAT3, "a_VertexPos" },
				{ graphics::ShaderDataType::FLOAT2, "a_TexCoords" },
				{ graphics::ShaderDataType::FLOAT3, "a_Normals" },
			};

			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData->m_Shader = std::shared_ptr<graphics::Shader>(new graphics::Shader(vsfile, ffile));
			


			// pbr: setup cubemap to render to and attach to framebuffer
			// ---------------------------------------------------------
			m_EnvCubemap = new graphics::CubemapTexture(1200, 800);
			m_RenderData1 = std::shared_ptr<graphics::RenderData>(new graphics::RenderData());
			m_RenderData1->m_VAO = std::shared_ptr<graphics::VertexArray>
			(
				new graphics::VertexArray(sizeof(float) * m_CubeData.size(), &m_CubeData[0])
			);
			
			m_RenderData1->m_Layout =
			{
				{ graphics::ShaderDataType::FLOAT3, "a_VertexPos" },
				{ graphics::ShaderDataType::FLOAT2, "a_TexCoords" },
				{ graphics::ShaderDataType::FLOAT3, "a_Normals" },
			};
			
			m_RenderData1->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData1->m_Shader = std::shared_ptr<graphics::Shader>(new graphics::Shader("shader/backvertex.vert", "shader/backfragment.frag"));
			m_RenderData1->m_Shader->BindShaderProgram();
			m_RenderData1->m_Shader->SetInt("environmentMap", 0);
		

			glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1200 / (float)800, 0.1f, 100.0f);

		}

		void HDRCubemap::Init()
		{
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1200 / (float)800, 0.1f, 100.0f);
			m_RenderData1->m_Shader->BindShaderProgram();
			m_RenderData1->m_Shader->SetMat4("projection", projection);
			//EnableObject();
		}

		void HDRCubemap::RenderSkybox(CamPair& camera)
		{

			//glDepthMask(GL_FALSE);
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1200 / (float)800, 0.1f, 100.0f);
			glm::mat4 view = glm::mat4(glm::mat4(camera.first->IsUseRef() == true
								       ? camera.first->GetViewMatrix()
								       : camera.second->GetViewMatrix()));
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
			m_RenderData->m_Shader->SetMat4("view", view);
			m_RenderData->m_Shader->SetInt("environmentMap", 0);
			m_RenderData->m_Shader->SetMat4("projection", projection);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnvCubemap->GetTextureRef());
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_RenderData1->m_VAO->UnbindVertexArray();
			//glDepthMask(GL_TRUE);
	
		}

		void HDRCubemap::EnableObject()
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_Shader->SetInt("equirectangularMap", 0);
			m_RenderData->m_Shader->SetMat4("projection", m_CaptureProjection);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_Cubemap->GetHDRTextureRef());

			for (size_t i = 0; i < 6; ++i)
			{
				m_RenderData->m_Shader->SetMat4("view", m_CaptureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_EnvCubemap->GetTexture(), 0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				RenderCube();
			}
			m_RenderData->m_Shader->UnbindShaderProgram();
			
		}

		void HDRCubemap::DisableObject()
		{
		}

		void HDRCubemap::OnUpdate()
		{
		}

		void HDRCubemap::RenderCube()
		{
			m_RenderData->m_VAO->BindVertexArray();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_RenderData->m_VAO->UnbindVertexArray();
		}

		HDRCubemap::~HDRCubemap()
		{
			delete m_EnvCubemap;
		}

		void HDRCubemap::UseHDRTexture()
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_Shader->SetInt("equirectangularMap", 0);
			m_RenderData->m_Shader->SetMat4("projection", m_CaptureProjection);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_Cubemap->GetHDRTextureRef());
		}

	}
}

