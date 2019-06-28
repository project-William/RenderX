#pragma once
#include "..//..//Core.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace renderx {
	namespace graphics {

		struct WinPros
		{
			unsigned int win_Width = 1280, win_Height = 720;
			std::string win_Title = "RenderX";
			GLFWwindow* glWindowPtr = nullptr;
		};


		class REN_API Window
		{
		private:
			WinPros m_WinPros;
			static Window* m_Instance;
			Window();
			bool __init();
		public:
			~Window();
			static Window& Create();

			inline GLFWwindow* GetWinPtr()const { return m_WinPros.glWindowPtr; }
			inline unsigned int GetWinWidth()const { return m_WinPros.win_Width; }
			inline unsigned int GetWinHeight()const { return m_WinPros.win_Height; }
			inline Window* GetWinClassPtr()const { return m_Instance; }

			void OnUpdate()const;
			void Clear()const;
			bool Closed()const;
		};


	}
}