#include "graphics/render/Render.h"

namespace renderx {
	namespace graphics {

		Render::Render()
			:m_VArray(nullptr),m_Shader(nullptr)
		{
			m_VArray = new VertexArray(sizeof(vertices), vertices);
			m_Shader = new Shader("shader/vertex.vert", "shader/fragment.frag");
			m_Layout = { { ShaderDataType::FLOAT3,"VertexPos" } };
			m_VArray->AddBufferLayout(m_Layout);
		}

		Render::~Render()
		{
			delete m_VArray;
			delete m_Shader;
		}


		void Render::Build()
		{
			
		}

		void Render::RenderAttrib()
		{
			
		}


		void Render::use()
		{
			m_Shader->BindShaderProgram();
		}

		void Render::Draw()
		{
			m_VArray->BindVertexArray();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	
	}
}