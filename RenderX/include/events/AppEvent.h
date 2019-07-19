#pragma once
#include "Event.h"

namespace renderx {
	namespace events {
		
		class REN_API WindowResizedEvent :public Event
		{
		private:
			unsigned int m_Width, m_Height;
			
		public:
		
			WindowResizedEvent():m_Width(0),m_Height(0)	{}
			WindowResizedEvent(unsigned int width, unsigned int height)
				:m_Width(width),m_Height(height)
			{
				glViewport(0, 0, width, height);
			}
			~WindowResizedEvent(){}

			inline const unsigned int GetWidth()const { return m_Width; }
			inline const unsigned int GetHeight()const { return m_Height; }
					
			EVENT_CLASS_TYPE(WindowResized)
			EVENT_NAME_TYPE(WindowResized)

		};


		class REN_API KeyTypeEvent :public Event
		{
		private:
			unsigned int m_KeyCode;
		public:
			KeyTypeEvent():m_KeyCode(0){}
			KeyTypeEvent(unsigned int keycode)
				:m_KeyCode(keycode)
			{

			}

			~KeyTypeEvent(){}
			inline unsigned int GetKeyCode()const { return m_KeyCode; }

			EVENT_CLASS_TYPE(KeyTyped)
			EVENT_NAME_TYPE(KeyTyped)

		};

		class REN_API WindowClosed :public Event
		{
		private:

		};




	}
}




