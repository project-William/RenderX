#include "graphics/render/Render.h"


namespace renderx {
	namespace graphics {

		Render::Render()
			:m_ShaderProgram(nullptr), m_VertexArray(nullptr) {}


		Render::Render(const std::string& vfile, const std::string& ffile)
			:m_ShaderProgram(nullptr),m_VertexArray(nullptr)
		{
			m_ShaderProgram = new ShaderProgram(vfile, ffile);
			m_VertexArray = new VertexArray();
			
		}

		void Render::SetUp()
		{
			m_VertexArray->SetVbuffer();
			m_VertexArray->Bind();
		}
			
		Render::~Render()
		{
		}


	}
}