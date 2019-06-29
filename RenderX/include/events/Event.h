#pragma once
#include "..//..//Core.h"

namespace renderx {
	namespace events {

		enum class Type
		{
			KEY_PRESSED = VALUE(0),
			KEY_RELEASED = VALUE(1),
			MOUSE_PRESSED = VALUE(2),
			MOUSE_CLICKED = VALUE(3),
			MOUSE_MOVED = VALUE(4),
			WINDOW_RESIZED = VALUE(5)
		};

		class REN_API Event 
		{
		protected:
			Type m_Type;
			bool m_Handled;

		protected:
			Event(Type& type);
			virtual ~Event();

		public:
			
			inline bool GetHandled()const { return m_Handled; }
			inline Type GetType()const { return m_Type; }


			static std::string TypeToString(Type& type);

		};



	}
}