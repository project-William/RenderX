#pragma once
#include "Event.h"

namespace renderx::base
{
	class MouseMovedEvent :public Event
	{
	private:
		float m_Xpos, m_Ypos;
	public:
		MouseMovedEvent(float x, float y)
			:m_Xpos(x), m_Ypos(y)
		{
		}
		~MouseMovedEvent() {}

		float GetMouseXPos()const { return m_Xpos; }
		float GetMouseYPos()const { return m_Ypos; }
		glm::vec2 GetMousePos()const { return glm::vec2(m_Xpos, m_Ypos); }

		EVENT_CLASS_TYPE(RX_MOUSE_MOVE)
			EVENT_NAME_TYPE(RX_MOUSE_MOVE)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT)
	};

	class MouseScrollEvent :public Event
	{
	private:
		float m_XOffset, m_YOffset;
	public:
		MouseScrollEvent(float xoffset, float yoffset)
			:m_XOffset(xoffset), m_YOffset(yoffset)
		{
		}

		~MouseScrollEvent() {}

		float GetXOffset()const { return m_XOffset; }
		float GetYOffset()const { return m_YOffset; }

		EVENT_CLASS_TYPE(RX_MOUSE_SCROLL)
			EVENT_NAME_TYPE(RX_MOUSE_SCROLL)

			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_INPUT)
	};


	class MouseButtonEvent :public Event
	{
	protected:
		int m_MouseButton;
		MouseButtonEvent(int button)
			:m_MouseButton(button)
		{

		}

	public:

		int GetMouseButton()const { return m_MouseButton; }

		EVENT_CLASS_TYPE(RX_MOUSE_BUTTON)
		EVENT_NAME_TYPE(RX_MOUSE_BUTTON)
		EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_MOUSE | RX_EVENT_CATEGORY_MOUSE_BUTTON | RX_EVENT_CATEGORY_INPUT)

	};

	class MousePressedEvent :public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button)
			:MouseButtonEvent(button)
		{
		}

		EVENT_CLASS_TYPE(RX_MOUSE_PRESS)
		EVENT_NAME_TYPE(RX_MOUSE_PRESS)

	};


	class MouseRelasedEvent :public MouseButtonEvent
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