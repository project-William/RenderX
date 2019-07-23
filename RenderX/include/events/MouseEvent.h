#pragma once
#include "Event.h"

namespace renderx {
	namespace events {

		class REN_API MouseMovedEvent :public Event
		{
		private:
			float m_Xpos, m_Ypos;
		public:
			MouseMovedEvent(float x, float y)
				:m_Xpos(x),m_Ypos(y)
			{

			}
			~MouseMovedEvent(){}

			inline float GetMouseXPos()const { return m_Xpos; }
			inline float GetMouseYPos()const { return m_Ypos; }
			EVENT_CLASS_TYPE(MouseMovement)
			EVENT_NAME_TYPE(MouseMovement)
		};

		class REN_API MouseScrollEvent :public Event
		{
		private:
			float m_XOffset, m_YOffset;
		public:
			MouseScrollEvent(float xoffset, float yoffset)
				:m_XOffset(xoffset),m_YOffset(yoffset)
			{

			}

			~MouseScrollEvent(){}

			inline float GetXOffset()const { return m_XOffset; }
			inline float GetYOffset()const { return m_YOffset; }

			EVENT_CLASS_TYPE(ScrollMovement)
			EVENT_NAME_TYPE(ScrollMovement)
		};








	}
}