#pragma once
#include "Event.h"

namespace renderx::events
{

	class REN_API MouseMovedEvent :public Event
	{
	private:
		float m_Xpos, m_Ypos;
	public:
		MouseMovedEvent(float x, float y)
			:m_Xpos(x), m_Ypos(y)
		{

		}
		~MouseMovedEvent() {}

		inline float GetMouseXPos()const { return m_Xpos; }
		inline float GetMouseYPos()const { return m_Ypos; }
		inline glm::vec2 GetMousePos()const { return glm::vec2(m_Xpos, m_Ypos); }

		EVENT_CLASS_TYPE(RX_MOUSE_MOVE)
			EVENT_NAME_TYPE(RX_MOUSE_MOVE)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT)
	};

	class REN_API MouseScrollEvent :public Event
	{
	private:
		float m_XOffset, m_YOffset;
	public:
		MouseScrollEvent(float xoffset, float yoffset)
			:m_XOffset(xoffset), m_YOffset(yoffset)
		{

		}

		~MouseScrollEvent() {}

		inline float GetXOffset()const { return m_XOffset; }
		inline float GetYOffset()const { return m_YOffset; }

		EVENT_CLASS_TYPE(RX_MOUSE_SCROLL)
			EVENT_NAME_TYPE(RX_MOUSE_SCROLL)

			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT)
	};


	class REN_API MouseButtonEvent :public Event
	{
	protected:
		int m_MouseButton;
		MouseButtonEvent(int button)
			:m_MouseButton(button)
		{

		}

	public:

		inline int GetMouseButton()const { return m_MouseButton; }

		EVENT_CLASS_TYPE(RX_MOUSE_BUTTON)
			EVENT_NAME_TYPE(RX_MOUSE_BUTTON)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_MOUSE_BUTTON | RX_EVENT_CATEGORY_INPUT)

	};

	class REN_API MousePressedEvent :public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button)
			:MouseButtonEvent(button)
		{

		}

		EVENT_CLASS_TYPE(RX_MOUSE_PRESS)
			EVENT_NAME_TYPE(RX_MOUSE_PRESS)

	};


	class REN_API MouseRelasedEvent :public MouseButtonEvent
	{
	public:
		MouseRelasedEvent(int button)
			:MouseButtonEvent(button)
		{

		}

		EVENT_CLASS_TYPE(RX_MOUSE_RELEASE)
			EVENT_NAME_TYPE(RX_MOUSE_RELEASE)
	};

}