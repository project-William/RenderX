#pragma once
#include "Event.h"


namespace renderx::events
{
	class REN_API KeyboardEvent :public Event
	{
	public:

		KeyboardEvent(int32_t keycode)
			:m_KeyCode(keycode)
		{ }

		virtual ~KeyboardEvent()
		{ }

		int32_t GetKeyCode()const { return m_KeyCode; }

		EVENT_CLASS_TYPE(RX_KEYBOARD)
			EVENT_NAME_TYPE(RX_KEYBOARD)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_KEYBOARD | RX_EVENT_CATEGORY_INPUT)

	protected:
		int32_t m_KeyCode;
	};


	class REN_API KeyPressedEvent :public KeyboardEvent
	{
	public:
		KeyPressedEvent(int32_t keycode, int32_t keyrepeatcount)
			:KeyboardEvent(keycode), m_KeyRepeatCount(keyrepeatcount)
		{ }

		int32_t GetKeyRepeatCount()const { return m_KeyRepeatCount; }

		EVENT_CLASS_TYPE(RX_KEY_PRESS)
			EVENT_NAME_TYPE(RX_KEY_PRESS)

	private:
		int32_t m_KeyRepeatCount;
	};

	class REN_API KeyReleasedEvent :public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int32_t keycode)
			:KeyboardEvent(keycode)
		{ }

		EVENT_CLASS_TYPE(RX_KEY_RELEASE)
			EVENT_NAME_TYPE(RX_KEY_RELEASE)

	};
}