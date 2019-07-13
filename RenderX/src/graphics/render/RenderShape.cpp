#include "graphics/render/RenderShape.h"

namespace renderx {
	namespace graphics {

		RenderShape::RenderShape()
		{
			MakeShape();
		}

		RenderShape::~RenderShape()
		{

		}


		void RenderShape::BindObject()const
		{

		}

		void RenderShape::UnbindObject()const
		{

		}


		void RenderShape::Draw()
		{
			DrawTriangle();
		}

		void RenderShape::DrawTriangle()
		{
			m_Shape.first->m_Shader->BindShaderProgram();
			m_Shape.first->m_VAO->BindVertexArray();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			m_Shape.first->m_VAO->UnbindVertexArray();
			m_Shape.first->m_Shader->UnbindShaderProgram();

		}

		void RenderShape::DrawRectangle()
		{

		}

		void RenderShape::MakeShape()
		{
			m_Shape.first = new Shape();
			m_Shape.first->m_VAO = std::unique_ptr<VertexArray>(new VertexArray(sizeof(float) * m_ShapeData.triangle.size(),
				&m_ShapeData.triangle[0]));
			m_Shape.first->m_Layout = { {ShaderDataType::FLOAT3, "VertexPos"} };
			m_Shape.first->m_VAO->AddBufferLayout(m_Shape.first->m_Layout);
			m_Shape.first->m_Shader = std::unique_ptr<Shader>(new Shader("shader/vertex.vert", "shader/fragment.frag"));
		}

	}
}


