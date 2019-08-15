#include "graphics/render/RenderSphere.h"

namespace renderx {
	namespace graphics {

		RenderSphere::RenderSphere(const std::string& vsfile, const std::string& fsfile)
			: X_SEGMENTS(64), Y_SEGMENTS(64), m_PI(3.1415926535)
		{
			m_RenderData = new RenderData();
			m_RenderData->m_Shader = std::shared_ptr<Shader>(new Shader(vsfile, fsfile));
			CreateSphere();

			m_RenderData->m_VAO = std::shared_ptr<VertexArray>
			(
				new VertexArray(sizeof(float) * m_SphereData.size(), &m_SphereData[0])
			);

			m_RenderData->m_VAO->AddEbo
			(
				sizeof(unsigned int) * m_RenderData->m_Indices.size(),
				&m_RenderData->m_Indices[0]
			);

			m_RenderData->m_Layout =
			{
				{ ShaderDataType::FLOAT3, "a_VertexPos" },
				{ ShaderDataType::FLOAT2, "a_TexCoords" },
				{ ShaderDataType::FLOAT3, "a_Normals" }
			};

			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);

			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_AOTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_MetallicTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_RoughnessTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture());
		
			m_Trans.color = glm::vec4(188/255.0f, 148/255.0f, 188/255.0f, 1.0f);
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

		RenderSphere::~RenderSphere()
		{
			delete m_RenderData;
		}

		void RenderSphere::BindObject() const
		{
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
		}

		void RenderSphere::UnbindObject() const
		{
			m_RenderData->m_VAO->UnbindVertexArray();
			m_RenderData->m_Shader->UnbindShaderProgram();
		}

		void RenderSphere::Draw(const WinData& windata)
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
					

					glDrawElements(GL_TRIANGLE_STRIP, m_IndexCount, GL_UNSIGNED_INT, 0);
				}
			}
		}

		void RenderSphere::SetAlbedoTex(const std::string& file)
		{
			m_AlbedoTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("albedo", file));
			m_RenderData->m_AlbedoTex = m_AlbedoTex->GetTexture();
		}

		void RenderSphere::SetNormalTex(const std::string& file)
		{
			m_NormalTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("normal", file));
			m_RenderData->m_NormalTex = m_NormalTex->GetTexture();
		}

		void RenderSphere::SetAOTex(const std::string& file)
		{
			m_AOTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("ao", file));
			m_RenderData->m_AOTex = m_AOTex->GetTexture();
		}

		void RenderSphere::SetRoughnessTex(const std::string& file)
		{
			m_RoughnessTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("roughness", file));
			m_RenderData->m_RoughnessTex = m_RoughnessTex->GetTexture();
		}

		void RenderSphere::SetMetallicTex(const std::string& file)
		{
			m_MetallicTex = std::shared_ptr<graphics::Texture>(new graphics::Texture("metallic", file));
			m_RenderData->m_MetallicTex = m_MetallicTex->GetTexture();
		}

		void RenderSphere::CreateSphere()
		{
			for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
			{
				for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
				{
					float xSegment = (float)x / (float)X_SEGMENTS;
					float ySegment = (float)y / (float)Y_SEGMENTS;
					float xPos = std::cos(xSegment * 2.0f * m_PI) * std::sin(ySegment * m_PI);
					float yPos = std::cos(ySegment * m_PI);
					float zPos = std::sin(xSegment * 2.0f * m_PI) * std::sin(ySegment * m_PI);

					m_RenderData->m_Positions.push_back(glm::vec3(xPos, yPos, zPos));
					m_RenderData->m_UV.push_back(glm::vec2(xSegment, ySegment));
					m_RenderData->m_Normals.push_back(glm::vec3(xPos, yPos, zPos));
				}
			}


			bool oddRow = false;
			for (int y = 0; y < Y_SEGMENTS; ++y)
			{
				if (!oddRow) // even rows: y == 0, y == 2; and so on
				{
					for (int x = 0; x <= X_SEGMENTS; ++x)
					{
						m_RenderData->m_Indices.push_back(y * (X_SEGMENTS + 1) + x);
						m_RenderData->m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					}				
				}
				else
				{
					for (int x = X_SEGMENTS; x >= 0; --x)
					{
						m_RenderData->m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
						m_RenderData->m_Indices.push_back(y * (X_SEGMENTS + 1) + x);
					}				
				}
				oddRow = !oddRow;
			}
			m_IndexCount = m_RenderData->m_Indices.size();

			for (int i = 0; i < m_RenderData->m_Positions.size(); ++i)
			{
				m_SphereData.push_back(m_RenderData->m_Positions[i].x);
				m_SphereData.push_back(m_RenderData->m_Positions[i].y);
				m_SphereData.push_back(m_RenderData->m_Positions[i].z);
				if (m_RenderData->m_UV.size() > 0)
				{
					m_SphereData.push_back(m_RenderData->m_UV[i].x);
					m_SphereData.push_back(m_RenderData->m_UV[i].y);
				}
				if (m_RenderData->m_Normals.size() > 0)
				{
					m_SphereData.push_back(m_RenderData->m_Normals[i].x);
					m_SphereData.push_back(m_RenderData->m_Normals[i].y);
					m_SphereData.push_back(m_RenderData->m_Normals[i].z);
				}
			}
		}

	}
}