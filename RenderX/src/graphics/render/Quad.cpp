#include "graphics/render/Quad.h"

namespace renderx
{
	namespace graphics
	{
		Quad::Quad()
		{
			m_VertexArray = std::shared_ptr<VertexArray>(new VertexArray(sizeof(float) * m_QuadData.size(), &m_QuadData[0]));
			m_Layout = 
			{
				{ ShaderDataType::FLOAT3, "a_VertexPos" },
				{ ShaderDataType::FLOAT2, "a_TexCoords" },
				{ ShaderDataType::FLOAT3, "a_Normals" }
			};
			m_VertexArray->AddBufferLayout(m_Layout);
		}

		Quad::~Quad()
		{

		}

		void Quad::BindVAO()
		{
			m_VertexArray->BindVertexArray();
		}

		void Quad::Draw()
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}


		void Quad::SetMVP(std::function<void()> func)
		{
			func();
		}
	}
}