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
			m_RenderData->m_VAO = std::unique_ptr<VertexArray>(
				new VertexArray(sizeof(float) * m_CubeData.size(), &m_CubeData[0]));
			m_RenderData->m_Layout = { 
				{ ShaderDataType::FLOAT3, "VertexPos" },
				{ ShaderDataType::FLOAT2, "TexCoords" }
			};
			m_RenderData->m_VAO->AddBufferLayout(m_RenderData->m_Layout);
			m_RenderData->m_Shader = std::unique_ptr<Shader>(new Shader(vspath, fspath));

			//default properties
			m_Trans.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
			m_Trans.model = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, glm::vec3(0.0f, 0.0f, -3.0f));
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
			m_RenderData->m_VAO->BindVertexArray();
			m_RenderData->m_Shader->BindShaderProgram();
			//set view matrix
			m_Trans.view = glm::mat4(1.0f);
			m_Trans.view = glm::translate(m_Trans.view, m_Trans.position);
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
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_RenderData->m_VAO->UnbindVertexArray();
		}

		void RenderCube::Color(const WinData& windata)
		{
			ImGui::ColorEdit4("Color", &m_Trans.color[0]);
			
			ImGui::SliderFloat3("Position", &m_Trans.position[0], -10.0f, 2.0f);
		}


		void RenderCube::Position(const glm::vec3& position)
		{
			m_Trans.view = glm::translate(m_Trans.view, position);
		}

		void RenderCube::Rotation(const float radians, const glm::vec3& axis)
		{
			m_Trans.model = glm::rotate(m_Trans.model, glm::radians(radians), axis);
		}

		void RenderCube::Scale(const float scale)
		{
			
		}

		void RenderCube::RenderProperties()
		{

		}

	}

}