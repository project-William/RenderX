#include "graphics/render/Block.h"


namespace renderx
{
	namespace graphics
	{
		Block::Block()
		{
			m_VertexArray = std::shared_ptr<VertexArray>(new VertexArray(sizeof(float)*m_BlockData.size(),&m_BlockData[0]));
			m_Layout =
			{
				{ ShaderDataType::FLOAT3, "a_VertexPos" },
				{ ShaderDataType::FLOAT2, "a_TexCoords" },
				{ ShaderDataType::FLOAT3, "a_Normals" }
			};

			m_VertexArray->AddBufferLayout(m_Layout);
		}

		Block::~Block()
		{ }

		void Block::BindVAO()
		{
			m_VertexArray->BindVertexArray();
		}

		void Block::Draw()
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		void Block::SetMVP(std::function<void()> func)
		{
			func();
		}

	}
}