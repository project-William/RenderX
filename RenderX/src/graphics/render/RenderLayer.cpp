#include "graphics/render/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
			:m_Render(nullptr)
		{
			m_Render = new Render();
		}

		RenderLayer::RenderLayer(WinPros winPros)
			:m_Render(nullptr),m_WinData(winPros)
		{
			
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
			ImGuiWindowFlags window_flags = false;
			m_Render->Draw();

			bool show = true;
			if (!ImGui::Begin("RenderX Settings", &show, window_flags))
			{
				// Early out if the window is collapsed, as an optimization.
                
				ImGui::End();
				return;
			}

			ImGui::End();
		}
	}
}