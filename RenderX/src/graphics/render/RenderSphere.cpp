#include "graphics/render/RenderSphere.h"

namespace renderx {
	namespace graphics {
		RenderSphere::RenderSphere()
			:X_SEGMENTS(64), Y_SEGMENTS(64), m_PI(3.1415926535)
		{

		}

		RenderSphere::RenderSphere(const std::string& vsfile, const std::string& fsfile)
			:X_SEGMENTS(64),Y_SEGMENTS(64),m_PI(3.1415926535)
		{
			m_RenderData = new RenderData();
			m_RenderData->m_Shader = std::shared_ptr<Shader>(new Shader(vsfile, fsfile));
			CreateSphere();
			
			m_RenderData->m_VAO = std::shared_ptr<VertexArray>
			(
				new VertexArray( sizeof(float) * m_SphereData.size(), &m_SphereData[0])
			);
			
			m_RenderData->m_VAO->AddEbo
			(
				sizeof(unsigned int) * m_RenderData->m_Indices.size(),
				&m_RenderData->m_Indices[0]
			);
			
			m_RenderData->m_Layout = 
			{
				{ ShaderDataType::FLOAT3, "VertexPos" },
				{ ShaderDataType::FLOAT2, "TexCoords" },
				{ ShaderDataType::FLOAT3, "Normals" }
			};
			
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);

			m_Trans.color = glm::vec4(0.6f, 0.0f, 0.6f, 1.0f);
			m_Trans.model = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, glm::vec3(0.0f, 0.0f, -3.0f));
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
			m_RenderData->m_Shader->BindShaderProgram();
			m_RenderData->m_VAO->BindVertexArray();
			
			//set view matrix
			m_Trans.view = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, m_Trans.position-glm::vec3(0.0f,0.0f,5.0f));
			m_RenderData->m_Shader->SetMat4("u_view", m_Trans.view);
			//set model matrix
			m_Trans.model = glm::mat4(1.0f);
			m_RenderData->m_Shader->SetMat4("u_model", m_Trans.model);
			//set projection matrix
			m_Trans.projection = glm::mat4(1.0f);
			m_Trans.projection = glm::perspective(glm::radians(m_Trans.perspective_radians),
				(float)windata.win_Width / (float)windata.win_Height,
				0.1f, 100.0f);
			m_RenderData->m_Shader->SetMat4("u_projection", m_Trans.projection);
			m_RenderData->m_Shader->SetVec4("u_color", m_Trans.color);

			glDrawElements(GL_TRIANGLE_STRIP, m_IndexCount, GL_UNSIGNED_INT, 0);

		}

		void RenderSphere::Color(const WinData& windata)
		{
			ImGui::ColorEdit4("Color", &m_Trans.color[0]);

			ImGui::SliderFloat3("Position", &m_Trans.position[0], -5.0f, 5.0f);
		}

		void RenderSphere::RenderProperties()
		{

	
		}


		void RenderSphere::Position(const glm::vec3& position)
		{

		}

		void RenderSphere::Rotation(const float radians, const glm::vec3& axis)
		{

		}

		void RenderSphere::Scale(const float scale)
		{

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