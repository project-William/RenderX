#pragma once
#include "..//Layer.h"


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
			void ImguiWindow();
			void End();
		public:

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}