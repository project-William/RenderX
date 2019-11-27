#pragma once
#include "..//Common.h"
#include "event/Event.h"

namespace renderx
{
	struct REN_API WinData
	{
		int32_t m_Width, m_Height;
		const char* m_Title;
		GLFWwindow* glWindowPtr = nullptr;

		WinData(int32_t width = 1280, int32_t height = 720)
			:m_Width(width), m_Height(height), m_Title("RenderX")
		{ }

		float mouse_xpos = 0, mouse_ypos = 0;

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
		static std::shared_ptr<Window> m_Instance;
		Window();
		bool init();
		Window& operator=(const Window& other) = delete;
		Window(const Window& other) = delete;
	public:
		~Window();
		static std::shared_ptr<Window> Create();

		float GetCursorPosX()const { return m_WinData.mouse_xpos; }
		float GetCursorPosY()const { return m_WinData.mouse_ypos; }

		GLFWwindow* GetWinPtr()const { return m_WinData.glWindowPtr; }
		int32_t GetWidth()const { return m_WinData.m_Width; }
		int32_t GetHeight()const { return m_WinData.m_Height; }
		static std::shared_ptr<Window> GetWindowInstance() { return m_Instance; }
		WinData& GetWinDataRef() { return m_WinData; }

		void SetEventCallback(const std::function<void(events::Event&)>& callback)
		{
			m_WinData.EventCallback = callback;
		}

		void OnWindowResized();
		void OnUpdate()const;
		void Clear()const;
		void ClearColor()const;
		bool Closed()const;
		void ConfigViewport(int32_t width, int32_t height);
		void ConfigFrameSize();
	};


}