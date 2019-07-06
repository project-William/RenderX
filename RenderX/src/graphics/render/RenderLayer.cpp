#include "graphics/render/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
		{
			Render* obj = new Render("shadersrc/basicVertexShader.vert", "shadersrc/basicFragmentShader.frag");
			m_RenderObj.push_back(obj);
		}

		RenderLayer::~RenderLayer()
		{
			for (auto& obj : m_RenderObj)
				delete obj;
		}

		void RenderLayer::OnAttach()
		{
			for (auto& obj : m_RenderObj)
			{
				obj->SetUp();
				obj->GetShaderProgram().BindShaderProgram();
				obj->GetVertexArray().Bind();
			}
		}

		void RenderLayer::OnDetach()
		{
			for (auto& obj : m_RenderObj)
			{
				obj->GetShaderProgram().UnbindShaderProgram();
				obj->GetVertexArray().Bind();
			}
		}


	}
}