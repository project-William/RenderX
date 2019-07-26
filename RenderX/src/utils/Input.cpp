#include "utils/Input.h"

namespace renderx {
	namespace utils {

		Input::Input(graphics::WinData& windata)
			:m_WinData(windata)
		{
		}

		Input::~Input()
		{

		}

		bool Input::IsKeyPressed(int keycode)
		{
			auto state = glfwGetKey(m_WinData.glWindowPtr, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}


	}
}