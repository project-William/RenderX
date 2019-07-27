#pragma once
#include "Event.h"


namespace renderx {
	namespace events {

		class REN_API KeyboardEvent :public Event
		{
		public:

			KeyboardEvent(int keycode)
				:m_KeyCode(keycode)
			{
				
			}

			virtual ~KeyboardEvent()
			{
			}

			inline int GetKeyCode()const { return m_KeyCode; }

			EVENT_CLASS_TYPE(RX_KEYBOARD)
			EVENT_NAME_TYPE(RX_KEYBOARD)
			EVENT_CATEGORY_TYPE(RX_EVENT_CATEGORY_KEYBOARD | RX_EVENT_CATEGORY_INPUT)

		protected:
			int m_KeyCode;
		};


		class REN_API KeyPressedEvent :public KeyboardEvent
		{
		public:
			KeyPressedEvent(int keycode, int keyrepeatcount)
				:KeyboardEvent(keycode),m_KeyRepeatCount(keyrepeatcount)
			{

			}

			inline int GetKeyRepeatCount()const { return m_KeyRepeatCount; }

			EVENT_CLASS_TYPE(RX_KEY_PRESS)
			EVENT_NAME_TYPE(RX_KEY_PRESS)

		private:
			int m_KeyRepeatCount;
		};

		class REN_API KeyReleasedEvent :public KeyboardEvent
		{
		public:
			KeyReleasedEvent(int keycode)
				:KeyboardEvent(keycode)
			{

			}

			EVENT_CLASS_TYPE(RX_KEY_RELEASE)
			EVENT_NAME_TYPE(RX_KEY_RELEASE)

		};

	}
}