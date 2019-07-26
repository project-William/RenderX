#pragma once
#include "..//..//Core.h"
#include "..//events/AppEvent.h"
#include "..//events/MouseEvent.h"
#include "..//events/KeyboardEvent.h"

namespace renderx {
	
	namespace graphics {


		struct REN_API WinData
		{
			unsigned int win_Width, win_Height;
			std::string win_Title;
			GLFWwindow* glWindowPtr = nullptr;

			WinData(unsigned int width = 1200, unsigned int height = 800)
				:win_Width(width),win_Height(height),win_Title("RenderX")
			{ }

			float mouse_xpos, mouse_ypos;

			std::function<void(events::Event&)> EventCallback;
			
			void OnEvent(events::Event& e)
			{
				if (EventCallback)
				{
					EventCallback(e);
				}
			}

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

			//cursor position
			inline float GetCursorPosX()const { return m_WinData.mouse_xpos; }
			inline float GetCursorPosY()const { return m_WinData.mouse_ypos; }

			inline GLFWwindow* GetWinPtr()const { return m_WinData.glWindowPtr; }
			inline unsigned int GetWinWidth()const { return m_WinData.win_Width; }
			inline unsigned int GetWinHeight()const { return m_WinData.win_Height; }
			inline Window* GetWinClassPtr()const { return m_Instance; }
			inline WinData& GetWinData() { return m_WinData; }

			inline void SetEventCallback(const std::function<void(events::Event&)>& callback)
			{
				m_WinData.EventCallback = callback;
			}

			void OnWindowResized();
			void OnUpdate()const;
			void Clear()const;
			void ClearColor()const;
			bool Closed()const;
		};
	}
}