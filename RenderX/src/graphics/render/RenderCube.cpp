#include "graphics/render/RenderCube.h"


namespace renderx {
	namespace graphics {

		RenderCube::RenderCube()
			:m_RenderData(nullptr)
		{

		}

		RenderCube::RenderCube(const std::string& vspath, const std::string& fspath)
			:m_RenderData(nullptr)
		{
			m_RenderData = new RenderData();
			
			m_RenderData->m_VAO = std::shared_ptr<VertexArray>
			(
				new VertexArray(sizeof(float) * m_CubeData.size(), &m_CubeData[0])
			);
			
			m_RenderData->m_Layout = 
			{ 
				{ ShaderDataType::FLOAT3, "a_VertexPos" },
				{ ShaderDataType::FLOAT2, "a_TexCoords" },
				{ ShaderDataType::FLOAT3, "a_Normals" }
			};
			
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData->m_Shader = std::shared_ptr<Shader>(new Shader(vspath, fspath));

			//default properties
			m_Trans.color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
			m_Trans.model = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, glm::vec3(0.0f, 0.0f, -3.0f));

			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);

			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_AOTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_MetallicTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_RoughnessTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());

			m_Trans.color = glm::vec4(188 / 255.0f, 148 / 255.0f, 188 / 255.0f, 1.0f);
			m_Trans.model = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, glm::vec3(0.0f, 0.0f, -3.0f));
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_Shader->SetVec3("u_albedo", 1.0f, 1.0f, 1.0f);
			m_RenderData->m_Shader->SetFloat("u_ao", 1.0f);
			m_RenderData->m_Shader->SetInt("u_albedoMap", 0);
			m_RenderData->m_Shader->SetInt("u_normalMap", 1);
			m_RenderData->m_Shader->SetInt("u_metallicMap", 2);
			m_RenderData->m_Shader->SetInt("u_roughnessMap", 3);
			m_RenderData->m_Shader->SetInt("u_aoMap", 4);
		}

		RenderCube::~RenderCube()
		{
			delete m_RenderData;
		}


		void RenderCube::BindObject() const
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
		}

		void RenderCube::UnbindObject()const
		{
			m_RenderData->m_Shader->UnbindShaderProgram();
			m_RenderData->m_VAO->UnbindVertexArray();
		}

		void RenderCube::Draw(const WinData& windata)
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					BindObject();
					//set view matrix
					m_RenderData->m_Shader->SetMat4("u_view", m_Trans.view);
					//set model matrix
					m_Trans.model = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f * j, 0.0f, 1.5f * i));
					m_Trans.model = glm::scale(m_Trans.model, m_Trans.scale);
					m_Trans.model = glm::scale(m_Trans.model, glm::vec3(m_Trans.s_scale));
					m_RenderData->m_Shader->SetMat4("u_model", m_Trans.model);
					//set projection matrix
					m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);

					//fragment uniform variables
					m_RenderData->m_Shader->SetVec4("u_color", m_Trans.color);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, m_RenderData->m_AlbedoTex);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, m_RenderData->m_NormalTex);
					glActiveTexture(GL_TEXTURE2);
					glBindTexture(GL_TEXTURE_2D, m_RenderData->m_MetallicTex);
					glActiveTexture(GL_TEXTURE3);
					glBindTexture(GL_TEXTURE_2D, m_RenderData->m_RoughnessTex);
					glActiveTexture(GL_TEXTURE4);
					glBindTexture(GL_TEXTURE_2D, m_RenderData->m_AOTex);

					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}

		void RenderCube::SetAlbedoTex(const std::string& file)
		{
			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("albedo", file));
		}

		void RenderCube::SetNormalTex(const std::string& file)
		{
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("normal", file));
		}

		void RenderCube::SetAOTex(const std::string& file)
		{
			m_AOTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("ao", file));
		}

		void RenderCube::SetRoughnessTex(const std::string& file)
		{
			m_RoughnessTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("roughness", file));
		}

		void RenderCube::SetMetallicTex(const std::string& file)
		{
			m_MetallicTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("metallic", file));
		}

	}

}