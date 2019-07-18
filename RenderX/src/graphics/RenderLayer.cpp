#include "graphics/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
			:m_Render(nullptr)//,m_FrameBuffer(nullptr)
		{
			m_Render = new Render();
		}

		RenderLayer::RenderLayer(WinData WinData)
			: m_Render(nullptr), m_WinData(WinData)//, m_FrameBuffer(nullptr)
		{
			m_Render = new Render();
			m_FrameBuffer = new FrameBuffer(m_WinData.win_Width, m_WinData.win_Height);
		}

		RenderLayer::~RenderLayer()
		{
			delete m_Render;
			delete m_FrameBuffer;
		}

		void RenderLayer::OnAttach()
		{
			m_Render->Draw();
		}

		void RenderLayer::OnDetach()
		{

		}

		void RenderLayer::TestDraw()
		{
			ImGuiWindowFlags window_flags = false;
			bool show = true;

			ImGui::SetNextWindowSize(ImVec2(1200, 800));

			ImGui::Begin("RenderX Settings");
			{
				// Early out if the window is collapsed, as an optimization.
				ImVec2 pos = ImGui::GetCursorScreenPos();
				std::cout << pos.x << "    " << pos.y << std::endl;
				m_Render->Draw();
				glViewport(0, 0, 1200, 800);
				auto tex = m_FrameBuffer->GetRendered();
				//glViewport(0, 0, 600, 360);
				ImGui::GetWindowDrawList()->AddImage((void*)tex, 
					ImVec2(ImGui::GetItemRectMin().x + pos.x,
						ImGui::GetItemRectMin().y + pos.y),
					ImVec2(pos.x + 1200, pos.y + 800),
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