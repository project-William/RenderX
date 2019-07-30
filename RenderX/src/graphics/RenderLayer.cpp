#include "graphics/RenderLayer.h"

namespace renderx {
	namespace graphics {

		RenderLayer::RenderLayer()
			:m_Render(nullptr)
		{

		}

		RenderLayer::RenderLayer(const WinData& windata)
			: m_Render(nullptr)
		{

		}

		RenderLayer::~RenderLayer()
		{
			delete m_Render;
		}


		void RenderLayer::PushFrontRenderer(RenderObject* renderer)
		{
			m_Renderers.push_front(renderer);
		}

		void RenderLayer::PushBackRenderer(RenderObject* renderer)
		{
			m_Renderers.push_back(renderer);
		}

		void RenderLayer::DoRendering(const WinData& windata)
		{
			for (auto renderer : m_Renderers)
			{
				renderer->Draw(windata);
			}
		}


		void RenderLayer::RenderSkybox()
		{

		}


		void RenderLayer::RenderModel()
		{

		}


		void RenderLayer::OnAttach()
		{
		}

		void RenderLayer::OnDetach()
		{
		}

	
		void RenderLayer::OnImguiLayer()
		{
			ImGuiWindowFlags window_flags = false;

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
