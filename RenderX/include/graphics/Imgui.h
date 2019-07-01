#pragma once

#include "..//..//Core.h"


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace renderx {
	namespace graphics {
		class REN_API Imgui
		{
		public:
			Imgui();

			void set(GLFWwindow* window);
			

			void begin();
			

			void show();
		

			void end(GLFWwindow* window);
			
		};
	}
}