#include "graphics/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
			:m_Render(nullptr) 
		{
			m_Render = new Render();
		}

		RenderLayer::RenderLayer(WinData& WinData)
			: m_Render(nullptr), m_WinData(WinData)
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

		void RenderLayer::TestDraw(const WinData& windata, const GLuint& texture)
		{

			ImGui::Begin("RenderX Viewport");
			{
				ImVec2 p = ImGui::GetCursorPos();
				ImVec2 pos = ImGui::GetCursorScreenPos();
				//std::cout << pos.x << "    " << pos.y << std::endl;
				ImGui::GetWindowViewport();
				ImGui::GetWindowDrawList()->AddImage((void*)texture, 
					ImVec2(pos.x, pos.y),
					ImVec2(pos.x + ImGui::GetWindowWidth(), pos.y + ImGui::GetWindowHeight()),
					ImVec2(0, 1), ImVec2(1, 0));
			}

			ImGui::End();
		}

		void RenderLayer::OnImguiLayer()
		{
			ImGuiWindowFlags window_flags = false;

			bool show = true;
			if (!ImGui::Begin("RenderX Settings", &show, window_flags))
			{
				// Early out if the window is collapsed, as an optimization.
				m_Render->Draw();
				ImGui::End();
				return;
			}
			
			ImGui::End();
		}
	}
}