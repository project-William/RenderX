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
				glViewport(0, 0, m_Width, m_Height);
			}
			~WindowResizedEvent(){}

			inline const unsigned int GetWidth()const { return m_Width; }
			inline const unsigned int GetHeight()const { return m_Height; }
					
			EVENT_CLASS_TYPE(WindowResized)
			EVENT_NAME_TYPE(WindowResized)

		};

	}
}




