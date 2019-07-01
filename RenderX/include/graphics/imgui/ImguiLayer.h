#pragma once
#include "..//Layer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


namespace renderx {
	namespace graphics {

		class REN_API ImguiLayer:public Layer
		{
		public:
			ImguiLayer();
			~ImguiLayer();

			ImguiLayer(GLFWwindow* window);

		public:

			void Begin();
			void ShowDemo();
			void End(GLFWwindow* window);
		public:

			void OnAttach() override;
			void OnDetach() override;

			void OnImguiLayer() override;

		};

	}
}