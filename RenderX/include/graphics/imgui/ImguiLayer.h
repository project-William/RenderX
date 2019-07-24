#pragma once
#include "..//Layer.h"


namespace renderx {
	namespace graphics {

		class REN_API ImguiLayer:public Layer
		{
		private:
			WinData m_WinData;
			GLFWwindow* m_Window = nullptr;
		public:
			ImguiLayer();
			~ImguiLayer();



			ImguiLayer(GLFWwindow* window, WinData windata);
		private:
			void SetUpImguiLayer();

		public:

			void Begin();
			void ShowDemo();
			void ImguiWindow();

			void SettingWindowBegin();

			void SettingWindowEnd();

			void End();
		public:

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}