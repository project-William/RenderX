#include "graphics/render/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
			:m_Render(nullptr)
		{
			m_Render = new Render();
		}

		RenderLayer::~RenderLayer()
		{
			delete m_Render;
		}

		void RenderLayer::OnAttach()
		{
			m_Render->Draw();
		}

		void RenderLayer::OnDetach()
		{

		}

		void RenderLayer::OnImguiLayer()
		{
			m_Render->Draw();
		}


	}
}