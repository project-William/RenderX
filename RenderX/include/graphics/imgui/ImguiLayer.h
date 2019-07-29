#pragma once
#include "..//Layer.h"


namespace renderx {
	namespace graphics {

		class REN_API ImguiLayer:public Layer
		{
		private:
			WinData m_WinData;
			GLFWwindow* m_Window = nullptr;
			bool m_Open = true;
		public:
			ImguiLayer();
			~ImguiLayer();

			ImguiLayer(GLFWwindow* window, WinData windata);
		private:
			void SetUpImguiLayer();
			
		public:

			void Begin();

			void End();
			void TestDraw(const WinData& windata,const GLuint& texture);

		public:

			void OnAttach() override;
			void OnDetach() override;
			void OnImguiLayer() override;

		};

	}
}