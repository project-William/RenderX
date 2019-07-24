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

		}

		RenderCube::~RenderCube()
		{
			delete m_RenderData;
		}


		void RenderCube::BindObject() const
		{
			m_RenderData->m_Shader->BindShaderProgram();
		}

		void RenderCube::UnbindObject()const
		{
			m_RenderData->m_Shader->UnbindShaderProgram();
		}

		void RenderCube::Draw()
		{
			m_RenderData->m_VAO->BindVertexArray();
			m_RenderData->m_Shader->BindShaderProgram();
			glDrawArrays(GL_TRIANGLES, 0, 36);
			m_RenderData->m_VAO->UnbindVertexArray();
		}


	}

}