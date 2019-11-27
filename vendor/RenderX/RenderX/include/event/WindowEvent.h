#pragma once
#include "Event.h"

namespace renderx::events {

	class REN_API WindowResizedEvent :public Event
	{
	private:
		unsigned int m_Width, m_Height;

	public:

		WindowResizedEvent() :m_Width(0), m_Height(0) {}
		WindowResizedEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height)
		{
			glViewport(0, 0, width, height);
		}
		~WindowResizedEvent() {}

		inline const unsigned int GetWidth()const { return m_Width; }
		inline const unsigned int GetHeight()const { return m_Height; }

		EVENT_CLASS_TYPE(RX_WINDOW_RESIZE)
			EVENT_NAME_TYPE(RX_WINDOW_RESIZE)

			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_WINDOW)
	};


	class REN_API WindowClosedEvent :public Event
	{
	public:
		WindowClosedEvent() {}

		EVENT_CLASS_TYPE(RX_WINDOW_CLOSE)
			EVENT_NAME_TYPE(RX_WINDOW_CLOSE)

			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_WINDOW)
	};


	class REN_API WindowMovedEvent :public Event
	{
	private:
		int m_Xpos, m_Ypos;
	public:
		WindowMovedEvent(int xpos, int ypos)
			:m_Xpos(xpos), m_Ypos(ypos)
		{

		}

		inline int GetWindowXpos()const { return m_Xpos; }
		inline int GetWindowYpos()const { return m_Ypos; }


		EVENT_CLASS_TYPE(RX_WINDOW_MOVE)
			EVENT_NAME_TYPE(RX_WINDOW_MOVE)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_WINDOW)
	};
}
