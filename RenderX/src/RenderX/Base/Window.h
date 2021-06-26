#pragma once
#include "pch.h"
#include "Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"


namespace renderx::base
{
	struct WindowData
	{
		uint32_t m_Width, m_Height;
		std::string m_Title;
		GLFWwindow* m_WinPtr;
		float mouse_x, mouse_y;
		bool m_IsWindowResized;
		WindowData()
			:m_Width(1280),m_Height(720),m_Title("RenderX"), m_WinPtr(nullptr),m_IsWindowResized(false)
		{}

		std::function<void(Event&)> EventCallback;

		void OnEvent(Event& e)
		{
			if (EventCallback)
			{
				EventCallback(e);
			}
		}
	};

	class Window
	{
	public:
		static std::shared_ptr<Window>& Get();
		~Window() {}
		Window(const Window&) = delete;

		void OnUpdate();
		static void ClearColor(float r = 0.2, float g = 0.2, float b = 0.2, float a = 0.2);
		static void ClearBuffer();
		static void ConfigViewport(int width, int height);
		bool Init();
		bool Close();

		WindowData& GetWinDataRef() { return m_Data; }
		WindowData& GetWinDataVal() { return m_Data; }


		GLFWwindow* GetNativeWindow() { return m_Data.m_WinPtr; }

		void SetEventCallback(const std::function<void(Event&)>& callback)
		{
			m_Data.EventCallback = callback;
		}

		void ResetWindowResizedSignal() { m_Data.m_IsWindowResized = false; }
		bool GetWindowResizedSignal() { return m_Data.m_IsWindowResized; }

		uint32_t GetWindowWidthVal() { return m_Data.m_Width; }
		uint32_t GetWindowHeightVal() { return m_Data.m_Height; }


	private:
		Window();
		WindowData m_Data;
		static std::shared_ptr<Window> s_Instance;

		
	};
}

