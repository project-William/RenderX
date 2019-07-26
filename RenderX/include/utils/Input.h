#pragma once
#include "..//graphics/Window.h"

namespace renderx {
	namespace utils {

		class REN_API Input
		{
		public:
			Input(graphics::WinData& windata);
			~Input();
			bool IsKeyPressed(int keycode);
			
			void ProcessInput()
			{
				if (IsKeyPressed(GLFW_KEY_ESCAPE))
				{
					std::cout << "Key pressed" << std::endl;
					glfwSetWindowShouldClose(m_WinData.glWindowPtr, GL_TRUE);
				}
			}

		private:
			graphics::WinData& m_WinData;

		};
	}
}