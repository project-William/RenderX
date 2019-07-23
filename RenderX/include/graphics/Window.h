#pragma once
#include "..//..//Core.h"
#include "..//events/AppEvent.h"

namespace renderx {
	namespace graphics {

		struct REN_API WinData
		{
			unsigned int win_Width, win_Height;
			std::string win_Title = "RenderX";
			GLFWwindow* glWindowPtr = nullptr;

			WinData(unsigned int width = 1200, unsigned int height = 800)
				:win_Width(width),win_Height(height),win_Title("RenderX")
			{ }

		};

		class REN_API Window
		{
		private:

			WinData m_WinData;
			static Window* m_Instance;
			Window();
			bool init();
			Window& operator=(const Window& other) = delete;
			Window(const Window& other) = delete;
		public:
			~Window();
			static Window* Create();

			inline GLFWwindow* GetWinPtr()const { return m_WinData.glWindowPtr; }
			inline unsigned int GetWinWidth()const { return m_WinData.win_Width; }
			inline unsigned int GetWinHeight()const { return m_WinData.win_Height; }
			inline Window* GetWinClassPtr()const { return m_Instance; }
			inline WinData& GetWinData() { return m_WinData; }


			void OnUpdate()const;
			void Clear()const;
			void ClearColor()const;
			bool Closed()const;
		};
	}
}