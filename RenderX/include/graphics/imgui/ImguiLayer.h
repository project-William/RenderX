#pragma once
#include "..//Layer.h"


namespace renderx {
	namespace ui {

		class REN_API ImguiLayer :public graphics::Layer
		{
		private:
			graphics::WinData m_WinData;
			GLFWwindow* m_Window = nullptr;
			bool m_Open = true;
		public:
			ImguiLayer();
			~ImguiLayer();

			ImguiLayer(const graphics::WinData& windata);
		private:
			void SetUpImguiLayer();
			
		public:

			void Begin();

			void End();

		public:

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}