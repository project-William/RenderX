#pragma once
#include "..//..//Core.h"
#include "shader/VertexShader.h"
namespace renderx {
	namespace graphics {

		struct REN_API WinPros
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
			bool init();
			VertexShader* vs;
		public:
			~Window();
			static Window* Create();

			inline GLFWwindow*& GetWinPtr() { return m_WinPros.glWindowPtr; }
			inline unsigned int GetWinWidth()const { return m_WinPros.win_Width; }
			inline unsigned int GetWinHeight()const { return m_WinPros.win_Height; }
			inline Window* GetWinClassPtr()const { return m_Instance; }
			inline WinPros GetWinPros()const { return m_WinPros; }

			void OnUpdate()const;
			void Clear()const;
			bool Closed()const;
		};


	}
}