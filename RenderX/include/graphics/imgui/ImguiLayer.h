#pragma once
#include "..//Layer.h"
#include "..//Window.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


namespace renderx {
	namespace graphics {

		class REN_API ImguiLayer:public Layer
		{
		private:
			WinPros m_WinData;
		public:
			ImguiLayer();
			~ImguiLayer();

			ImguiLayer(WinPros winData);
		private:
			void SetUpImguiLayer();

		public:

			
			void Begin();
			void ShowDemo();
			void End();
		public:

			void OnAttach() override;
			void OnDetach() override;

			void OnImguiLayer() override;

		};

	}
}